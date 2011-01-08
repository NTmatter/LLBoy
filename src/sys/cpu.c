#include <stdio.h>
#include <stdlib.h>
#include <libc.h>
#include "cpu.h"

cpu_t* initialize_cpu() {
    cpu_t* cpu = malloc(sizeof(cpu_t));
    bzero(cpu, sizeof(cpu_t));
    return cpu;
}

void cpu_hello() {
    printf("Greetings from the CPU\n");
}