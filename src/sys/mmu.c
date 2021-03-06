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


#include "mmu.h"
#include "mmu_functions.h"

#include <stdint.h>
#include <stdbool.h>
#include <libc.h>
#include "bios.h"

// TODO This should be dynamically determined based upon the number of banks in the cart.
#define MMU_CART_BANKS 1 // Includes the basic bank 1.

void mmu_initialize(mmu_t* mmu)
{
    mmu->rom_offset = 0x4000;
    mmu->in_bios = true;
    
    // This is problematic, as we need to enlarge the memory allocation to fit the banks declared
    // in the cart. See REALLOC.
    // mmu->memory = (uint8_t*) malloc(MMU_BIOS_SIZE);
    mmu->memory = (uint8_t*) calloc(MMU_BIOS_SIZE + 0x10000 + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE, 1);
    memcpy(mmu->memory, bios, MMU_BIOS_SIZE);
}

void mmu_reset(system_t* state)
{
    mmu_t* mmu = &(state->mmu);
    
    mmu->in_bios = true;
    mmu->iE = 0;
    mmu->iF = 0;
    
    mmu->cart_type = 0;
    mmu->ram_offset = 0;
    mmu->rom_offset = 0x4000;
}

uint32_t mmu_memory_offset(system_t* state, uint16_t addr)
{
    mmu_t* mmu = &(state->mmu);
    if(mmu->in_bios && addr < MMU_BIOS_SIZE)
    {
        return addr;
    } else if(addr < 0x4000) { // Basic ROM bank 0
        return MMU_BIOS_SIZE + addr;
    } else if(addr < 0x8000) { // ROM Bank 1 or other
        uint32_t current_bank = 1;
        return MMU_BIOS_SIZE + current_bank * MMU_ROM_BANK_SIZE + addr;
    } else if(addr < 0xA000) { // GPU VRAM
        return MMU_BIOS_SIZE + MMU_CART_BANKS * MMU_ROM_BANK_SIZE + addr;
    } else if(addr < 0xC000) { // External RAM
        return MMU_BIOS_SIZE + MMU_CART_BANKS * MMU_ROM_BANK_SIZE + addr;
    } else if(addr < 0xF000) { // Work RAM and Echo RAM
        return MMU_BIOS_SIZE + MMU_CART_BANKS * MMU_ROM_BANK_SIZE + 0xC000 + (addr & 0x1FFF);
    } else if(addr < 0xFE00) { // Echo RAM
        return MMU_BIOS_SIZE + MMU_CART_BANKS * MMU_ROM_BANK_SIZE + 0xC000 + (addr & 0x1FFF);
    } else if(addr < 0xFEA0) { // GPU OAM
        return MMU_BIOS_SIZE + MMU_CART_BANKS * MMU_ROM_BANK_SIZE + addr;
    } else if(addr < 0xFF00) {
        // XXX This memory should always return zero (?) Could be audio controls...
        return -1;
    } else if(addr == 0xFF00) { // Joypad state
        return MMU_BIOS_SIZE + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE + addr;
    } else if (addr < 0xFF04) {
        // XXX This memory should always return zero
        return -1;
    } else if(addr < 0xFF08) {
        // Timer
        return MMU_BIOS_SIZE + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE + addr;
    } else if(addr < 0xFF0F) {
        // XXX This memory should always return zero
        return -1;
    } else if(addr == 0xFF0F) {
        // The interrupt flags
        return MMU_BIOS_SIZE + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE + addr;
    } else if(addr < 0xFF40) {
        // XXX This memory should always return zero
        return -1;
    } else if(addr < 0xFF80) { // GPU
        return MMU_BIOS_SIZE + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE + addr;
    } else if(addr < 0xFFFF) { // ZRAM
        return MMU_BIOS_SIZE + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE + addr;
    } else if(addr == 0xFFFF) {
        // Normally MMU._ie
        return MMU_BIOS_SIZE + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE + addr;
    }
    
    return -1;
}

uint8_t mmu_rb(system_t* state, uint16_t addr)
{
    if(state->mmu.in_bios && state->cpu.pc >= 0x0100) {
        state->mmu.in_bios = false;
    }
    
    // Certain areas of ZRAM should always return zero
    if((addr >= 0xFEA0 && addr < 0xFF00) || (addr >= 0xFF01 && addr < 0xFF04)
        || (addr >= 0xFF08 && addr < 0xFF0F) || (addr >= 0xFF10 && addr < 0xFF40))
    {
        return 0;
    }
    
    uint32_t index = mmu_memory_offset(state, addr);
    if(index == -1)
    {
        printf("Attempted to read unimplemented memory segment 0x%04x\n", addr);
        return -1;
    }
    return state->mmu.memory[index];
}

uint16_t mmu_rw(system_t* state, uint16_t addr)
{
    return mmu_rb(state, addr) + (mmu_rb(state, addr + 1) << 8);
}

void mmu_wb(system_t* state, uint16_t addr, uint8_t val)
{
    mmu_t* mmu = &(state->mmu);
    
    uint32_t index = mmu_memory_offset(state, addr);
    if(index == -1)
    {
        printf("Attempted to write to unimplemented memory segment 0x%04x\n", addr);
        return;
    }
    
    if(addr < 0x2000) { // ROM Bank 0, activate external RAM
        if(mmu->cart_type == 1)
        {
            mmu->mbc.ram_on = ((val & 0xF) == 0xA) ? 1 : 0;
        }
        return;
    } else if(addr < 0x4000) { // ROM bank switch (1-32)
        if(mmu->cart_type == 1)
        {
            // Clamp to 1-32 banks
            val &= 0x1F;
            if(!val) val = 1;
            
            // Update the lower bits of the ROM bank
            mmu->mbc.rom_bank &= 0x60;
            mmu->mbc.rom_bank |= val;
            mmu->rom_offset = mmu->mbc.rom_bank * MMU_ROM_BANK_SIZE;
        }
        return;
    } else if(addr < 0x6000) {
        if(mmu->cart_type == 1)
        {
            mmu->mbc.ram_bank = val & 3;
            mmu->ram_offset = mmu->mbc.ram_bank * MMU_RAM_BANK_SIZE;
        } else {
            mmu->mbc.rom_bank &= 0x1F;
            mmu->mbc.rom_bank |= ((val & 3) << 5);
            mmu->rom_offset = mmu->mbc.rom_bank * MMU_ROM_BANK_SIZE;
        }
        return;
    } else if(addr < 0x8000) {
        if(mmu->cart_type == 1)
        {
            mmu->mbc.mode = val & 1;
        }
        return;
    } else if(addr < 0xA000) { // VRAM
        state->mmu.memory[index] = val;
        // TODO Trigger GPU Tile updates
        return;
    } else if(addr < 0xC000) { // External RAM
        // TODO Write to ERAM at suggested address, needs additional paging?
        state->mmu.memory[index] = val; // XXX this may require changes to mmu_memory_offset
    } else if(addr < 0xFE00) {
        state->mmu.memory[index] = val;
    } else if(addr < 0xFEA0) { // Graphics OAM modify
        state->mmu.memory[index] = val;
        // TODO GPU.updateoam(addr, val)
        return;
    } else if(addr < 0xFF00) {  // Graphics OAM update only
        // TODO GPU.updateoam(addr, val)
        return;
    } else if(addr == 0xFFFF) {
        mmu->iE = val;
        return;
    }
    
    // Write to memory unless explicitly consumed
    state->mmu.memory[index] = val;
}

void mmu_ww(system_t* state, uint16_t addr, uint16_t val)
{
    mmu_wb(state, addr, val & 0xFF);
    mmu_wb(state, addr + 1, val >> 8);
}
