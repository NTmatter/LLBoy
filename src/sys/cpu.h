#ifndef __CPU_H
#define __CPU_H

#include <stdint.h>
typedef struct cpu
{
    uint16_t pc;
} cpu_t;

/// Returns a freshly-initialized CPU structure
cpu_t* initialize_cpu();

/// Prints a simple Hello World
void cpu_hello();
#endif