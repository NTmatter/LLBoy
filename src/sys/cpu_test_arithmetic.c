#include <stdio.h>
#include <assert.h>
#include "cpu.h"
#include "cpu_functions.h"
#include "system.h"

int main(int argc, char** argv)
{
    system_t* sys = initialize_system();

    // Simple addition
    sys->cpu.a = 1;
    sys->cpu.b = 2;
    sys->cpu.c = 255;
    sys->cpu.d = 14;
    cpu_op_ADDr_b(sys);
    printf("1 + 2 = %d with overflow %s\n",
        sys->cpu.a,
        (sys->cpu.flags & CPU_FLAG_CARRY) ? "true" : "false");
    assert(sys->cpu.a == 3);
    assert(!(sys->cpu.flags & CPU_FLAG_CARRY));
    
    cpu_op_ADDr_c(sys);
    assert(sys->cpu.a == 2);
    assert(sys->cpu.flags & CPU_FLAG_CARRY);
    
    cpu_op_ADDr_d(sys);
    assert(sys->cpu.a == 16);
    assert(sys->cpu.flags & CPU_FLAG_HALF_CARRY);
    
    printf("Final PC: 0x%04x\n", sys->cpu.pc);
    assert(sys->cpu.pc == 3);
    return 0;
}
