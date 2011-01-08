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

#define CPU_OP(name) void cpu_op_##name(system_t* state)

// -- Helper Functions -- //
void cpu_hello()
{
    printf("Greetings from the CPU\n");
}

cpu_t* initialize_cpu()
{
    cpu_t* cpu = malloc(sizeof(cpu_t));
    bzero(cpu, sizeof(cpu_t));
    return cpu;
}

void cpu_reset(system_t* state)
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
    
    state->cpu.registers.m = 0;
    
    state->cpu.registers.ime = 1;
    
    state->cpu.clock.m = 0;
    
    state->cpu.halt = false;
    state->cpu.stop = false;
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

/// Execute an instruction
/// Core of Fetch/Decode/Execute loop
/// This should probably be absorbed into the code generator
void cpu_exec(system_t* state)
{
    state->cpu.registers.r++;
    state->cpu.registers.r &= 127;
    // Fetch instruction from memory
    // uint8_t opcode = state->mmu.rb(state->cpu.pc++);
    // Fetch op implementation from table
    void (*op)(system_t* state) = 0;
    // execute op
    op(state);
    state->cpu.clock.m += state->cpu.registers.m;
}

// -- Ops -- //
void cpu_op_undefined(system_t* state)
{
    printf("Hit unimplemented or unknown instruction $%x", state->cpu.registers.pc);
    state->cpu.stop = true;
}

CPU_OP(nop)
{
    state->cpu.registers.m = 1;
}

CPU_OP(halt)
{
    state->cpu.halt = true;
    state->cpu.registers.m = 1;
}

#undef FLAG_ZERO
#undef FLAG_OPERATION
#undef FLAG_HALF_CARRY
#undef FLAG_CARRY
#undef CPU_OP