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

// --- Load/Store operations --- //
// ---- Register-to-Register ---- //
// for to in a b c d e h l; do for from in a b c d e h l; do echo "CPU_OP(LDrr_$to$from);"; done; done
CPU_OP(LDrr_aa); CPU_OP(LDrr_ab); CPU_OP(LDrr_ac); CPU_OP(LDrr_ad); CPU_OP(LDrr_ae); CPU_OP(LDrr_ah); CPU_OP(LDrr_al);
CPU_OP(LDrr_ba); CPU_OP(LDrr_bb); CPU_OP(LDrr_bc); CPU_OP(LDrr_bd); CPU_OP(LDrr_be); CPU_OP(LDrr_bh); CPU_OP(LDrr_bl);
CPU_OP(LDrr_ca); CPU_OP(LDrr_cb); CPU_OP(LDrr_cc); CPU_OP(LDrr_cd); CPU_OP(LDrr_ce); CPU_OP(LDrr_ch); CPU_OP(LDrr_cl);
CPU_OP(LDrr_da); CPU_OP(LDrr_db); CPU_OP(LDrr_dc); CPU_OP(LDrr_dd); CPU_OP(LDrr_de); CPU_OP(LDrr_dh); CPU_OP(LDrr_dl);
CPU_OP(LDrr_ea); CPU_OP(LDrr_eb); CPU_OP(LDrr_ec); CPU_OP(LDrr_ed); CPU_OP(LDrr_ee); CPU_OP(LDrr_eh); CPU_OP(LDrr_el);
CPU_OP(LDrr_ha); CPU_OP(LDrr_hb); CPU_OP(LDrr_hc); CPU_OP(LDrr_hd); CPU_OP(LDrr_he); CPU_OP(LDrr_hh); CPU_OP(LDrr_hl);
CPU_OP(LDrr_la); CPU_OP(LDrr_lb); CPU_OP(LDrr_lc); CPU_OP(LDrr_ld); CPU_OP(LDrr_le); CPU_OP(LDrr_lh); CPU_OP(LDrr_ll);

// ---- Load/Store specified memory location into register ---- //
// CPU_OP(LDrHLm_$to); CPU_OP(LDHLmr_$from);
CPU_OP(LDrHLm_a); CPU_OP(LDrHLm_b); CPU_OP(LDrHLm_c); CPU_OP(LDrHLm_d); CPU_OP(LDrHLm_e); CPU_OP(LDrHLm_h); CPU_OP(LDrHLm_l);
CPU_OP(LDHLmr_a); CPU_OP(LDHLmr_b); CPU_OP(LDHLmr_c); CPU_OP(LDHLmr_d); CPU_OP(LDHLmr_e); CPU_OP(LDHLmr_h); CPU_OP(LDHLmr_l);

// ---- Load from immediate address ---- //
// CPU_OP(LDrn_$to)
CPU_OP(LDrn_a); CPU_OP(LDrn_b); CPU_OP(LDrn_c); CPU_OP(LDrn_d); CPU_OP(LDrn_e); CPU_OP(LDrn_h); CPU_OP(LDrn_l);

// TODO: other load/store ops starting at LDHLmn

// ---- Swap operations ---- //
CPU_OP(SWAPr_a); CPU_OP(SWAPr_b); CPU_OP(SWAPr_c); CPU_OP(SWAPr_d); CPU_OP(SWAPr_e); CPU_OP(SWAPr_h); CPU_OP(SWAPr_l);

// --- Arithmetic Ops --- //
// ---- Addition ---- //
// Single Register
CPU_OP(ADDr_a); CPU_OP(ADDr_b); CPU_OP(ADDr_c); CPU_OP(ADDr_d); CPU_OP(ADDr_e); CPU_OP(ADDr_h); CPU_OP(ADDr_l);

// Double Register
CPU_OP(ADDHLBC); CPU_OP(ADDHLDE); CPU_OP(ADDHLHL);

CPU_OP(ADDHLSP);

// From memory
CPU_OP(ADDHL); CPU_OP(ADDn); CPU_OP(ADDSPn);



#undef CPU_OP
#endif