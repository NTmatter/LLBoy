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
#include <stdint.h>
#include <assert.h>
#include "system.h"
#include "cpu_functions.h"
#include "mmu_functions.h"

int main (int argc, char const *argv[])
{
    printf("Initializing system\n");
    system_t* state = initialize_system();
    
    int i = 0;
    const int max_iterations = 100000;
    uint8_t opcode;
    void (*op)(system_t*);
    for(i = 0; i < max_iterations; i++)
    {
        // Fetch op implementation from appropriate table
        opcode = mmu_rb(state, state->cpu.pc);
        printf("Execute 0x%04X: %02X", state->cpu.pc, opcode);
        if(opcode == 0xCB) {
            opcode = mmu_rb(state, ++state->cpu.pc);
            printf("%02X\n", opcode);
            op = cpu_ops_cb[opcode];
        } else {
            op = cpu_ops_basic[opcode];
            printf("\n");
        }
        assert(op != cpu_op_NOP);
        assert(op != cpu_op_undefined);
        assert(op != cpu_op_unimplemented);
        
        cpu_execute(state);
    }
    assert(i < max_iterations);
    return 0;
}