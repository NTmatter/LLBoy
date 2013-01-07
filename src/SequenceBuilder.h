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

#import "cart_metadata.h"
#import "sys/system.h"
#import <string.h>
#import <llvm/LLVMContext.h>
#import <llvm/Module.h>

using namespace llvm;

class SequenceBuilder {
public:
    /// Read a module from the specified path
    static Module* readModule(LLVMContext* ctx, std::string path, std::string moduleName);
    
    /// Builds a module with a uint32_t play(system_t* sys) function
    static void buildFromCart(Module* base, system_t* sys);
    
    /// Runs optimization passes on the supplied module
    static void optimize(Module* mod);
};