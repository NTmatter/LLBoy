#ifndef __LLGB_CPU_H
#define __LLGB_CPU_H

// Copyright (c) 2011 Thomas Johnson
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


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
    
    uint8_t a, b, c, d, e; // General-purpose registers
    uint8_t h, l; // General-purpose registers (commonly for address registers)
    uint8_t m; // Cycles for last instruction
    uint8_t flags; // Flags - http://gbdev.gg8.se/wiki/articles/CPU_Registers_and_Flags
    uint8_t i; // ?
    uint8_t r; // ? & 127
    bool ime; // Interrupt Master Enable
    
    uint16_t pc; // Program Counter
    uint16_t sp; // Stack Pointer
    
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
