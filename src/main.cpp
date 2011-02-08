/*
 Copyright (c) 2011 Thomas Johnson
 
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


#include <iostream>

#include <llvm/LLVMContext.h>
#include <llvm/Function.h>
#include <llvm/Module.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/CallingConv.h>

#include <llvm/Target/TargetData.h>
#include <llvm/Target/TargetSelect.h>

extern "C"
{
    #include "sys/system.h"
    #include "sys/cpu.h"
    #include "sys/cpu_functions_names.h"
}

using namespace std;
using namespace llvm;

Module* read_module(LLVMContext* ctx, string path, string* error)
{
    MemoryBuffer* buffer;
    Module* out = NULL;
    if((buffer = MemoryBuffer::getFile(path, error)))
    {
        out = ParseBitcodeFile(buffer, *ctx, error);
        delete buffer;
    } else {
        cerr << "Could not find file " << path << endl;
    }
    return out;
}

int main(int argc, char** argv)
{
    string error;
    MemoryBuffer* buffer;
    LLVMContext* context = &(getGlobalContext());
 
    cout << "Loading System and CPU code...";   
    Module* module_cpu = read_module(context, "sys/cpu.o", &error);
    if(!module_cpu) cerr << "Failed to load CPU module: " << error << endl;
    Module* module_mmu = NULL;
    // if(!module_mmu) cerr << "Failed to load MMU module: " << error << endl;
    Module* module_system = read_module(context, "sys/system.o", &error);
    if(!module_system) cerr << "Failed to load System module: " << error << endl;
    cout << "Complete." << endl;
    
    // InitializeNativeTarget();
    // ExecutionEngine* engine = ExecutionEngine::create(module_system, false, &error);
    InitializeAllTargets();
    ExecutionEngine* engine = ExecutionEngine::createJIT(module_system, &error);
    if(engine)
    {
        cout << "Execution Engine created" << endl;
    } else {
        cerr << "Failed to create Execution Engine: " << error << endl;
        return -1;
    }
    
    engine->addModule(module_cpu);
    
    Function* op_ADDr_b = module_cpu->getFunction(cpu_op_names_basic[0x80]);
    if(op_ADDr_b)
    {
        cout << "Found ADDr_b function" << endl;
    } else {
        cerr << "Could not find ADDr_b" << endl;
        return -1;
    }
    
    void *p_ADDr_b = engine->getPointerToFunction(op_ADDr_b);
    if(p_ADDr_b)
    {
        cout << "Got function pointer for add instruction" << endl;
    } else {
        cerr << "Could not retrieve function pointer for add instruction" << endl;
        return -1;
    }
    
    system_t* state = (system_t*) malloc(sizeof(system_t));
    state->cpu.a = 1;
    state->cpu.b = 2;
    void (*ADDr_b)(system_t*) = (void (*)(system_t*)) p_ADDr_b;
    ADDr_b(state);
    cout << "Executing function 1 + 2 = " << (int)(state->cpu.a) << endl;
    ADDr_b(state);
    cout << "Executing function 3 + 2 = " << (int)(state->cpu.a) << endl;
    return 0;
}
