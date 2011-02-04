#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "system.h"
#include "cpu_functions.h"

int main (int argc, char const *argv[])
{
    printf("Initializing system\n");
    system_t* state = initialize_system();
    
    // Test variables
    printf("Setting up variables\n");
    state->cpu.a = 1;
    state->cpu.b = 2;
    state->cpu.sp = 0xFFFE;
    
    // Set up memory
    printf("Setting up memory\n");
    uint8_t* mem = (uint8_t*) (state->mmu.memory);
    uint16_t m = 0;
    // CALLnn 0x100
    mem[m++] = 0xCD; mem[m++] = 0x50; mem[m++] = 0;
    // ADDr_b
    mem[m = 0x50] = 0x80;
    // RET
    mem[m = 0x51] = 0xC9;
    
    // Execute functions (expect 3 calls)
    void (*op)(system_t*);
    
    // CALLnn function at 0x0050
    cpu_execute(state);
    printf("Executed CALLnn, PC = 0x%04x\n", state->cpu.pc);
    assert(state->cpu.pc == 0x50);
    
    // ADDr_b, a := a + b = 1 + 2 = 3
    cpu_execute(state);
    printf("Executed ADDr_b, PC = 0x%04x\n", state->cpu.pc);
    assert(state->cpu.a == 0x03);
    
    // RET, back to 0x03 after the CALLnn and arguments
    cpu_execute(state);
    printf("Executed RET, PC = 0x%04x\n", state->cpu.pc);
    assert(state->cpu.pc == 0x03);
    
    // Result should still be 3
    assert(state->cpu.a == 3);
    return 0;
}
