#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "system.h"
#include "mmu_functions.h"

/// http://imrannazar.com/GameBoy-Emulation-in-JavaScript:-Memory
int main (int argc, char const *argv[])
{
    printf("Initializing system\n");
    system_t* state = initialize_system();
    
    printf("Setting up ROM\n");
    uint8_t* mem = (uint8_t*) state->mmu.memory;
    mem[0x0000] = 0x00; mem[0x0001] = 0x01; mem[0x0002] = 0x04; mem[0x0003] = 0x08;
    mem[0x0100] = 0x10; mem[0x0101] = 0x20; mem[0x0102] = 0x30; mem[0x0103] = 0x40;
    
    printf("Reading bytes and words from BIOS\n");
    assert(mmu_rb(state, 0x0000) == 0x00);
    assert(mmu_rb(state, 0x0001) == 0x01);
    assert(mmu_rw(state, 0x0002) == 0x0804);
    
    // Transition out of BIOS
    printf("Leaving BIOS\n");
    assert(mmu_memory_offset(state, 0x0000) == 0x0);
    state->cpu.pc = 0x100;
    assert(mmu_memory_offset(state, 0x0000) == 0x0); // Read must occur
    assert(mmu_rb(state, 0x0000) == 0x10); // Force the read
    assert(mmu_memory_offset(state, 0x0000) == 0x100);
    
    // Read from new locations
    printf("Reading Cart ROM locations\n");
    assert(mmu_rb(state, 0x0000) == 0x10);
    assert(mmu_rb(state, 0x0001) == 0x20);
    assert(mmu_rw(state, 0x0000) == 0x2010);
    
    // ROM areas should be unwriteable
    printf("Attempting to write to ROM\n");
    mmu_wb(state, 0x0000, 0x01);
    mmu_wb(state, 0x0001, 0x02);
    mmu_ww(state, 0x0002, 0x2233);
    assert(mmu_rw(state, 0x0000) == 0x2010);
    assert(mmu_rw(state, 0x0002) == 0x4030);
    
    // Write to RAM
    printf("Read/Write Working RAM\n");
    assert(mmu_rb(state, 0xC000) == 0);
    mmu_wb(state, 0xC000, 0x01);
    assert(mmu_rb(state, 0xC000) == 0x01);
    mmu_wb(state, 0xC001, 0x02);
    mmu_wb(state, 0xDE00, 0x05);
    mmu_ww(state, 0xDF9E, 0x4321);
    mmu_ww(state, 0xDFFE, 0x1234);
    assert(mmu_rw(state, 0xC000) == 0x0201);
    assert(mmu_rw(state, 0xDF9E) == 0x4321);
    assert(mmu_rw(state, 0xDFFE) == 0x1234);
    
    printf("Read/Write Working RAM Shadow");
    // Values propagated from basic Working RAM
    assert(mmu_rb(state, 0xE000) == 0x01);
    
    // Values propagated back to Working RAM
    mmu_wb(state, 0xE000, 0x03);
    assert(mmu_rb(state, 0xC000) == 0x03);
    assert(mmu_rb(state, 0xC000) == 0x03);
    
    // ZRAM must not be propagated back down to Working RAM base
    mmu_wb(state, 0xFE00, 0x04);
    assert(mmu_rb(state, 0xDE00) == 0x05);
    assert(mmu_rw(state, 0xFDFE) != 0x1234);
    
    return 0;
}
