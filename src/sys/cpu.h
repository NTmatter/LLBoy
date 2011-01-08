#ifdef __CPU_H
#define __CPU_H
typedef struct
{
    int pc = 0;
} cpu_t;

/// Prints a simple Hello World
void cpu_hello();
#endif