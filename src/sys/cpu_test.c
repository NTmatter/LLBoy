#include <stdio.h>
#include "cpu.h"
#include "cpu_functions.h"
#include "system.h"

int main(int argc, char** argv)
{
    cpu_hello();
    cpu_t* cpu = initialize_cpu();
    cpu->registers.a = 1;
    
    void (*op)() = (void (*)()) &cpu_hello;
    op();
    
    system_t* sys = initialize_system();
    void (*nop)(system_t*) = (void (*)(system_t*)) &cpu_op_nop;
    nop(sys);
    printf("CPU's last instruction time: %d\n", sys->cpu.registers.m);
    
    cpu_reset(sys);
    printf("After reset: %d\n", sys->cpu.registers.m);
    return 0;
}