#ifndef __LLGB_CPU_FUNCTIONS_H
#define __LLGB_CPU_FUNCTIONS_H

#include "system.h"

/// Returns a freshly-initialized CPU structure
cpu_t* initialize_cpu();

void cpu_reset(system_t* state);

void cpu_nop(system_t* state);

/// Prints a simple Hello World
void cpu_hello();
#endif