#include "mmu.h"
#include "mmu_functions.h"

#include <stdint.h>
#include <stdbool.h>
#include <libc.h>
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
    memset(state->mmu.wram, 0, MMU_WRAM_SIZE);
    memset(state->mmu.eram, 0, MMU_ERAM_SIZE);
    memset(state->mmu.zram, 0, MMU_ZRAM_SIZE); // XXX originally 127
}