#include <stdio.h>
#include <stdlib.h>
#include <libc.h>

#include "cpu.h"
#include "cpu_functions.h"
#include "system.h"

#define FLAG_ZERO 0x80
#define FLAG_OPERATION 0x40
#define FLAG_HALF_CARRY 0x20
#define FLAG_CARRY 0x10

cpu_t* initialize_cpu() {
    cpu_t* cpu = malloc(sizeof(cpu_t));
    bzero(cpu, sizeof(cpu_t));
    return cpu;
}

void reset_cpu(system_t* state) {
    state->cpu.pc = 0;
    state->cpu.sp = 0;
    state->cpu.registers.a = 0;
    state->cpu.registers.b = 0;
    state->cpu.registers.c = 0;
    state->cpu.registers.d = 0;
    state->cpu.registers.e = 0;
    state->cpu.registers.h = 0;
    state->cpu.registers.l = 0;
    state->cpu.halt = false;
    state->cpu.stop = false;
    state->cpu.clock.m = 0;
}

void cpu_nop(system_t* state) {
    state->cpu.clock.m = 1;
    state->cpu.clock.t += 4;
}

void cpu_hello() {
    printf("Greetings from the CPU\n");
}

#undef FLAG_ZERO
#undef FLAG_OPERATION
#undef FLAG_HALF_CARRY
#undef FLAG_CARRY