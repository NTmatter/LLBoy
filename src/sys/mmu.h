#ifndef __LLGB_MMU_H
#define __LLGB_MMU_H

#include <stdint.h>
#include <stdbool.h>

#include "bios.h"

typedef struct {
    uint8_t* rom;
    uint8_t cart_type;
    
    struct {
        uint8_t rom_bank;
        uint8_t ram_bank;
        uint8_t ram_on;
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