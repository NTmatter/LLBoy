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
    return 0;
}
