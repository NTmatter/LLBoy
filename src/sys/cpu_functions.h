#ifndef __LLGB_CPU_FUNCTIONS_H
#define __LLGB_CPU_FUNCTIONS_H

#include "system.h"

// -- Helper Functions -- //

/// Returns a freshly-initialized CPU structure
cpu_t* initialize_cpu();

void cpu_reset(system_t* state);

/// Save current registers
void cpu_rsv(system_t* state);

/// Restore registers
void cpu_rrs(system_t* state);

// -- Ops -- //
/// Handler for unknown opcodes
void cpu_op_undefined(system_t* state);

void cpu_op_nop(system_t* state);

/// Prints a simple Hello World
void cpu_hello();
#endif