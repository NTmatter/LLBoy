#include <iostream>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/CallingConv.h>

#include <llvm/Target/TargetData.h>
#include <llvm/Target/TargetSelect.h>



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
    
    return 0;
}
