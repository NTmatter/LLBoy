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
#import "SequenceBuilder.h"
#import <llvm/Support/system_error.h>
#import <llvm/Support/MemoryBuffer.h>
#import <llvm/Bitcode/ReaderWriter.h>
#import <llvm/DataLayout.h>
#import <llvm/PassManager.h>
#import <llvm/Analysis/Verifier.h>
#import <llvm/LinkAllPasses.h>

extern "C" {
#import "sys/cpu.h"
#import "sys/cpu_functions.h"
}

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

void SequenceBuilder::buildFromCart(Module* m, system_t* sys)
{
    // BIOS 0x0000-0x00FF
    
    // Reserved Memory 0x0000-0x00FF
    
    // Built-in ROM bank 0x0000-0x3FFF
    
    // Switchable ROM bank 0x4000-0x7FFF
}

void SequenceBuilder::optimize(Module* m)
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
    pm.add(createMemDepPrinter()); // -memdep?
    pm.add(createGVNPass());
    pm.add(createMemDepPrinter());
    pm.add(createMemCpyOptPass());
    pm.add(createSCCPPass());
    pm.add(createInstructionCombiningPass());
    pm.add(createLazyValueInfoPass());
    pm.add(createJumpThreadingPass());
    pm.add(createCorrelatedValuePropagationPass());
    // -domtree?
    pm.add(createMemDepPrinter());
    pm.add(createDeadStoreEliminationPass());
    pm.add(createAggressiveDCEPass());
    pm.add(createCFGSimplificationPass());
    pm.add(createInstructionCombiningPass());
    pm.add(createStripDeadPrototypesPass());
    pm.add(createGlobalDCEPass());
    pm.add(createConstantMergePass());
    // -domtree?
    pm.add(createVerifierPass());
    
    pm.run(*m);
}