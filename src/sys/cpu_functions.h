#ifndef __LLGB_CPU_FUNCTIONS_H
#define __LLGB_CPU_FUNCTIONS_H

#include "system.h"
#define CPU_OP(name) void cpu_op_##name(system_t* state)

// -- Helper Functions -- //
/// Prints a simple Hello World
void cpu_hello();

/// Initializes the contents of the provided cpu structure
void cpu_initialize(cpu_t* cpu);

void cpu_reset(system_t* state);

/// Save current registers
void cpu_rsv(system_t* state);

/// Restore registers
void cpu_rrs(system_t* state);

// -- Ops -- //

/// Handler for unknown opcodes
CPU_OP(undefined);

/// Handler for opcodes that exist but have not been implemented
CPU_OP(unimplemented);
CPU_OP(NOP);
CPU_OP(HALT);

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

#define OP(opname) cpu_op_##opname
static void* cpu_ops_basic[256] = {
    // 00
    OP(NOP), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(ADDHLBC), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // 10
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(ADDHLDE), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // 20
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(ADDHLHL), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // 30
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // 40
    OP(LDrr_bb), OP(LDrr_bc), OP(LDrr_bd), OP(LDrr_be),
    OP(LDrr_bh), OP(LDrr_bl), OP(LDrHLm_b), OP(LDrr_ba),
    OP(LDrr_cb), OP(LDrr_cc), OP(LDrr_cd), OP(LDrr_ce),
    OP(LDrr_ch), OP(LDrr_cl), OP(LDrHLm_c), OP(LDrr_ca),
    // 50
    OP(LDrr_db), OP(LDrr_dc), OP(LDrr_dd), OP(LDrr_de),
    OP(LDrr_dh), OP(LDrr_dl), OP(LDrHLm_d), OP(LDrr_da),
    OP(LDrr_eb), OP(LDrr_ec), OP(LDrr_ed), OP(LDrr_ee),
    OP(LDrr_eh), OP(LDrr_el), OP(LDrHLm_e), OP(LDrr_ea),
    // 60
    OP(LDrr_hb), OP(LDrr_hc), OP(LDrr_hd), OP(LDrr_he),
    OP(LDrr_hh), OP(LDrr_hl), OP(LDrHLm_h), OP(LDrr_ha),
    OP(LDrr_lb), OP(LDrr_lc), OP(LDrr_ld), OP(LDrr_le),
    OP(LDrr_lh), OP(LDrr_ll), OP(LDrHLm_l), OP(LDrr_ll),
    // 70
    OP(LDHLmr_b), OP(LDHLmr_c), OP(LDHLmr_d), OP(LDHLmr_e),
    OP(LDHLmr_h), OP(LDHLmr_l), OP(HALT), OP(LDHLmr_a),
    OP(LDrr_ab), OP(LDrr_ac), OP(LDrr_ad), OP(LDrr_ae),
    OP(LDrr_ah), OP(LDrr_al), OP(LDrHLm_a), OP(LDrr_aa),
    // 80
    OP(ADDr_b), OP(ADDr_c), OP(ADDr_d), OP(ADDr_e),
    OP(ADDr_h), OP(ADDr_l), OP(ADDHL), OP(ADDr_a),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // 90
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // A0
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // B0
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // C0
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // D0
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(undefined),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(undefined),
    OP(unimplemented), OP(undefined), OP(unimplemented), OP(unimplemented),
    // E0
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(undefined),
    OP(undefined), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(undefined),
    OP(undefined), OP(undefined), OP(unimplemented), OP(unimplemented),
    // F0
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(undefined), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(undefined), OP(unimplemented), OP(unimplemented),
    OP(undefined), OP(undefined), OP(unimplemented), OP(unimplemented)
};

static void* cpu_ops_cb[256] = {
    // 00
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // 10
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // 20
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(undefined), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(undefined), OP(unimplemented),
    // 30
    OP(SWAPr_b), OP(SWAPr_c), OP(SWAPr_d), OP(SWAPr_e),
    OP(SWAPr_h), OP(SWAPr_l), OP(undefined), OP(SWAPr_a),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(undefined), OP(unimplemented),
    // 40
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // 50
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // 60
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // 70
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // 80
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // 90
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // A0
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // B0
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // C0
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // D0
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // E0
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // F0
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented)
};
#undef OP
#endif