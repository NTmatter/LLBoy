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
    
    Function* op_ADDr_b = module_cpu->getFunction("cpu_op_ADDr_b");
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
    state->cpu.registers.a = 1;
    state->cpu.registers.b = 2;
    void (*ADDr_b)(system_t*) = (void (*)(system_t*)) p_ADDr_b;
    ADDr_b(state);
    cout << "Executing function 1 + 2 = " << (int)(state->cpu.registers.a) << endl;
    
    return 0;
}
