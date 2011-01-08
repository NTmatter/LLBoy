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

// -- Helper Functions -- //

cpu_t* initialize_cpu()
{
    cpu_t* cpu = malloc(sizeof(cpu_t));
    bzero(cpu, sizeof(cpu_t));
    return cpu;
}

void reset_cpu(system_t* state)
{
    state->cpu.registers.pc = 0;
    state->cpu.registers.sp = 0;
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

void cpu_rsv(system_t* state)
{
    state->cpu.saved_registers.a = state->cpu.registers.a;
    state->cpu.saved_registers.b = state->cpu.registers.b;
    state->cpu.saved_registers.c = state->cpu.registers.c;
    state->cpu.saved_registers.d = state->cpu.registers.d;
    state->cpu.saved_registers.e = state->cpu.registers.e;
    state->cpu.saved_registers.h = state->cpu.registers.h;
    state->cpu.saved_registers.l = state->cpu.registers.l;
    
    state->cpu.saved_registers.flags = state->cpu.registers.flags;
}

void cpu_rrs(system_t* state)
{
    state->cpu.registers.a = state->cpu.saved_registers.a;
    state->cpu.registers.b = state->cpu.saved_registers.b;
    state->cpu.registers.c = state->cpu.saved_registers.c;
    state->cpu.registers.d = state->cpu.saved_registers.d;
    state->cpu.registers.e = state->cpu.saved_registers.e;
    state->cpu.registers.h = state->cpu.saved_registers.h;
    state->cpu.registers.l = state->cpu.saved_registers.l;
    
    state->cpu.registers.flags = state->cpu.saved_registers.flags;
}


// -- Ops -- //
void cpu_op_undefined(system_t* state)
{
    printf("Hit unimplemented or unknown instruction $%x", state->cpu.registers.pc);
    state->cpu.stop = true;
}

void cpu_op_nop(system_t* state)
{
    state->cpu.clock.m = 1;
}

void cpu_hello()
{
    printf("Greetings from the CPU\n");
}

#undef FLAG_ZERO
#undef FLAG_OPERATION
#undef FLAG_HALF_CARRY
#undef FLAG_CARRY