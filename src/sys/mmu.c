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
    mmu->wram = (uint8_t*) malloc(MMU_WRAM_SIZE);
    mmu->eram = (uint8_t*) malloc(MMU_ERAM_SIZE);
    mmu->zram = (uint8_t*) malloc(MMU_ZRAM_SIZE); // XXX originally 127
    
    // This is problematic, as we need to enlarge the memory allocation to fit the banks declared
    // in the cart. See REALLOC.
    // mmu->memory = (uint8_t*) malloc(MMU_BIOS_SIZE);
    mmu->memory = (uint8_t*) calloc(MMU_BIOS_SIZE + 0x10000 + MMU_CART_BANKS * MMU_ROM_BANK_SIZE, 1);
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
    
    memset(mmu->wram, 0, MMU_WRAM_SIZE);
    memset(mmu->eram, 0, MMU_ERAM_SIZE);
    memset(mmu->zram, 0, MMU_ZRAM_SIZE); // XXX originally 127
}

uint32_t mmu_memory_offset(system_t* state, uint16_t addr)
{
    mmu_t* mmu = &(state->mmu);
    if(addr < MMU_BIOS_SIZE && mmu->in_bios)
    {
        return addr;
    } else if(addr == MMU_BIOS_SIZE && mmu->in_bios) {
        mmu->in_bios = false;
        return MMU_BIOS_SIZE + addr;
    } else if(addr < 0x4000) { // Basic ROM bank 0
        return MMU_BIOS_SIZE + addr;
    } else if(addr < 0x8000) { // Currently-selected ROM Bank
        uint32_t current_bank = 1;
        return MMU_BIOS_SIZE + (current_bank - 1) * MMU_ROM_BANK_SIZE + addr;
    } else if(addr < 0xA000) { // GPU VRAM
        return MMU_BIOS_SIZE + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE + addr;
    } else if(addr < 0xC000) { // External RAM
        return MMU_BIOS_SIZE + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE + addr;
    } else if(addr < 0xF000) { // Work RAM and Echo RAM
        return MMU_BIOS_SIZE + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE + 0xE000 + (addr & 0x1FFF);
    } else if(addr < 0xFE00) { // Echo RAM
        return MMU_BIOS_SIZE + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE + 0xE000 + (addr & 0x1FFF);
    } else if(addr < 0xFEA0) { // GPU OAM
        return MMU_BIOS_SIZE + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE + addr;
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
    } else if(addr < 0xFF10) {
        // The interrupt flags
        return MMU_BIOS_SIZE + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE + addr;
    } else if(addr < 0xFF40) {
        // XXX This memory should always return zero
        return -1;
    } else if(addr < 0xFF80) { // GPU
        return MMU_BIOS_SIZE + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE + addr;
    } else if(addr < 0xFFFF) { // ZRAM
        // Normally ANDed with 0x7F
        return -1;
    } else if(addr == 0xFFFF) {
        // Normally MMU._ie
        return MMU_BIOS_SIZE + (MMU_CART_BANKS - 1) * MMU_ROM_BANK_SIZE + addr;
    }
    
    return -1;
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