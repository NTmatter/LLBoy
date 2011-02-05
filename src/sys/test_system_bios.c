#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "system.h"
#include "cpu_functions.h"
#include "mmu_functions.h"

int main (int argc, char const *argv[])
{
    printf("Initializing system\n");
    system_t* state = initialize_system();
    
    int i = 0;
    const int max_iterations = 100000;
    uint8_t opcode;
    void (*op)(system_t*);
    for(i = 0; i < max_iterations; i++)
    {
        // Fetch op implementation from appropriate table
        opcode = mmu_rb(state, state->cpu.pc);
        printf("Execute 0x%04X: %02X", state->cpu.pc, opcode);
        if(opcode == 0xCB) {
            opcode = mmu_rb(state, ++state->cpu.pc);
            printf("%02X\n", opcode);
            op = cpu_ops_cb[opcode];
        } else {
            op = cpu_ops_basic[opcode];
            printf("\n");
        }
        assert(op != cpu_op_NOP);
        assert(op != cpu_op_undefined);
        assert(op != cpu_op_unimplemented);
        
        cpu_execute(state);
    }
    assert(i < max_iterations);
    return 0;
}