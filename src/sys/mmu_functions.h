#ifndef __LLGB_MMU_FUNCTIONS_H
#define __LLGB_MMU_FUNCTIONS_H

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

#include "system.h"
#include "mmu.h"

void mmu_initialize(mmu_t* mmu);
void mmu_reset(system_t* state);

/// Return a pointer to the actual location specified by the address
uint8_t* mmu_map_address(system_t* state, uint16_t address);

/// Find the offset into the memory array that corresponds to the given address,
/// accounting for the current system state, such as being in the BIOS, or 
/// for the currently selected ROM Bank.
uint32_t mmu_memory_offset(system_t* state, uint16_t address);

/// Reads a byte from memory at the given address
uint8_t mmu_rb(system_t* state, uint16_t address);
void mmu_wb(system_t* state, uint16_t address, uint8_t value);

uint16_t mmu_rw(system_t* state, uint16_t address);
void mmu_ww(system_t* state, uint16_t address, uint16_t value);
#endif
