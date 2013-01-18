/*
 Copyright (c) 2012 Thomas Johnson
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */
#import <iostream>
#import <sstream>
#import <iomanip>

#import "SequenceBuilder.h"
#import <llvm/Support/system_error.h>
#import <llvm/Support/MemoryBuffer.h>
#import <llvm/Bitcode/ReaderWriter.h>
#import <llvm/DataLayout.h>
#import <llvm/PassManager.h>
#import <llvm/Analysis/Verifier.h>
#import <llvm/LinkAllPasses.h>
#import <llvm/BasicBlock.h>

extern "C" {
#import "sys/cpu.h"
#import "sys/cpu_functions.h"
#import "cart_metadata.h"
#import "sys/bios.h"
}

using namespace std;

Module* readModule(LLVMContext* ctx, std::string path, std::string moduleName)
{
    error_code err;
    OwningPtr<MemoryBuffer> mb;
    
    err = MemoryBuffer::getFile(path, mb);
    if(err)
    {
        return NULL;
    }
    
    return ParseBitcodeFile(mb.get(), *ctx);
}

/// Mockup of the generated execution function
uint32_t exampleExecuteNative(system_t* sys)
{
entry:
    uint16_t pc = sys->cpu.pc;
    uint32_t execution_count = 0;
    
    switch (pc) {
        case 0x0000:
            cpu_op_LDSPnn(sys);
            execution_count += sys->cpu.m;
            cpu_op_XORr_a(sys);
            execution_count += sys->cpu.m;
        case 0x0007:
            cpu_op_LDHLDA(sys); // landing == true
            execution_count += sys->cpu.m;
            cpu_op_BIT7h(sys);
            execution_count += sys->cpu.m;
            cpu_op_JRNZn(sys);
            execution_count += sys->cpu.m; // terminator == true
            break;
        default:
            break;
    }
    
end:
    return execution_count;
}

void SequenceBuilder::buildFromCart(Module* m, system_t* sys)
{
    Function* execute = m->getFunction("execute");
    StructType* system_s = m->getTypeByName("struct.system_t");
    PointerType* pSystem_s = PointerType::getUnqual(system_s);
    
    BasicBlock* entry;
    SwitchInst* sw;
    BasicBlock* finish;
    Value* systemPointerArgument;
    
    // Create Execute function from scratch
    {
        if(execute) execute->eraseFromParent();
        
        FunctionType* ft = FunctionType::get(IntegerType::getInt32Ty(m->getContext()),
                                             pSystem_s,
                                             (Type*)0);
        
        execute = cast<Function>(m->getOrInsertFunction("execute", ft));
        entry = BasicBlock::Create(m->getContext(), "entry", execute);
        finish = BasicBlock::Create(m->getContext(), "finish", execute);

        // Populate entry block:
        //   get PC
        //   create execution cycle accumulator
        //   create switch(pc) defaulting to exit block
        
        Argument* argSystemPointer = execute->getArgumentList().begin();
        argSystemPointer->setName("sys");
        
        // Copy the System pointer from first argument, and retrieve its value
        AllocaInst* copyOfArgument = new AllocaInst(argSystemPointer->getType(), "", entry);
        StoreInst* storeCopyOfArgument = new StoreInst(argSystemPointer, copyOfArgument, false, entry);
        systemPointerArgument = cast<Value>(new LoadInst(copyOfArgument, "systemPointerArgument", false, entry));
        
        // Extract sys->cpu*
        std::vector<Value*> gep_indices;
        gep_indices.push_back(ConstantInt::get(m->getContext(), APInt(8*sizeof(void*), 0)));
        gep_indices.push_back(ConstantInt::get(m->getContext(), APInt(32, 0))); // Index into structure
        GetElementPtrInst* sys_cpu_gep = GetElementPtrInst::Create(argSystemPointer, gep_indices, "", entry);
        
        StructType* cpu_ty = m->getTypeByName("struct.cpu_t");
        PointerType* pCpu_ty = PointerType::getUnqual(cpu_ty);
        AllocaInst* allocateCpuPointer = new AllocaInst(pCpu_ty, "", entry);
        StoreInst* storeCpuPointer = new StoreInst(sys_cpu_gep, allocateCpuPointer, entry);
        LoadInst* cpuPointer = new LoadInst(allocateCpuPointer, "", entry);
        
        // Extract cpu.pc
        GetElementPtrInst* cpu_pc_gep = GetElementPtrInst::Create(cpuPointer, gep_indices, "", entry);
        LoadInst* loadPC = new LoadInst(cpu_pc_gep, "", entry);
        
        sw = SwitchInst::Create(loadPC, finish, 0, entry);
        
        // Populate finish block
        //   return execution cycle accumulator
        ReturnInst::Create(m->getContext(), ConstantInt::get(m->getContext(), APInt(32, 0)), finish);
        
        // Create translated blocks, inserting before "finish":
        // BasicBlock* current = BasicBlock::Create(m->getContext(), "", execute, finish);
        // Add "current" to the switch and begin populating the block
        // On landings, create a "next" block, add an unconditional jump from previous to next
        // On terminations, create an unconditional jump to finish block, then scan for new instructions
    }
    
    BasicBlock* b = NULL;
    // BIOS 0x0000-0x00FF
    for(uint32_t i = 0; i < 0x100; i++)
    {
        const cart_metadata_s md = bios_metadata[i];
        
        // Unvisited -> Unvisited: continue
        // Unvisited -> Visited: new block
        // Visited -> Visited: new block if landing or terminator.
        // Visited -> Unvisited: break, jump to end. Set previous to null.
        
        // Emit calls for visited instructions, skipping over unknown or unvisited memory
        if(md.isVisited && md.isInstruction)
        {
            // Build a friendly hex offset for use as labels
            std::ostringstream offset;
            offset << "0x" << setw(4) << hex << setfill('0') << i;
            
            // Offset for use in switch statement
            ConstantInt* iOffset = ConstantInt::get(Type::getInt16Ty(m->getContext()), i);
            
            
            // Chain blocks together if needed for a landing instruction.
            // If there is no previous block, there is no need for chaining.
            if(md.isLanding && (b != NULL))
            {
                cout << "case " << offset.str() << ": " << endl;
                
                BasicBlock* previous = b;
                b = BasicBlock::Create(m->getContext(), offset.str(), execute, finish);
                if(previous) BranchInst::Create(b, previous);
                // Then add to switch for current offset (Beware with 0xCB instructions)
                sw->addCase(iOffset, b);
            }
            
            // Ensure that a current block exists
            if(b == NULL)
            {
                cout << "case " << offset.str() << ": " << endl;
                b = BasicBlock::Create(m->getContext(), offset.str(), execute, finish);
                // Then add to switch for current offset (Beware with 0xCB instructions)
                sw->addCase(iOffset, b);
            }
            
            // Retrieve metadata about the currently-selected op
            cpu_op_metadata_s op_md = cpu_op_metadata_basic[bios[i]];
            if(op_md.opcode == 0xCB) op_md = cpu_op_metadata_cb[bios[++i]];
            
            // Create call instruction
            cout << "   " << offset.str() << ": " << op_md.name << "(";
            if(op_md.args >= 1) cout << "0x" << setw(2) << setfill('0') << hex << (unsigned int)bios[i + 1];
            if(op_md.args == 2) cout << ", 0x" << setw(2) << setfill('0') << hex << (unsigned int)bios[i + 2];
            cout << ")" << endl;
            
            Function* op = m->getFunction(op_md.impl_name);
            CallInst::Create(op, ArrayRef<Value*>(systemPointerArgument), "", b);
            
            // Terminate the block if the instruction demands it.
            if(op_md.terminator)
            {
                cout << "   break;" << endl;
                BranchInst::Create(finish, b);
                b = NULL;
            }
        }
        
        // Moving into an unvisited region of memory terminates the block.
        if(!md.isVisited && (b != NULL))
        {
            cout << "   break;" << endl;
            BranchInst::Create(finish, b);
            b = NULL;
        }
    }
    
    // Terminate the block for this memory segment if the final instruction did not do so
    if(b != NULL)
    {
        cout << "   break;" << endl;
        BranchInst::Create(finish, b);
    }
    
    // Reserved Memory 0x0000-0x00FF
    
    // Built-in ROM bank 0x0000-0x3FFF
    
    // Switchable ROM bank 0x4000-0x7FFF
}

bool SequenceBuilder::optimize(Module* m)
{
    PassManager pm;
    pm.add(new DataLayout(m));
    pm.add(createNoAAPass());
    pm.add(createTypeBasedAliasAnalysisPass());
    pm.add(createBasicAliasAnalysisPass());
    pm.add(createVerifierPass());
    // -domtree?
    pm.add(createGlobalOptimizerPass());
    pm.add(createIPSCCPPass());
    pm.add(createDeadArgEliminationPass());
    pm.add(createInstructionCombiningPass());
    pm.add(createCFGSimplificationPass());
    // -basiccg?
    pm.add(createPruneEHPass());
    pm.add(createFunctionInliningPass());
    pm.add(createFunctionAttrsPass());
    pm.add(createArgumentPromotionPass());
    pm.add(createScalarEvolutionAliasAnalysisPass());
    // -domtree?
    pm.add(createEarlyCSEPass());
    pm.add(createSimplifyLibCallsPass());
    pm.add(createLazyValueInfoPass());
    pm.add(createJumpThreadingPass());
    pm.add(createCorrelatedValuePropagationPass());
    pm.add(createCFGSimplificationPass());
    pm.add(createInstructionCombiningPass());
    pm.add(createTailCallEliminationPass());
    pm.add(createCFGSimplificationPass());
    pm.add(createReassociatePass());
    // -domtree
    // -loop
    pm.add(createLoopSimplifyPass());
    pm.add(createLCSSAPass());
    pm.add(createLoopRotatePass());
    pm.add(createLICMPass());
    pm.add(createLCSSAPass());
    pm.add(createLoopUnswitchPass());
    pm.add(createInstructionCombiningPass());
    pm.add(createScalarEvolutionAliasAnalysisPass());
    pm.add(createLoopSimplifyPass());
    pm.add(createLCSSAPass());
    pm.add(createIndVarSimplifyPass());
    pm.add(createLoopIdiomPass());
    pm.add(createLoopDeletionPass());
    pm.add(createLoopUnrollPass());
    // pm.add(createMemDepPrinter()); // -memdep?
    pm.add(createGVNPass());
    // pm.add(createMemDepPrinter());
    pm.add(createMemCpyOptPass());
    pm.add(createSCCPPass());
    pm.add(createInstructionCombiningPass());
    pm.add(createLazyValueInfoPass());
    pm.add(createJumpThreadingPass());
    pm.add(createCorrelatedValuePropagationPass());
    // -domtree?
    // pm.add(createMemDepPrinter());
    pm.add(createDeadStoreEliminationPass());
    pm.add(createAggressiveDCEPass());
    pm.add(createCFGSimplificationPass());
    pm.add(createInstructionCombiningPass());
    pm.add(createStripDeadPrototypesPass());
    pm.add(createGlobalDCEPass());
    pm.add(createConstantMergePass());
    // -domtree?
    pm.add(createVerifierPass());
    
    return pm.run(*m);
}
