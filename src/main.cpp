#include <iostream>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Bitcode/ReaderWriter.h>


using namespace std;
using namespace llvm;

Module* read_module(LLVMContext* ctx, string path, string* error)
{
    MemoryBuffer* buffer;
    Module* out = NULL;
    if((buffer = MemoryBuffer::getFile(path, error)))
    {
        out = ParseBitcodeFile(buffer, *ctx);
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
    Module* module_mmu = NULL;
    Module* module_system = read_module(context, "sys/system.o", &error);
    cout << "Complete." << endl;
    
    return 0;
}
