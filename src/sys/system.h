#ifndef __LLGB_SYSTEM_H
#define __LLGB_SYSTEM_H

#include <stdlib.h>
#include "cpu.h"
#include "mmu.h"

/// Aggregates all of the system components
typedef struct {
    cpu_t cpu;
    mmu_t mmu;
} system_t;

system_t* initialize_system();

#endif