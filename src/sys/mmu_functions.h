#ifndef __LLGB_MMU_FUNCTIONS_H
#define __LLGB_MMU_FUNCTIONS_H

#include <stdint.h>

#include "system.h"
#include "mmu.h"

#define MMU_WRAM_SIZE 8192
#define MMU_ERAM_SIZE 32768
#define MMU_ZRAM_SIZE 128 // XXX 127 in the original implementation

void mmu_initialize(mmu_t* mmu);
void mmu_reset(system_t* state);

uint8_t mmu_read_byte(system_t* state, uint16_t address);
void mmu_write_byte(system_t* state, uint16_t address, uint8_t value);

uint16_t mmu_read_word(system_t* state, uint16_t address);
void mmu_write_word(system_t* state, uint16_t address, uint16_t value);
#endif