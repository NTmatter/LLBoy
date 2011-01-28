#include <stdio.h>
#include <stdint.h>
#include "system.h"
#include "mmu.h"
#include "mmu_functions.h"

/// Iterates over all memory to ensure that there are no gaps
int main (int argc, char const *argv[])
{
    system_t* state = initialize_system();
    uint16_t i = 0;
    do {
        if(i % 0x100 == 0) {
            printf("Reading 0x%04x...\n", i);
        }
        uint32_t index = mmu_memory_offset(state, i);
        if(index < 0) {
            printf("Hit unimplemented memory at 0x%04x\n", i);
            return 1;
        }
    } while(i++ != 0xFFFF);
    
    return 0;
}