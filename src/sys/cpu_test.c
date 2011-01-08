#include <stdio.h>
#include "cpu.h"
#include "cpu_functions.h"

int main(int argc, char** argv)
{
    cpu_hello();
    cpu_t* cpu = initialize_cpu();
    cpu->registers.a = 1;
    return 0;
}