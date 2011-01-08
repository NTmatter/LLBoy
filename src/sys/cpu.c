#include <stdio.h>
#include <stdlib.h>
#include <libc.h>
#include "cpu.h"

cpu_t* initialize_cpu() {
    cpu_t* cpu = malloc(sizeof(cpu_t));
    bzero(cpu, sizeof(cpu_t));
    return cpu;
}

void reset_cpu(cpu_t* cpu) {
    cpu->pc = 0;
    cpu->sp = 0;
    cpu->registers.a = 0;
    cpu->registers.b = 0;
    cpu->registers.c = 0;
    cpu->registers.d = 0;
    cpu->registers.e = 0;
    cpu->registers.h = 0;
    cpu->registers.l = 0;
    cpu->halt = false;
    cpu->stop = false;
    cpu->clock.m = 0;
}

void cpu_nop(cpu_t* cpu) {
    cpu->clock.m = 1;
    cpu->clock.t += 4;
}

void cpu_hello() {
    printf("Greetings from the CPU\n");
}