#ifndef __LLGB_MMU_FUNCTIONS_H
#define __LLGB_MMU_FUNCTIONS_H

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
uint8_t mmu_ww(system_t* state, uint16_t address, uint16_t value);

uint8_t mmu_read_byte(system_t* state, uint16_t address);
void mmu_write_byte(system_t* state, uint16_t address, uint8_t value);

uint16_t mmu_read_word(system_t* state, uint16_t address);
void mmu_write_word(system_t* state, uint16_t address, uint16_t value);
#endif