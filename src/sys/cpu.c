#include <stdio.h>
#include <stdlib.h>
#include <libc.h>

#include "cpu.h"
#include "cpu_functions.h"
#include "mmu_functions.h"
#include "system.h"

#define CPU_OP(name) void cpu_op_##name(system_t* state)

// -- Helper Functions -- //
void cpu_hello()
{
    printf("Greetings from the CPU\n");
}

void cpu_initialize(cpu_t* cpu)
{
    memset(cpu, 0, sizeof(cpu_t));
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
    
    state->cpu.registers.ime = true;
    
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
    state->cpu.registers.pc++;
    state->cpu.registers.m = 1;
}

CPU_OP(halt)
{
    state->cpu.registers.pc++;
    state->cpu.halt = true;
    state->cpu.registers.m = 1;
}

// --- Load/Store operations --- //
// ---- Register-to-Register ---- //
// for to in a b c d e h l; do for from in a b c d e h l; do echo "LDRR($to,$from);"; done; done
#define LDRR(to, from) CPU_OP(LDrr_##to##from)\
{ \
    state->cpu.registers.pc++; \
    state->cpu.registers.to = state->cpu.registers.from; \
    state->cpu.registers.m = 1; \
}

LDRR(a,a); LDRR(a,b); LDRR(a,c); LDRR(a,d); LDRR(a,e); LDRR(a,h); LDRR(a,l);
LDRR(b,a); LDRR(b,b); LDRR(b,c); LDRR(b,d); LDRR(b,e); LDRR(b,h); LDRR(b,l);
LDRR(c,a); LDRR(c,b); LDRR(c,c); LDRR(c,d); LDRR(c,e); LDRR(c,h); LDRR(c,l);
LDRR(d,a); LDRR(d,b); LDRR(d,c); LDRR(d,d); LDRR(d,e); LDRR(d,h); LDRR(d,l);
LDRR(e,a); LDRR(e,b); LDRR(e,c); LDRR(e,d); LDRR(e,e); LDRR(e,h); LDRR(e,l);
LDRR(h,a); LDRR(h,b); LDRR(h,c); LDRR(h,d); LDRR(h,e); LDRR(h,h); LDRR(h,l);
LDRR(l,a); LDRR(l,b); LDRR(l,c); LDRR(l,d); LDRR(l,e); LDRR(l,h); LDRR(l,l);

#undef LDRR

// ---- Load from specified memory location ---- //
#define LDRHLM(to) CPU_OP(LDrHLm_##to) \
{\
    state->cpu.registers.pc++; \
    uint16_t address = state->cpu.registers.h << 8 + state->cpu.registers.l; \
    state->cpu.registers.to = mmu_rb(state, address); \
    state->cpu.registers.m = 2; \
}
LDRHLM(a); LDRHLM(b); LDRHLM(c); LDRHLM(d); LDRHLM(e); LDRHLM(h); LDRHLM(l);
#undef LDRHLM

// ---- Store to memory location specified by HL registers ---- //
#define LDHLMR(from) CPU_OP(LDHLmr_##from)\
{\
    state->cpu.registers.pc++; \
    uint16_t address = state->cpu.registers.h << 8 + state->cpu.registers.l; \
    mmu_wb(state, address, state->cpu.registers.from); \
    state->cpu.registers.m = 2; \
}
LDHLMR(a); LDHLMR(b); LDHLMR(c); LDHLMR(d); LDHLMR(e); LDHLMR(h); LDHLMR(l);
#undef LDHLMR

// --- Load from immediate address --- //
// TODO Immediate-mode version with values embedded in function call
#define LDRN(to) CPU_OP(LDrn_##to) \
{ \
    state->cpu.registers.pc++; \
    uint16_t address = mmu_rb(state, state->cpu.registers.pc++) << 8 + mmu_rb(state, state->cpu.registers.pc++); \
    state->cpu.registers.to = mmu_rb(state, address); \
    state->cpu.registers.m = 2; \
}
LDRN(a); LDRN(b); LDRN(c); LDRN(d); LDRN(e); LDRN(h); LDRN(l);
#undef LDRN


#define SWAPR(reg) CPU_OP(SWAPr_##reg) \
{ \
    state->cpu.registers.pc++; \
    const uint8_t val = state->cpu.registers.reg; \
    state->cpu.registers.reg = ((val & 0xf) << 4) | (val >> 4); \
    state->cpu.registers.m = 1; \
}
SWAPR(a); SWAPR(b); SWAPR(c); SWAPR(d); SWAPR(e); SWAPR(h); SWAPR(l);
#undef SWAPR

// --- Arithmetic Ops --- //
// ---- Addition ---- //
// Single Register
#define ADDR(from) CPU_OP(ADDr_##from) \
{ \
    state->cpu.registers.pc++; \
    const uint8_t from = state->cpu.registers.from; \
    const uint16_t sum = state->cpu.registers.a + from; \
    state->cpu.registers.a += from; \
    state->cpu.registers.flags = ((sum) > 255) ? CPU_FLAG_CARRY : 0; \
    if(state->cpu.registers.a == 0) state->cpu.registers.flags |= CPU_FLAG_ZERO; \
    if((state->cpu.registers.a ^ state->cpu.registers.from) & 0x10) \
        state->cpu.registers.flags |= CPU_FLAG_HALF_CARRY; \
    state->cpu.registers.m = 1; \
}
ADDR(a); ADDR(b); ADDR(c); ADDR(d); ADDR(e); ADDR(h); ADDR(l);
#undef ADDR

#define ADDHLXY(XY, x, y) CPU_OP(ADDHL##XY) \
{ \
    state->cpu.registers.pc++; \
    const uint32_t sum = (state->cpu.registers.h << 8) + state->cpu.registers.l \
        + (state->cpu.registers.x << 8) + state->cpu.registers.y; \
    state->cpu.registers.h = (sum >> 8) & 0xFF; \
    state->cpu.registers.l = sum & 0xFF; \
    state->cpu.registers.m = 3; \
    if(sum > 0xFFFF) \
        state->cpu.registers.flags |= CPU_FLAG_CARRY; \
    else \
        state->cpu.registers.flags &= ~CPU_FLAG_CARRY; \
}
// XXX Is this missing parts of its Flags update?
ADDHLXY(BC, b, c); ADDHLXY(DE, d, e); ADDHLXY(HL, h, l);
#undef ADDHLXY

CPU_OP(ADDHL)
{
    state->cpu.registers.pc++;
    const uint16_t addr = (state->cpu.registers.h << 8) + state->cpu.registers.l;
    const uint8_t augend = state->cpu.registers.a;
    const uint8_t addend = mmu_rb(state, addr);
    const uint16_t sum = augend + addend;
    state->cpu.registers.a += addend;
    
    state->cpu.registers.m = 2;
    state->cpu.registers.flags = 0;
    if(sum > 0xFF) state->cpu.registers.flags |= CPU_FLAG_CARRY;
    if(state->cpu.registers.a == 0) state->cpu.registers.flags |= CPU_FLAG_ZERO;
    if((state->cpu.registers.a ^ augend ^ addend) & 0x10) state->cpu.registers.flags |= CPU_FLAG_HALF_CARRY;
}
#undef CPU_OP