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
    BasicBlock* entry = BasicBlock::Create(m->getContext(), "entry", execute);
    BasicBlock* finish = BasicBlock::Create(m->getContext(), "finish", execute);
    SwitchInst* sw;
    
    if(execute) execute->eraseFromParent();
    
    // Create Execute function from scratch
    {
        StructType* system_s = m->getTypeByName("struct.system_t");
        PointerType* pSystem_s = PointerType::getUnqual(system_s);
        FunctionType* ft = FunctionType::get(IntegerType::getInt32Ty(m->getContext()),
                                             pSystem_s,
                                             (Type*)0);
        
        execute = m->getOrInsertFunction("execute", ft);

        // Populate entry block:
        //   get PC
        //   create execution cycle accumulator
        //   create switch(pc) defaulting to exit block
        // Populate finish block
        //   return execution cycle accumulator
        
        // Create translated blocks, inserting before "finish":
        BasicBlock* current = BasicBlock::Create(m->getContext(), "", execute, finish);
        // Add "current" to the switch and begin populating the block
        // On landings, create a "next" block, add an unconditional jump from previous to next
        // On terminations, create an unconditional jump to finish block, then scan for new instructions
    }
    
    BasicBlock* b;
    // BIOS 0x0000-0x00FF
    for(int i = 0; i < 0x100; i++)
    {
        const cart_metadata_s md = bios_metadata[i];
        
        // Debugging info
        if(md.isVisited && md.isInstruction)
        {
            cpu_op_metadata_s op_md = cpu_op_metadata_basic[bios[i]];
            if(op_md.opcode == 0xCB) op_md = cpu_op_metadata_cb[bios[++i]];
            
            // Display op info
            if(md.isLanding && op_md.terminator)
            {
                cout << "TL";
            } else if(md.isLanding) {
                cout << " L";
            } else if(op_md.terminator) {
                cout << "T ";
            } else {
                cout << "  ";
            }
            cout << setw(2) << hex << setfill('0') << i << ": " << op_md.name << "(";
            if(op_md.args >= 1) cout << "0x" << setw(2) << hex << (unsigned int)bios[i + 1];
            if(op_md.args == 2) cout << ", 0x" << setw(2) << hex << (unsigned int)bios[i + 2];
            cout << ")";
            
            cout << endl;
        }
        
        // Unvisited -> Unvisited: continue
        // Unvisited -> Visited: new block
        // Visited -> Visited: new block if landing or terminator.
        // Visited -> Unvisited: break, jump to end. Set previous to null.
        
        if(md.isVisited && md.isInstruction)
        {
            // Chain blocks together if needed for a landing instruction.
            // If there is no previous block, there is no need for chaining.
            if(md.isLanding && b)
            {
                BasicBlock* previous = b;
                b = BasicBlock::Create(m->getContext(), "", execute, finish);
                BranchInst::Create(b, previous);
                // Then add to switch for current offset (Beware with 0xCB instructions)
                // sw->addCase(i, b);
            }
            
            // Ensure that a current block exists
            if(!b)
            {
                b = BasicBlock::Create(m->getContext(), "", execute, finish);
                // Then add to switch for current offset (Beware with 0xCB instructions)
                // sw->addCase(i, b);
            }
            
            // Retrieve metadata about the currently-selected op
            cpu_op_metadata_s op_md = cpu_op_metadata_basic[bios[i]];
            if(op_md.opcode == 0xCB) op_md = cpu_op_metadata_cb[bios[++i]];
            
            // Create call instruction
            Function* op = m->getFunction(op_md.impl_name);
            // CallInst::Create(op, ArrayRef<PointerType>(/* Function's sys_t argument */), "", b);
            
            // Terminate the block if necessary
            if(op_md.terminator)
            {
                BranchInst::Create(finish, b);
                b = NULL;
            }
        }
        
        // Moving into an unvisited region of memory. Terminate the block.
        if(!md.isVisited && b)
        {
            BranchInst::Create(finish, b);
            b = NULL;
        }
    }
    
    // Finally, finish an unterminated block if at the end of the memory region:
    if(b) BranchInst::Create(finish, b);
    
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
