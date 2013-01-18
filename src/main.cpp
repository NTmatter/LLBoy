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


#import <iostream>

#import <llvm/Support/system_error.h>
#import <llvm/LLVMContext.h>
#import <llvm/Function.h>
#import <llvm/Module.h>
#import <llvm/Support/MemoryBuffer.h>
#import <llvm/Bitcode/ReaderWriter.h>
#import <llvm/Analysis/Verifier.h>
#import <llvm/CallingConv.h>
#import <llvm/Support/TargetSelect.h>
#import <llvm/ExecutionEngine/ExecutionEngine.h>
#import <llvm/ExecutionEngine/JIT.h>

extern "C"
{
    #import "sys/system.h"
    #import "sys/cpu_functions.h"
    #import "cart_metadata.h"
}

#import "SequenceBuilder.h"

using namespace std;
using namespace llvm;

Module* read_module(LLVMContext* ctx, string path, string* error)
{
    error_code err;
    OwningPtr<MemoryBuffer> mb;

    err = MemoryBuffer::getFile(path, mb);
    if(err)
    {
        cerr << "Error reading bitcode file: " << err << endl;
        return NULL;
    }

    return ParseBitcodeFile(mb.get(), *ctx);
}

int main(int argc, char** argv)
{
    string error;
    LLVMContext* context = &(getGlobalContext());
 
    cout << "Loading System implementation bitcode...";
    Module* module_system = read_module(context, "sys/llboy.bc", &error);
    if(module_system)
    {
        cout << "done." << endl;
    } else {
        cerr << "Failed to load system module: " << error << endl;
        return -1;
    }
    
    SequenceBuilder::buildFromCart(module_system, initialize_system());
    // module_system->dump();
    
    cout << "Optimizing module...";
    if(SequenceBuilder::optimize(module_system))
    {
        cout << "done." << endl;
        // module_system->dump();
    } else {
        cout << "Module needed no optimizations" << endl;
    }
    
    // Create JIT for native target
    cout << "Creating execution engine...";
    InitializeNativeTarget();
    ExecutionEngine* engine = ExecutionEngine::createJIT(module_system, &error);
    if(engine)
    {
        cout << "done." << endl;
    } else {
        cerr << "Failed to create Execution Engine: " << error << endl;
        return -1;
    }

    // Find a function and get a pointer to it. Use ADDr_b for testing (ra += rb)
    cout << cpu_op_metadata_basic[0x80].impl_name << endl;
    Function* op_ADDr_b = module_system->getFunction(cpu_op_metadata_basic[0x80].impl_name);
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
    
    // Sanity check of retrieved function pointer
    system_t* state = initialize_system();
    state->cpu.a = 1;
    state->cpu.b = 2;
    void (*ADDr_b)(system_t*) = (void (*)(system_t*)) p_ADDr_b;
    ADDr_b(state);
    cout << "Executing function 1 + 2 = " << (int)(state->cpu.a) << endl;
    ADDr_b(state);
    cout << "Executing function 3 + 2 = " << (int)(state->cpu.a) << endl;
    
    // Try to execute the first bit of the bios
    cout << "Calling game's execute function..." << endl;
    system_t* state2 = initialize_system();
    Function* executeFunction = module_system->getFunction("execute");
    uint32_t (*execute)(system_t*) = (uint32_t (*)(system_t*)) engine->getPointerToFunction(executeFunction);
    uint32_t cycles = execute(state2);
    cout << "Completed in " << cycles << " cycles. PC is currently at " << hex << state2->cpu.pc << ". Uptime is " << dec << state2->cpu.clock.m << " cycles" << endl;
    cout << "Long run...";
    for(int i = 0; i < 0x10000; i++)
    {
        execute(state2);
        if(state2->cpu.pc != 0x07)
        {
            cout << hex << state2->cpu.pc << endl;
        }
        
        if(state2->cpu.pc == 0xa6) break;
    }
    cout << "Completed in " << cycles << " cycles. PC is currently at " << hex << state2->cpu.pc << ". Uptime is " << dec << state2->cpu.clock.m << " cycles" << endl;
    
    return 0;
}
