#ifndef __LLGB_CPU_H
#define __LLGB_CPU_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    bool halt;
    bool stop;
    
    uint16_t pc; // Program Counter
    uint16_t sp; // Stack Pointer
    
    struct
    {
        uint8_t a, b, c, d, e; // General-purpose registers
        uint8_t h, l; // General-purpose registers
        uint8_t m; // Cycles for last instruction
        uint8_t f; // Flags
        uint8_t r; // ?
        uint8_t ime; // Interrupt Master Enable
    } registers;
    
    struct
    {
        uint16_t m; // Cycles for last instruction
        uint16_t t; // Total uptime
    } clock;
} cpu_t;

#endif