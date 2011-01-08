#ifndef __LLGB_CPU_H
#define __LLGB_CPU_H

#include <stdint.h>
#include <stdbool.h>

#define CPU_FLAG_ZERO 0x80
#define CPU_FLAG_OPERATION 0x40
#define CPU_FLAG_HALF_CARRY 0x20
#define CPU_FLAG_CARRY 0x10

typedef struct
{
    bool halt;
    bool stop;
    
    struct
    {
        uint8_t a, b, c, d, e; // General-purpose registers
        uint8_t h, l; // General-purpose registers (commonly for address registers)
        uint8_t m; // Cycles for last instruction
        uint8_t flags; // Flags
        uint8_t i; // ?
        uint8_t r; // ? & 127
        uint8_t ime; // Interrupt Master Enable
        
        uint16_t pc; // Program Counter
        uint16_t sp; // Stack Pointer
    } registers;
    
    struct
    {
        uint8_t a, b, c, d, e, h, l, flags;
    } saved_registers;
    
    struct
    {
        uint16_t m; // Total uptime
    } clock;
} cpu_t;

#endif