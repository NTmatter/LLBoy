#ifndef __LLGB_MMU_H
#define __LLGB_MMU_H

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
    
    // These could probably be condensed into a single array
    uint8_t* wram;
    uint8_t* eram;
    uint8_t* zram;
    
    uint16_t rom_offset;
    uint16_t ram_offset;
    
    bool in_bios;
    bool iE;
    bool iF;
} mmu_t;
#endif