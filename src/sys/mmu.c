#include "mmu.h"
#include "mmu_functions.h"

#include <stdint.h>
#include <stdbool.h>
#include <libc.h>
#include "bios.h"

void mmu_initialize(mmu_t* mmu)
{
    mmu->rom_offset = 0x4000;
    mmu->in_bios = true;
    mmu->wram = (uint8_t*) malloc(MMU_WRAM_SIZE);
    mmu->eram = (uint8_t*) malloc(MMU_ERAM_SIZE);
    mmu->zram = (uint8_t*) malloc(MMU_ZRAM_SIZE); // XXX originally 127
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
    
    memset(mmu->wram, 0, MMU_WRAM_SIZE);
    memset(mmu->eram, 0, MMU_ERAM_SIZE);
    memset(mmu->zram, 0, MMU_ZRAM_SIZE); // XXX originally 127
}

uint8_t mmu_read_byte(system_t* state, uint16_t addr)
{
    mmu_t* mmu = &(state->mmu);
    if(mmu->in_bios)
    {
        if(addr < 0x0100)
        {
            return bios[addr];
        } else if(state->cpu.registers.pc >= 0x0100) {
            mmu->in_bios = false;
        }
    }
    
    if(addr < 0x4000)
    {
        return mmu->rom[addr];
    } else if(addr < 0x8000) {
        return mmu->rom[addr & 0x3FFF + mmu->rom_offset];
    } else if(addr < 0xA000) {
        return 0; // TODO return &gpu->vram[addr & 0x1FFF];
    } else if(addr < 0xC000) {
        return mmu->eram[addr & 0x1FFF + mmu->ram_offset];
    } else if(addr < 0xF000) {
        return mmu->wram[addr & 0x1FFF];
    } else if(addr < 0xFF00) {
        // OAM
        // return ((addr & 0xFF) < 0xA0) ? 0 /* &gpu->oam[addr & 0xFF]*/ : 0;
        return 0;
    } else if(addr == 0xFFFF) {
        return mmu->iE;
    } else if(addr > 0xFF7F) {
        return mmu->zram[addr & 0x7F];
    } else if(addr == 0xFF00){
        return 0; // state->key.rb();
    } else if(addr < 0xFF04) {
        return 0;
    } else if(addr < 0xFF08) {
        return 0; // state->timer.rb(addr)
    } else if(addr < 0xFF15) {
        return 0;
    } else if(addr == 0xFF15) {
        return mmu->iF;
    } else if(addr < 0xFF40) {
        return 0;
    } else if(addr < 0xFF80) {
        return 0; // state->gpu.rb(addr);
    } else {
        return 0;
    }
}