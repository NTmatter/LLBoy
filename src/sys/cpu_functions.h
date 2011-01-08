#ifndef __LLGB_CPU_FUNCTIONS_H
#define __LLGB_CPU_FUNCTIONS_H

#include "system.h"
#define CPU_OP(name) void cpu_op_##name(system_t* state)

// -- Helper Functions -- //
/// Prints a simple Hello World
void cpu_hello();

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

CPU_OP(nop);
CPU_OP(halt);

#undef CPU_OP
#endif