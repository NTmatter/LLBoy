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
#include <llvm/BasicBlock.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/CallingConv.h>

#include <llvm/Type.h>
#include <llvm/DerivedTypes.h>

#include <llvm/Target/TargetData.h>
#include <llvm/Target/TargetSelect.h>

#include <llvm/Constants.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/InstIterator.h>

using namespace std;
using namespace llvm;

Module* read_module(LLVMContext &ctx, string path, string* error)
{
    MemoryBuffer* buffer;
    Module* out = NULL;
    if((buffer = MemoryBuffer::getFile(path, error)))
    {
        out = ParseBitcodeFile(buffer, ctx, error);
        delete buffer;
    } else {
        cerr << "Could not find file " << path << endl;
    }
    return out;
}

int main (int argc, char const *argv[])
{
    cout << "Hello World!" << endl;
    
    // Create Module
    string error;
    LLVMContext &ctx = getGlobalContext();
    Module* cpu = read_module(ctx, "sys/cpu.o", &error);
    if(cpu == NULL)
    {
        cerr << "Could not find CPU objects" << endl;
        return 1;
    } else {
        cout << "Found CPU Implementation" << endl;
    }
    
    Module* sys = read_module(ctx, "sys/system.o", &error);
    if(sys == NULL)
    {
        cerr << "Could not find System objects" << endl;
        return 1;
    } else {
        cout << "Found System Implementation" << endl;
    }
    
    Function* cpu_get_pc = cpu->getFunction("cpu_get_pc");
    if(cpu_get_pc == NULL)
    {
        cerr << "Could not find cpu_get_pc" << endl;
        return 1;
    } else {
        cout << "Found getter for CPU Program Counter" << endl;
    }
    
    Module* cacheTemplate = read_module(ctx, "sys/game_template.o", &error);
    if(cacheTemplate == NULL)
    {
        cerr << "Could not find template for game cache" << endl;
    } else {
        cout << "Found game cache" << endl;
    }
    
    // Dig up template for cached instructions
    Function* game_loop = cacheTemplate->getFunction("game_cache");
    if(game_loop == NULL)
    {
        cerr << "Could not find game loop function" << endl;
        return 2;
    } else {
        cout << "Found game loop function" << endl;
    }
    
    cout << "Game loop has " << game_loop->arg_size() << " arguments" << endl;
    const Type* systemType = game_loop->arg_begin()->getType();
    if(systemType == NULL)
    {
        cerr << "Could not find type for game loop's argument";
        return 3;
    } else {
        cout << "Found type for system_t*" << endl;
        systemType->dump();
    }

    const Type* ret = game_loop->getReturnType();
    ret->dump();
    
    // Game Cache function, bool game_cache(state_t* state)
    Module* cache = new Module("Game Cache", ctx);
    Function* f = cast<Function>(cache->getOrInsertFunction("game_cache", Type::getIntNTy(ctx, 1), systemType, NULL));
    Argument* state = f->arg_begin();
    state->setName("state");
    
    BasicBlock* label_entry = BasicBlock::Create(ctx, "entry", f);
    
    // Build cases for switch statement
    // Default: return false (not found)
    BasicBlock* case_default = BasicBlock::Create(ctx, "defaultCase", f);
    ReturnInst::Create(ctx, ConstantInt::get(Type::getInt1Ty(ctx), false), case_default);
    
    // Case 0: Pretend we have a cache hit, and return true
    BasicBlock* case_0 = BasicBlock::Create(ctx, "defaultCase", f);
    // TODO: Call mutator function
    ReturnInst::Create(ctx, ConstantInt::get(Type::getInt1Ty(ctx), true), case_0);
    
    // Assemble the Switch instruction
    SwitchInst* sw = SwitchInst::Create(ConstantInt::get(Type::getInt32Ty(ctx), 0), case_default, 10, label_entry);
    sw->addCase(ConstantInt::get(Type::getInt32Ty(ctx), 0), case_0);
    
    
    
    f->dump();
    verifyFunction(*f);
    
    // TODO Call function
    cout << "Initializing targets..." << endl;
    InitializeAllTargets();
    ExecutionEngine* engine = ExecutionEngine::create(cache);
    if(engine == NULL)
    {
        cerr << "Failed to create engine" << endl;
        return 4;
    } else {
        cout << "Created engine" << endl;
    }
    
    
    // TODO Write module to file
    cout << "done!" << endl;
    return 0;
}