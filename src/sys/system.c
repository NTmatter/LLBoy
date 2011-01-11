#include "system.h"
#include "cpu_functions.h"
#include "mmu_functions.h"

system_t* initialize_system() {
    system_t* sys = (system_t*) malloc(sizeof(system_t));
    cpu_initialize(&(sys->cpu));
    mmu_initialize(&(sys->mmu));
    return sys;
}