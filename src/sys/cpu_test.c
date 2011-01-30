#include <stdio.h>
#include "cpu.h"
#include "cpu_functions.h"
#include "system.h"

int main(int argc, char** argv)
{
    cpu_hello();
    cpu_t* cpu = (cpu_t*) malloc(sizeof(cpu_t));
    cpu_initialize(cpu);
    cpu->a = 1;
    
    void (*op)() = (void (*)()) &cpu_hello;
    op();
    
    system_t* sys = initialize_system();
    void (*nop)(system_t*) = (void (*)(system_t*)) &cpu_op_NOP;
    nop(sys);
    printf("CPU's last instruction time: %d\n", sys->cpu.m);
    
    cpu_reset(sys);
    printf("After reset: %d\n", sys->cpu.m);
    
    // Simple addition
    sys->cpu.a = 1;
    sys->cpu.b = 2;
    sys->cpu.c = 255;
    sys->cpu.d = 14;
    cpu_op_ADDr_b(sys);
    printf("1 + 2 = %d with overflow %s\n",
        sys->cpu.a,
        (sys->cpu.flags & CPU_FLAG_CARRY) ? "true" : "false");
    
    cpu_op_ADDr_c(sys);
    printf("3 + 255 = %d with overflow %s\n",
        sys->cpu.a,
        (sys->cpu.flags & CPU_FLAG_CARRY) ? "true" : "false");
    
    cpu_op_ADDr_d(sys);
    printf("2 + 14 = %d with half-carry %s\n",
        sys->cpu.a,
        (sys->cpu.flags & CPU_FLAG_HALF_CARRY) ? "true" : "false");
    
    printf("Final PC: 0x%04x\n", sys->cpu.pc);
    return 0;
}
