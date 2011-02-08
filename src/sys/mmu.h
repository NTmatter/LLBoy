#ifndef __LLGB_MMU_H
#define __LLGB_MMU_H

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

#include "bios.h"

#define MMU_BIOS_SIZE 0x100
#define MMU_RAM_BANK_SIZE 0x2000
#define MMU_ROM_BANK_SIZE 0x4000
#define MMU_VRAM_SIZE 0x2000
#define MMU_WRAM_SIZE 0x2000
#define MMU_ERAM_SIZE 0x8000
#define MMU_ZRAM_SIZE 0x80 // XXX 127 in the original implementation

typedef struct {
    uint8_t* memory;
    uint8_t* rom;
    uint8_t cart_type;
    
    // Memory Bank Controller
    struct {
        uint8_t rom_bank;
        uint8_t ram_bank;
        uint8_t ram_on; // Should likely be a boolean, is external RAM enabled?
        uint8_t mode;
        // Some other type?
    } mbc;
    
    uint16_t rom_offset;
    uint16_t ram_offset;
    
    bool in_bios;
    bool iE;
    bool iF;
} mmu_t;
#endif
