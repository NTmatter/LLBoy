#ifndef __CPU_H
#define __CPU_H

#include <stdint.h>
#include <stdbool.h>

#define FLAG_ZERO 0x80
#define FLAG_OPERATION 0x40
#define FLAG_HALF_CARRY 0x20
#define FLAG_CARRY 0x10

typedef struct cpu
{
    bool halt;
    bool stop;
    
    uint16_t pc; // Program Counter
    uint16_t sp; // Stack Pointer
    
    struct regs {
        uint8_t a, b, c, d, e; // General-purpose registers
        uint8_t h, l; // General-purpose registers
        uint8_t m; // Cycles for last instruction
        uint8_t f; // Flags
        uint8_t r; // ?
        uint8_t ime; // Interrupt Master Enable
    } registers;
    
    struct clk {
        uint16_t m; // Cycles for last instruction
        uint16_t t; // Total uptime
    } clock;
} cpu_t;

/// Returns a freshly-initialized CPU structure
cpu_t* initialize_cpu();

void reset_cpu(cpu_t* cpu);

void cpu_nop(cpu_t* cpu);
/// Prints a simple Hello World
void cpu_hello();

#undef FLAG_ZERO
#undef FLAG_OPERATION
#undef FLAG_HALF_CARRY
#undef FLAG_CARRY
#endif