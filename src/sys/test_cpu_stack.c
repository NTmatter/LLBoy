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

#include <stdio.h>
#include <assert.h>
#include "system.h"
#include "mmu_functions.h"
#include "cpu.h"
#include "cpu_functions.h"


int main (int argc, char const *argv[])
{
    printf("Initializing system\n");
    system_t* state = initialize_system();
    
    // Test variables
    printf("Setting up variables\n");
    state->cpu.a = 1; state->cpu.b = 2;
    state->cpu.c = 3; state->cpu.d = 4;
    state->cpu.e = 5; state->cpu.flags = CPU_FLAG_ZERO;
    state->cpu.h = 6; state->cpu.l = 7;
    state->cpu.sp = 0xFFFE;
    
    // Push an item onto the stack, and clear out the registers
    
    // Set up memory
    printf("Setting up memory...\n");
    uint8_t* mem = (uint8_t*) (state->mmu.memory);
    uint16_t m = 0;
    // PUSHAF, PUSHBC
    mem[m++] = 0xF5; mem[m++] = 0xC5;
    // POPAF, POPBC
    mem[m++] = 0xF1; mem[m++] = 0xC1;
    
    // Execute functions (expect 4 calls)
    void (*op)(system_t*);
    printf("Initial State, SP = 0x%04X\n", state->cpu.sp);
    
    // PUSHAF
    cpu_execute(state);
    printf("Executed PUSHAF, SP = 0x%04X\n", state->cpu.sp);
    assert(state->cpu.sp == 0xFFFC);
    assert(mmu_rb(state, 0xFFFD) == 0x01);
    assert(mmu_rb(state, 0xFFFC) == CPU_FLAG_ZERO);
    
    // PUSHBC
    cpu_execute(state);
    printf("Executed PUSHBC, SP = 0x%04X\n", state->cpu.sp);
    assert(state->cpu.sp == 0xFFFA);
    assert(mmu_rb(state, 0xFFFB) == 0x02);
    assert(mmu_rb(state, 0xFFFA) == 0x03);
    
    // POPAF
    cpu_execute(state);
    printf("Executed POPAF, SP = 0x%04X\n", state->cpu.sp);
    assert(state->cpu.sp == 0xFFFC);
    assert(state->cpu.a == 0x02);
    assert(state->cpu.flags == 0x03);
    
    // POPBC
    cpu_execute(state);
    printf("Executed POPBC, SP = 0x%04X\n", state->cpu.sp);
    assert(state->cpu.sp == 0xFFFE);
    assert(state->cpu.b == 0x01);
    assert(state->cpu.c == CPU_FLAG_ZERO);
    
    return 0;
}