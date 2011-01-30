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
    state->cpu.pc = 0;
    state->cpu.sp = 0;
    
    state->cpu.a = 0;
    state->cpu.b = 0;
    state->cpu.c = 0;
    state->cpu.d = 0;
    state->cpu.e = 0;
    
    state->cpu.h = 0;
    state->cpu.l = 0;
    
    state->cpu.m = 0;
    
    state->cpu.ime = true;
    
    state->cpu.clock.m = 0;
    
    state->cpu.halt = false;
    state->cpu.stop = false;
}

void cpu_rsv(system_t* state)
{
    state->cpu.saved_registers.a = state->cpu.a;
    state->cpu.saved_registers.b = state->cpu.b;
    state->cpu.saved_registers.c = state->cpu.c;
    state->cpu.saved_registers.d = state->cpu.d;
    state->cpu.saved_registers.e = state->cpu.e;
    state->cpu.saved_registers.h = state->cpu.h;
    state->cpu.saved_registers.l = state->cpu.l;
    
    state->cpu.saved_registers.flags = state->cpu.flags;
}

void cpu_rrs(system_t* state)
{
    state->cpu.a = state->cpu.saved_registers.a;
    state->cpu.b = state->cpu.saved_registers.b;
    state->cpu.c = state->cpu.saved_registers.c;
    state->cpu.d = state->cpu.saved_registers.d;
    state->cpu.e = state->cpu.saved_registers.e;
    state->cpu.h = state->cpu.saved_registers.h;
    state->cpu.l = state->cpu.saved_registers.l;
    
    state->cpu.flags = state->cpu.saved_registers.flags;
}

/// Execute an instruction
/// Core of Fetch/Decode/Execute loop
/// This should probably be absorbed into the code generator
void cpu_exec(system_t* state)
{
    state->cpu.r++;
    state->cpu.r &= 0x7F; 
    // Fetch instruction from memory
    // uint8_t opcode = state->mmu.rb(state->cpu.pc++);
    // Fetch op implementation from table
    void (*op)(system_t* state) = 0;
    // execute op
    op(state);
    state->cpu.clock.m += state->cpu.m;
}

// -- Ops -- //
void cpu_op_undefined(system_t* state)
{
    printf("Hit unknown instruction $%x", state->cpu.pc);
    state->cpu.stop = true;
}

void cpu_op_unimplemented(system_t* state)
{
    printf("Hit unimplemented instruction 0x%02x at 0x%04x\n",
        mmu_rb(state, state->cpu.pc), state->cpu.pc);
    state->cpu.halt = true;
}

CPU_OP(NOP)
{
    state->cpu.pc++;
    state->cpu.m = 1;
}

CPU_OP(HALT)
{
    state->cpu.pc++;
    state->cpu.halt = true;
    state->cpu.m = 1;
}

// --- Load/Store operations --- //
// ---- Register-to-Register ---- //
// for to in a b c d e h l; do for from in a b c d e h l; do echo "LDRR($to,$from);"; done; done
#define LDRR(to, from) CPU_OP(LDrr_##to##from)\
{ \
    state->cpu.pc++; \
    state->cpu.to = state->cpu.from; \
    state->cpu.m = 1; \
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
    state->cpu.pc++; \
    uint16_t address = state->cpu.h << 8 + state->cpu.l; \
    state->cpu.to = mmu_rb(state, address); \
    state->cpu.m = 2; \
}
LDRHLM(a); LDRHLM(b); LDRHLM(c); LDRHLM(d); LDRHLM(e); LDRHLM(h); LDRHLM(l);
#undef LDRHLM

// ---- Store to memory location specified by HL registers ---- //
#define LDHLMR(from) CPU_OP(LDHLmr_##from)\
{\
    state->cpu.pc++; \
    uint16_t address = state->cpu.h << 8 + state->cpu.l; \
    mmu_wb(state, address, state->cpu.from); \
    state->cpu.m = 2; \
}
LDHLMR(a); LDHLMR(b); LDHLMR(c); LDHLMR(d); LDHLMR(e); LDHLMR(h); LDHLMR(l);
#undef LDHLMR

// --- Load from immediate address --- //
// TODO Immediate-mode version with values embedded in function call
#define LDRN(to) CPU_OP(LDrn_##to) \
{ \
    state->cpu.pc++; \
    uint16_t address = mmu_rb(state, state->cpu.pc++) << 8 + mmu_rb(state, state->cpu.pc++); \
    state->cpu.to = mmu_rb(state, address); \
    state->cpu.m = 2; \
}
LDRN(a); LDRN(b); LDRN(c); LDRN(d); LDRN(e); LDRN(h); LDRN(l);
#undef LDRN


#define SWAPR(reg) CPU_OP(SWAPr_##reg) \
{ \
    state->cpu.pc++; \
    const uint8_t val = state->cpu.reg; \
    state->cpu.reg = ((val & 0xf) << 4) | (val >> 4); \
    state->cpu.m = 1; \
}
SWAPR(a); SWAPR(b); SWAPR(c); SWAPR(d); SWAPR(e); SWAPR(h); SWAPR(l);
#undef SWAPR

// --- Arithmetic Ops --- //
// ---- Addition ---- //
// Single Register
#define ADDR(from) CPU_OP(ADDr_##from) \
{ \
    state->cpu.pc++; \
    const uint8_t from = state->cpu.from; \
    const uint16_t sum = state->cpu.a + from; \
    state->cpu.a += from; \
    state->cpu.flags = ((sum) > 255) ? CPU_FLAG_CARRY : 0; \
    if(state->cpu.a == 0) state->cpu.flags |= CPU_FLAG_ZERO; \
    if((state->cpu.a ^ state->cpu.from) & 0x10) \
        state->cpu.flags |= CPU_FLAG_HALF_CARRY; \
    state->cpu.m = 1; \
}
ADDR(a); ADDR(b); ADDR(c); ADDR(d); ADDR(e); ADDR(h); ADDR(l);
#undef ADDR

#define ADDHLXY(XY, x, y) CPU_OP(ADDHL##XY) \
{ \
    state->cpu.pc++; \
    const uint32_t sum = (state->cpu.h << 8) + state->cpu.l \
        + (state->cpu.x << 8) + state->cpu.y; \
    state->cpu.h = (sum >> 8) & 0xFF; \
    state->cpu.l = sum & 0xFF; \
    state->cpu.m = 3; \
    if(sum > 0xFFFF) \
        state->cpu.flags |= CPU_FLAG_CARRY; \
    else \
        state->cpu.flags &= ~CPU_FLAG_CARRY; \
}
ADDHLXY(BC, b, c); ADDHLXY(DE, d, e); ADDHLXY(HL, h, l);
#undef ADDHLXY

CPU_OP(ADDHL)
{
    state->cpu.pc++;
    const uint16_t addr = (state->cpu.h << 8) + state->cpu.l;
    const uint8_t augend = state->cpu.a;
    const uint8_t addend = mmu_rb(state, addr);
    const uint16_t sum = augend + addend;
    state->cpu.a += addend;
    
    state->cpu.m = 2;
    state->cpu.flags = 0;
    if(sum > 0xFF) state->cpu.flags |= CPU_FLAG_CARRY;
    if(state->cpu.a == 0) state->cpu.flags |= CPU_FLAG_ZERO;
    if((state->cpu.a ^ augend ^ addend) & 0x10) state->cpu.flags |= CPU_FLAG_HALF_CARRY;
}

// -- Control Flow -- //
/// CALLnn Unconditional Branch
CPU_OP(CALLnn)
{
    state->cpu.pc++;
    state->cpu.m = 5;
    
    // Consume argument
    const uint16_t target = mmu_rw(state, state->cpu.pc);
    state->cpu.pc += 2;
    
    // Store return location
    state->cpu.sp -= 2;
    mmu_ww(state, state->cpu.sp, state->cpu.pc);
    
    // Set Jump Target
    state->cpu.pc = target;
}

/// RET Unconditional Return
CPU_OP(RET)
{
    state->cpu.pc++;
    state->cpu.m = 3;
    state->cpu.pc = mmu_rw(state, state->cpu.sp);
    state->cpu.sp += 2;
}

// -- Comparison -- //
#define CPR(r) CPU_OP(CPr_##r)\
{\
    state->cpu.pc++; \
    state->cpu.m = 1; \
    const uint8_t i = state->cpu.a; \
    const uint8_t m = state->cpu.r; \
    state->cpu.a -= m; \
    state->cpu.flags = CPU_FLAG_OPERATION; \
    if(m > i) state->cpu.flags |= CPU_FLAG_CARRY; \
    if(m == i) state->cpu.flags |= CPU_FLAG_ZERO; \
    if((state->cpu.a^i^m) & 0x10) state->cpu.flags |= CPU_FLAG_HALF_CARRY; \
}

CPR(b); CPR(c); CPR(d); CPR(e); CPR(h); CPR(l); CPR(a);

#undef CPR

CPU_OP(CPHL)
{
    state->cpu.pc++;
    state->cpu.m = 2;
    const uint8_t i = state->cpu.a;
    const uint8_t m = mmu_rb(state, (state->cpu.h << 8) + state->cpu.l);
    state->cpu.a -= m;
    
    // Update Flags
    state->cpu.flags = CPU_FLAG_OPERATION;
    if(m > i) state->cpu.flags |= CPU_FLAG_CARRY;
    if(m == i) state->cpu.flags |= CPU_FLAG_ZERO;
    if((state->cpu.a^i^m) & 0x10) state->cpu.flags |= CPU_FLAG_HALF_CARRY;
}

CPU_OP(CPn)
{
    state->cpu.pc++;
    state->cpu.m = 2;
    const uint8_t i = state->cpu.a;
    const uint8_t m = mmu_rb(state, state->cpu.pc++);
    state->cpu.a -= m;
    
    // Update Flags
    state->cpu.flags = CPU_FLAG_OPERATION;
    if(m > i) state->cpu.flags |= CPU_FLAG_CARRY;
    if(m == i) state->cpu.flags |= CPU_FLAG_ZERO;
    if((state->cpu.a^i^m) & 0x10) state->cpu.flags |= CPU_FLAG_HALF_CARRY;
}

// -- CB Ops -- //
// --- Bit Queries --- //
#define BITnr(n, r) CPU_OP(BIT##n##r) \
{ \
    state->cpu.pc += 2; \
    state->cpu.flags = \
        (state->cpu.r & (1 << n)) ? 0 : CPU_FLAG_ZERO; \
        state->cpu.m = 2; \
}
#define BITnm(n) CPU_OP(BIT##n##m) \
{ \
    state->cpu.pc += 2; \
    const uint16_t addr = (state->cpu.h << 8) + state->cpu.l; \
    state->cpu.flags = \
        (mmu_rb(state, addr) & (1 << n)) ? 0 : CPU_FLAG_ZERO; \
        state->cpu.m = 3; \
}

#define BIT(n) \
BITnr(n,b); BITnr(n,c); BITnr(n,d); BITnr(n,e); \
BITnr(n,h); BITnr(n,l); BITnm(n); BITnr(n,a);

BIT(0); BIT(1); BIT(2); BIT(3); BIT(4); BIT(5); BIT(6); BIT(7);

#undef BITnr
#undef BITnm
#undef BITn
#undef CPU_OP
