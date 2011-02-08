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
#include "cpu.h"
#include "cpu_functions.h"
#include "system.h"

int main(int argc, char** argv)
{
    system_t* sys = initialize_system();

    // Simple addition
    sys->cpu.a = 1;
    sys->cpu.b = 2;
    sys->cpu.c = 255;
    sys->cpu.d = 14;
    cpu_op_ADDr_b(sys);
    printf("1 + 2 = %d with overflow %s\n",
        sys->cpu.a,
        (sys->cpu.flags & CPU_FLAG_CARRY) ? "true" : "false");
    assert(sys->cpu.a == 3);
    assert(!(sys->cpu.flags & CPU_FLAG_CARRY));
    
    cpu_op_ADDr_c(sys);
    assert(sys->cpu.a == 2);
    assert(sys->cpu.flags & CPU_FLAG_CARRY);
    
    cpu_op_ADDr_d(sys);
    assert(sys->cpu.a == 16);
    assert(sys->cpu.flags & CPU_FLAG_HALF_CARRY);
    
    printf("Final PC: 0x%04x\n", sys->cpu.pc);
    assert(sys->cpu.pc == 3);
    return 0;
}
