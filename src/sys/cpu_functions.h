#ifndef __LLGB_CPU_FUNCTIONS_H
#define __LLGB_CPU_FUNCTIONS_H

// Copyright (c) 2011 Thomas Johnson
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#import <string.h>
#include "system.h"
#define CPU_OP(name) void cpu_op_##name(system_t* state)

typedef void (*cpu_op_t)(system_t*);
typedef struct {
    const char* name;
    uint8_t opcode;
    uint8_t cycles;
    cpu_op_t impl;
    const char* impl_name;
    uint8_t args;
    bool terminator;
} cpu_op_metadata_s;

// -- Helper Functions -- //
/// Initializes the contents of the provided cpu structure
void cpu_initialize(cpu_t* cpu);
void cpu_execute(system_t* state);

void cpu_reset(system_t* state);

/// Save current registers
void cpu_rsv(system_t* state);

/// Restore registers
void cpu_rrs(system_t* state);

void cpu_op_cb(system_t* state);

// -- Ops -- //
/// Handler for unknown opcodes
CPU_OP(undefined);

/// Handler for opcodes that exist but have not been implemented
CPU_OP(unimplemented);

CPU_OP(NOP);
CPU_OP(HALT);
CPU_OP(EI);
CPU_OP(DI);

// --- Load/Store operations --- //
// ---- Register-to-Register ---- //
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

// ---- Miscellaneous Load/Store operations ---- //
CPU_OP(LDHLDA); CPU_OP(LDHLIA); CPU_OP(LDAHLD); CPU_OP(LDAHLI);
CPU_OP(LDHLmn);
CPU_OP(LDABCm); CPU_OP(LDADEm);
CPU_OP(LDBCnn); CPU_OP(LDDEnn); CPU_OP(LDHLnn); CPU_OP(LDSPnn);
CPU_OP(LDmmA); CPU_OP(LDAmm);
CPU_OP(LDAIOn); CPU_OP(LDIOnA); CPU_OP(LDAIOC); CPU_OP(LDIOCA);

// --- Control Flow --- //
// ---- Function Calls ---- //
CPU_OP(CALLnn);

// ---- Function Returns ---- //
CPU_OP(RET); CPU_OP(RETNZ); CPU_OP(RETZ); CPU_OP(RETNC); CPU_OP(RETC);

// ---- Absolute Jumps ---- //
CPU_OP(JPnn); CPU_OP(JPCnn); CPU_OP(JPNCnn); CPU_OP(JPZnn); CPU_OP(JPNZnn); CPU_OP(JPHL);
// ---- Relative Jumps ---- //
CPU_OP(JRn); CPU_OP(JRCn); CPU_OP(JRNCn); CPU_OP(JRZn); CPU_OP(JRNZn);

// ---- Swap operations ---- //
CPU_OP(SWAPr_a); CPU_OP(SWAPr_b); CPU_OP(SWAPr_c); CPU_OP(SWAPr_d); CPU_OP(SWAPr_e); CPU_OP(SWAPr_h); CPU_OP(SWAPr_l);

// --- Stack Operations --- //
CPU_OP(PUSHAF); CPU_OP(PUSHBC); CPU_OP(PUSHDE); CPU_OP(PUSHHL);
CPU_OP(POPAF); CPU_OP(POPBC); CPU_OP(POPDE); CPU_OP(POPHL);

// --- Arithmetic Ops --- //
// ---- Addition ---- //
// Single Register
CPU_OP(ADDr_a); CPU_OP(ADDr_b); CPU_OP(ADDr_c); CPU_OP(ADDr_d); CPU_OP(ADDr_e); CPU_OP(ADDr_h); CPU_OP(ADDr_l);

// Double Register
CPU_OP(ADDHLBC); CPU_OP(ADDHLDE); CPU_OP(ADDHLHL);

CPU_OP(ADDHLSP);

// From memory
CPU_OP(ADDHL); CPU_OP(ADDn); CPU_OP(ADDSPn);

// ---- Subtraction ---- //
// Single Register
CPU_OP(SUBr_a); CPU_OP(SUBr_b); CPU_OP(SUBr_c); CPU_OP(SUBr_d);
CPU_OP(SUBr_e); CPU_OP(SUBr_h); CPU_OP(SUBr_l);

// ---- Increment ---- //
CPU_OP(INCBC); CPU_OP(INCDE); CPU_OP(INCDE); CPU_OP(INCHL); CPU_OP(INCSP);

CPU_OP(INCr_a); CPU_OP(INCr_b); CPU_OP(INCr_c); CPU_OP(INCr_d);
CPU_OP(INCr_e); CPU_OP(INCr_h); CPU_OP(INCr_l); CPU_OP(INCHLm);

// ---- Decrement ---- //
CPU_OP(DECBC); CPU_OP(DECDE); CPU_OP(DECDE); CPU_OP(DECHL); CPU_OP(DECSP);

CPU_OP(DECr_a); CPU_OP(DECr_b); CPU_OP(DECr_c); CPU_OP(DECr_d);
CPU_OP(DECr_e); CPU_OP(DECr_h); CPU_OP(DECr_l); CPU_OP(DECHLm);

// --- Comparisons --- //
CPU_OP(CPr_a); CPU_OP(CPr_b); CPU_OP(CPr_c); CPU_OP(CPr_d);
CPU_OP(CPr_e); CPU_OP(CPr_h); CPU_OP(CPr_l);

CPU_OP(CPHL); CPU_OP(CPn);

// --- Rotations --- //
CPU_OP(RLA);

CPU_OP(RLr_a); CPU_OP(RLr_b); CPU_OP(RLr_c); CPU_OP(RLr_d);
CPU_OP(RLr_e); CPU_OP(RLr_h); CPU_OP(RLr_l);

// --- XOR --- //
CPU_OP(XORr_a); CPU_OP(XORr_b); CPU_OP(XORr_c); CPU_OP(XORr_d);
CPU_OP(XORr_e); CPU_OP(XORr_h); CPU_OP(XORr_l);

// -- CB OPS -- //
CPU_OP(BIT0b); CPU_OP(BIT0c); CPU_OP(BIT0d); CPU_OP(BIT0e);
CPU_OP(BIT0h); CPU_OP(BIT0l); CPU_OP(BIT0m); CPU_OP(BIT0a);
CPU_OP(BIT1b); CPU_OP(BIT1c); CPU_OP(BIT1d); CPU_OP(BIT1e);
CPU_OP(BIT1h); CPU_OP(BIT1l); CPU_OP(BIT1m); CPU_OP(BIT1a);
CPU_OP(BIT2b); CPU_OP(BIT2c); CPU_OP(BIT2d); CPU_OP(BIT2e);
CPU_OP(BIT2h); CPU_OP(BIT2l); CPU_OP(BIT2m); CPU_OP(BIT2a);
CPU_OP(BIT3b); CPU_OP(BIT3c); CPU_OP(BIT3d); CPU_OP(BIT3e);
CPU_OP(BIT3h); CPU_OP(BIT3l); CPU_OP(BIT3m); CPU_OP(BIT3a);
CPU_OP(BIT4b); CPU_OP(BIT4c); CPU_OP(BIT4d); CPU_OP(BIT4e);
CPU_OP(BIT4h); CPU_OP(BIT4l); CPU_OP(BIT4m); CPU_OP(BIT4a);
CPU_OP(BIT5b); CPU_OP(BIT5c); CPU_OP(BIT5d); CPU_OP(BIT5e);
CPU_OP(BIT5h); CPU_OP(BIT5l); CPU_OP(BIT5m); CPU_OP(BIT5a);
CPU_OP(BIT6b); CPU_OP(BIT6c); CPU_OP(BIT6d); CPU_OP(BIT6e);
CPU_OP(BIT6h); CPU_OP(BIT6l); CPU_OP(BIT6m); CPU_OP(BIT6a);
CPU_OP(BIT7b); CPU_OP(BIT7c); CPU_OP(BIT7d); CPU_OP(BIT7e);
CPU_OP(BIT7h); CPU_OP(BIT7l); CPU_OP(BIT7m); CPU_OP(BIT7a);

#undef CPU_OP

#define OP(opname) cpu_op_##opname
#define OPM(op_name, op_code, op_cycles, op_impl, op_args, op_terminator) \
{.name = #op_name, .opcode = op_code, .cycles = op_cycles, .args = op_args, .terminator = op_terminator, \
    .impl = op_impl, .impl_name = #op_impl}

static cpu_op_metadata_s cpu_op_metadata_basic[256] = {
    // 0x00
    OPM(NOP, 0x00, 1, cpu_op_NOP, 0, false),
    OPM(LDBCnn, 0x01, 3, cpu_op_LDBCnn, 2, false),
    OPM(LDBCmA, 0x02, 2, cpu_op_unimplemented, 0, false),
    OPM(INCBC, 0x03, 1, cpu_op_INCBC, 0, false),
    OPM(INCr_b, 0x04, 1, cpu_op_INCr_b, 0, false),
    OPM(DECr_b, 0x05, 1, cpu_op_DECr_b, 0, false),
    OPM(LDrn_b, 0x06, 2, cpu_op_LDrn_b, 1, false),
    OPM(RLCA, 0x07, 1, cpu_op_unimplemented, 0, false),
    OPM(LDmmSP, 0x08, 1, cpu_op_undefined, 0, true),
    OPM(ADDHLBC, 0x09, 3, cpu_op_ADDHLBC, 0, false),
    OPM(LDABCm, 0x0A, 2, cpu_op_LDABCm, 0, false),
    OPM(DECBC, 0x0B, 1, cpu_op_DECBC, 0, false),
    OPM(INCr_c, 0x0C, 1, cpu_op_INCr_c, 0, false),
    OPM(DECr_c, 0x0D, 1, cpu_op_DECr_c, 0, false),
    OPM(LDrn_c, 0x0E, 2, cpu_op_LDrn_c, 1, false),
    OPM(RRCA, 0x0F, 1, cpu_op_unimplemented, 0, false),

    // 0x10
    OPM(DJNZn, 0x10, 2, cpu_op_unimplemented, 1, true),
    OPM(LDDEnn, 0x11, 3, cpu_op_LDDEnn, 2, false),
    OPM(LDDEmA, 0x12, 2, cpu_op_unimplemented, 0, false),
    OPM(INCDE, 0x13, 1, cpu_op_INCDE, 0, false),
    OPM(INCr_d, 0x14, 1, cpu_op_INCr_d, 0, false),
    OPM(DECr_d, 0x15, 1, cpu_op_DECr_d, 0, false),
    OPM(LDrn_d, 0x16, 2, cpu_op_LDrn_d, 1, false),
    OPM(RLA, 0x17, 1, cpu_op_unimplemented, 0, false),
    OPM(JRn, 0x18, 2, cpu_op_JRn, 1, true),
    OPM(ADDHLDE, 0x19, 3, cpu_op_ADDHLDE, 0, false),
    OPM(LDADEm, 0x1A, 2, cpu_op_LDADEm, 0, false),
    OPM(DECDE, 0x1B, 1, cpu_op_DECDE, 0, false),
    OPM(INCr_e, 0x1C, 1, cpu_op_INCr_e, 0, false),
    OPM(DECr_e, 0x1D, 1, cpu_op_DECr_e, 0, false),
    OPM(LDrn_e, 0x1E, 2, cpu_op_LDrn_e, 1, false),
    OPM(RRA, 0x1F, 1, cpu_op_unimplemented, 0, false),

    // 0x20
    OPM(JRNZn, 0x20, 2, cpu_op_JRNZn, 1, true),
    OPM(LDHLnn, 0x21, 3, cpu_op_LDHLnn, 2, false),
    OPM(LDHLIA, 0x22, 2, cpu_op_LDHLIA, 0, false),
    OPM(INCHL, 0x23, 1, cpu_op_INCHL, 0, false),
    OPM(INCr_h, 0x24, 1, cpu_op_INCr_h, 0, false),
    OPM(DECr_h, 0x25, 1, cpu_op_DECr_h, 0, false),
    OPM(LDrn_h, 0x26, 2, cpu_op_LDrn_h, 1, false),
    OPM(DAA, 0x27, 1, cpu_op_unimplemented, 0, false),
    OPM(JRZn, 0x28, 2, cpu_op_JRZn, 1, true),
    OPM(ADDHLHL, 0x29, 3, cpu_op_ADDHLHL, 0, false),
    OPM(LDAHLI, 0x2A, 2, cpu_op_LDAHLI, 0, false),
    OPM(DECHL, 0x2B, 1, cpu_op_DECHL, 0, false),
    OPM(INCr_l, 0x2C, 1, cpu_op_INCr_l, 0, false),
    OPM(DECr_l, 0x2D, 1, cpu_op_DECr_l, 0, false),
    OPM(LDrn_l, 0x2E, 2, cpu_op_LDrn_l, 1, false),
    OPM(CPL, 0x2F, 1, cpu_op_unimplemented, 0, false),

    // Ox30
    OPM(JRNCn, 0x30, 2, cpu_op_JRNCn, 1, true),
    OPM(LDSPnn, 0x31, 3, cpu_op_LDSPnn, 2, false),
    OPM(LDHLDA, 0x32, 2, cpu_op_LDHLDA, 0, false),
    OPM(INCSP, 0x33, 1, cpu_op_INCSP, 0, false),
    OPM(INCHLm, 0x34, 3, cpu_op_INCHLm, 0, false),
    OPM(DECHLm, 0x35, 3, cpu_op_DECHLm, 0, false),
    OPM(LDHLmn, 0x36, 3, cpu_op_LDHLmn, 1, false),
    OPM(SCF, 0x37, 1, cpu_op_unimplemented, 0, false),
    OPM(JRCn, 0x38, 2, cpu_op_JRCn, 1, true),
    OPM(ADDHLSP, 0x39, 3, cpu_op_unimplemented, 0, false),
    OPM(LDAHLD, 0x3A, 2, cpu_op_LDAHLD, 0, false),
    OPM(DECSP, 0x3B, 1, cpu_op_DECSP, 0, false),
    OPM(INCr_a, 0x3C, 1, cpu_op_INCr_a, 0, false),
    OPM(DECr_a, 0x3D, 1, cpu_op_DECr_a, 0, false),
    OPM(LDrn_a, 0x3E, 2, cpu_op_LDrn_a, 1, false),
    OPM(CCF, 0x3F, 1, cpu_op_unimplemented, 0, false),

    // 0x40
    OPM(LDrr_bb, 0x40, 1, cpu_op_LDrr_bb, 0, false),
    OPM(LDrr_bc, 0x41, 1, cpu_op_LDrr_bc, 0, false),
    OPM(LDrr_bd, 0x42, 1, cpu_op_LDrr_bd, 0, false),
    OPM(LDrr_be, 0x43, 1, cpu_op_LDrr_be, 0, false),
    OPM(LDrr_bh, 0x44, 1, cpu_op_LDrr_bh, 0, false),
    OPM(LDrr_bl, 0x45, 1, cpu_op_LDrr_bl, 0, false),
    OPM(LDrHLm_b, 0x46, 2, cpu_op_LDrHLm_b, 0, false),
    OPM(LDrr_ba, 0x47, 1, cpu_op_LDrr_ba, 0, false),
    OPM(LDrr_cb, 0x48, 1, cpu_op_LDrr_cb, 0, false),
    OPM(LDrr_cc, 0x49, 1, cpu_op_LDrr_cc, 0, false),
    OPM(LDrr_cd, 0x4A, 1, cpu_op_LDrr_cd, 0, false),
    OPM(LDrr_ce, 0x4B, 1, cpu_op_LDrr_ce, 0, false),
    OPM(LDrr_ch, 0x4C, 1, cpu_op_LDrr_ch, 0, false),
    OPM(LDrr_cl, 0x4D, 1, cpu_op_LDrr_cl, 0, false),
    OPM(LDrHLm_c, 0x4E, 2, cpu_op_LDrHLm_c, 0, false),
    OPM(LDrr_ca, 0x4F, 1, cpu_op_LDrr_ca, 0, false),

    // 0x50
    OPM(LDrr_db, 0x50, 1, cpu_op_LDrr_db, 0, false),
    OPM(LDrr_dc, 0x51, 1, cpu_op_LDrr_dc, 0, false),
    OPM(LDrr_dd, 0x52, 1, cpu_op_LDrr_dd, 0, false),
    OPM(LDrr_de, 0x53, 1, cpu_op_LDrr_de, 0, false),
    OPM(LDrr_dh, 0x54, 1, cpu_op_LDrr_dh, 0, false),
    OPM(LDrr_dl, 0x55, 1, cpu_op_LDrr_dl, 0, false),
    OPM(LDrHLm_d, 0x56, 2, cpu_op_LDrHLm_d, 0, false),
    OPM(LDrr_da, 0x57, 1, cpu_op_LDrr_da, 0, false),
    OPM(LDrr_eb, 0x58, 1, cpu_op_LDrr_eb, 0, false),
    OPM(LDrr_ec, 0x59, 1, cpu_op_LDrr_ec, 0, false),
    OPM(LDrr_ed, 0x5A, 1, cpu_op_LDrr_ed, 0, false),
    OPM(LDrr_ee, 0x5B, 1, cpu_op_LDrr_ee, 0, false),
    OPM(LDrr_eh, 0x5C, 1, cpu_op_LDrr_eh, 0, false),
    OPM(LDrr_el, 0x5D, 1, cpu_op_LDrr_el, 0, false),
    OPM(LDrHLm_e, 0x5E, 2, cpu_op_LDrHLm_e, 0, false),
    OPM(LDrr_ea, 0x5F, 1, cpu_op_LDrr_ea, 0, false),

    // 0x60
    OPM(LDrr_hb, 0x60, 1, cpu_op_LDrr_hb, 0, false),
    OPM(LDrr_hc, 0x61, 1, cpu_op_LDrr_hc, 0, false),
    OPM(LDrr_hd, 0x62, 1, cpu_op_LDrr_hd, 0, false),
    OPM(LDrr_he, 0x63, 1, cpu_op_LDrr_he, 0, false),
    OPM(LDrr_hh, 0x64, 1, cpu_op_LDrr_hh, 0, false),
    OPM(LDrr_hl, 0x65, 1, cpu_op_LDrr_hl, 0, false),
    OPM(LDrHLm_h, 0x66, 2, cpu_op_LDrHLm_h, 0, false),
    OPM(LDrr_ha, 0x67, 1, cpu_op_LDrr_ha, 0, false),
    OPM(LDrr_lb, 0x68, 1, cpu_op_LDrr_lb, 0, false),
    OPM(LDrr_lc, 0x69, 1, cpu_op_LDrr_lc, 0, false),
    OPM(LDrr_ld, 0x6A, 1, cpu_op_LDrr_ld, 0, false),
    OPM(LDrr_le, 0x6B, 1, cpu_op_LDrr_le, 0, false),
    OPM(LDrr_lh, 0x6C, 1, cpu_op_LDrr_lh, 0, false),
    OPM(LDrr_ll, 0x6D, 1, cpu_op_LDrr_ll, 0, false),
    OPM(LDrHLm_l, 0x6E, 2, cpu_op_LDrHLm_l, 0, false),
    OPM(LDrr_la, 0x6F, 1, cpu_op_LDrr_la, 0, false),

    // 0x70
    OPM(LDHLmr_b, 0x70, 2, cpu_op_LDHLmr_b, 0, false),
    OPM(LDHLmr_c, 0x71, 2, cpu_op_LDHLmr_c, 0, false),
    OPM(LDHLmr_d, 0x72, 2, cpu_op_LDHLmr_d, 0, false),
    OPM(LDHLmr_e, 0x73, 2, cpu_op_LDHLmr_e, 0, false),
    OPM(LDHLmr_h, 0x74, 2, cpu_op_LDHLmr_h, 0, false),
    OPM(LDHLmr_l, 0x75, 2, cpu_op_LDHLmr_l, 0, false),
    OPM(HALT, 0x76, 1, cpu_op_HALT, 0, true),
    OPM(LDHLmr_a, 0x77, 2, cpu_op_LDHLmr_a, 0, false),
    OPM(LDrr_ab, 0x78, 1, cpu_op_LDrr_ab, 0, false),
    OPM(LDrr_ac, 0x79, 1, cpu_op_LDrr_ac, 0, false),
    OPM(LDrr_ad, 0x7A, 1, cpu_op_LDrr_ad, 0, false),
    OPM(LDrr_ae, 0x7B, 1, cpu_op_LDrr_ae, 0, false),
    OPM(LDrr_ah, 0x7C, 1, cpu_op_LDrr_ah, 0, false),
    OPM(LDrr_al, 0x7D, 1, cpu_op_LDrr_al, 0, false),
    OPM(LDrHLm_a, 0x7E, 2, cpu_op_LDrHLm_a, 0, false),
    OPM(LDrr_aa, 0x7F, 1, cpu_op_LDrr_aa, 0, false),

    // 0x80
    OPM(ADDr_b, 0x80, 1, cpu_op_ADDr_b, 0, false),
    OPM(ADDr_c, 0x81, 1, cpu_op_ADDr_c, 0, false),
    OPM(ADDr_d, 0x82, 1, cpu_op_ADDr_d, 0, false),
    OPM(ADDr_e, 0x83, 1, cpu_op_ADDr_e, 0, false),
    OPM(ADDr_h, 0x84, 1, cpu_op_ADDr_h, 0, false),
    OPM(ADDr_l, 0x85, 1, cpu_op_ADDr_l, 0, false),
    OPM(ADDHL, 0x86, 2, cpu_op_ADDHL, 0, false),
    OPM(ADDr_a, 0x87, 1, cpu_op_ADDr_a, 0, false),
    OPM(ADCr_b, 0x88, 1, cpu_op_unimplemented, 0, false),
    OPM(ADCr_c, 0x89, 1, cpu_op_unimplemented, 0, false),
    OPM(ADCr_d, 0x8A, 1, cpu_op_unimplemented, 0, false),
    OPM(ADCr_e, 0x8B, 1, cpu_op_unimplemented, 0, false),
    OPM(ADCr_h, 0x8C, 1, cpu_op_unimplemented, 0, false),
    OPM(ADCr_l, 0x8D, 1, cpu_op_unimplemented, 0, false),
    OPM(ADCHL, 0x8E, 2, cpu_op_unimplemented, 0, false),
    OPM(ADCr_a, 0x8F, 1, cpu_op_unimplemented, 0, false),

    // 0x90
    OPM(SUBr_b, 0x90, 1, cpu_op_SUBr_b, 0, false),
    OPM(SUBr_c, 0x91, 1, cpu_op_SUBr_c, 0, false),
    OPM(SUBr_d, 0x92, 1, cpu_op_SUBr_d, 0, false),
    OPM(SUBr_e, 0x93, 1, cpu_op_SUBr_e, 0, false),
    OPM(SUBr_h, 0x94, 1, cpu_op_SUBr_h, 0, false),
    OPM(SUBr_l, 0x95, 1, cpu_op_SUBr_l, 0, false),
    OPM(SUBHL, 0x96, 2, cpu_op_unimplemented, 0, false),
    OPM(SUBr_a, 0x97, 1, cpu_op_SUBr_a, 0, false),
    OPM(SBCr_b, 0x98, 1, cpu_op_unimplemented, 0, false),
    OPM(SBCr_c, 0x99, 1, cpu_op_unimplemented, 0, false),
    OPM(SBCr_d, 0x9A, 1, cpu_op_unimplemented, 0, false),
    OPM(SBCr_e, 0x9B, 1, cpu_op_unimplemented, 0, false),
    OPM(SBCr_h, 0x9C, 1, cpu_op_unimplemented, 0, false),
    OPM(SBCr_l, 0x9D, 1, cpu_op_unimplemented, 0, false),
    OPM(SBCHL, 0x9E, 2, cpu_op_unimplemented, 0, false),
    OPM(SBCr_a, 0x9F, 1, cpu_op_unimplemented, 0, false),

    // 0xA0
    OPM(ANDr_b, 0xA0, 1, cpu_op_unimplemented, 0, false),
    OPM(ANDr_c, 0xA1, 1, cpu_op_unimplemented, 0, false),
    OPM(ANDr_d, 0xA2, 1, cpu_op_unimplemented, 0, false),
    OPM(ANDr_e, 0xA3, 1, cpu_op_unimplemented, 0, false),
    OPM(ANDr_h, 0xA4, 1, cpu_op_unimplemented, 0, false),
    OPM(ANDr_l, 0xA5, 1, cpu_op_unimplemented, 0, false),
    OPM(ANDHL, 0xA6, 2, cpu_op_unimplemented, 0, false),
    OPM(ANDr_a, 0xA7, 1, cpu_op_unimplemented, 0, false),
    OPM(XORr_b, 0xA8, 1, cpu_op_XORr_b, 0, false),
    OPM(XORr_c, 0xA9, 1, cpu_op_XORr_c, 0, false),
    OPM(XORr_d, 0xAA, 1, cpu_op_XORr_d, 0, false),
    OPM(XORr_e, 0xAB, 1, cpu_op_XORr_e, 0, false),
    OPM(XORr_h, 0xAC, 1, cpu_op_XORr_h, 0, false),
    OPM(XORr_l, 0xAD, 1, cpu_op_XORr_l, 0, false),
    OPM(XORHL, 0xAE, 2, cpu_op_unimplemented, 0, false),
    OPM(XORr_a, 0xAF, 1, cpu_op_XORr_a, 0, false),

    // 0xB0
    OPM(ORr_b, 0xB0, 1, cpu_op_unimplemented, 0, false),
    OPM(ORr_c, 0xB1, 1, cpu_op_unimplemented, 0, false),
    OPM(ORr_d, 0xB2, 1, cpu_op_unimplemented, 0, false),
    OPM(ORr_e, 0xB3, 1, cpu_op_unimplemented, 0, false),
    OPM(ORr_h, 0xB4, 1, cpu_op_unimplemented, 0, false),
    OPM(ORr_l, 0xB5, 1, cpu_op_unimplemented, 0, false),
    OPM(ORHL, 0xB6, 2, cpu_op_unimplemented, 0, false),
    OPM(ORr_a, 0xB7, 1, cpu_op_unimplemented, 0, false),
    OPM(CPr_b, 0xB8, 1, cpu_op_CPr_b, 0, false),
    OPM(CPr_c, 0xB9, 1, cpu_op_CPr_c, 0, false),
    OPM(CPr_d, 0xBA, 1, cpu_op_CPr_d, 0, false),
    OPM(CPr_e, 0xBB, 1, cpu_op_CPr_e, 0, false),
    OPM(CPr_h, 0xBC, 1, cpu_op_CPr_h, 0, false),
    OPM(CPr_l, 0xBD, 1, cpu_op_CPr_l, 0, false),
    OPM(CPHL, 0xBE, 2, cpu_op_CPHL, 0, false),
    OPM(CPr_a, 0xBF, 1, cpu_op_CPr_a, 0, false),

    // 0xC0
    OPM(RETNZ, 0xC0, 1, cpu_op_RETNZ, 0, true),
    OPM(POPBC, 0xC1, 3, cpu_op_POPBC, 0, false),
    OPM(JPNZnn, 0xC2, 3, cpu_op_JPNZnn, 2, true),
    OPM(JPnn, 0xC3, 3, cpu_op_JPnn, 2, true),
    OPM(CALLNZnn, 0xC4, 3, cpu_op_unimplemented, 2, true),
    OPM(PUSHBC, 0xC5, 3, cpu_op_PUSHBC, 0, false),
    OPM(ADDn, 0xC6, 2, cpu_op_unimplemented, 1, false),
    OPM(RST00, 0xC7, 3, cpu_op_unimplemented, 0, true),
    OPM(RETZ, 0xC8, 1, cpu_op_RETZ, 0, true),
    OPM(RET, 0xC9, 3, cpu_op_RET, 0, true),
    OPM(JPZnn, 0xCA, 3, cpu_op_JPZnn, 2, true),
    OPM(MAPcb, 0xCB, 0, cpu_op_cb, 0, false),
    OPM(CALLZnn, 0xCC, 3, cpu_op_unimplemented, 2, true),
    OPM(CALLnn, 0xCD, 5, cpu_op_CALLnn, 2, true),
    OPM(ADCn, 0xCE, 2, cpu_op_unimplemented, 1, false),
    OPM(RST08, 0xCF, 3, cpu_op_unimplemented, 0, true),

    // 0xD0
    OPM(RETNC, 0xD0, 1, cpu_op_RETNC, 0, true),
    OPM(POPDE, 0xD1, 3, cpu_op_POPDE, 0, false),
    OPM(JPNCnn, 0xD2, 3, cpu_op_JPNCnn, 2, true),
    OPM(XX, 0xD3, 1, cpu_op_undefined, 0, true),
    OPM(CALLNCnn, 0xD4, 3, cpu_op_unimplemented, 2, true),
    OPM(PUSHDE, 0xD5, 3, cpu_op_PUSHDE, 0, false),
    OPM(SUBn, 0xD6, 2, cpu_op_unimplemented, 1, false),
    OPM(RST10, 0xD7, 3, cpu_op_unimplemented, 0, true),
    OPM(RETC, 0xD8, 1, cpu_op_RETC, 0, true),
    OPM(RETI, 0xD9, 3, cpu_op_unimplemented, 0, true),
    OPM(JPCnn, 0xDA, 3, cpu_op_JPCnn, 2, true),
    OPM(XX, 0xDB, 1, cpu_op_undefined, 0, true),
    OPM(CALLCnn, 0xDC, 5, cpu_op_unimplemented, 2, true),
    OPM(XX, 0xDD, 1, cpu_op_undefined, 0, true),
    OPM(SBCn, 0xDE, 2, cpu_op_unimplemented, 1, false),
    OPM(RST18, 0xDF, 3, cpu_op_unimplemented, 0, true),

    // 0xE0
    OPM(LDIOnA, 0xE0, 3, cpu_op_LDIOnA, 1, false),
    OPM(POPHL, 0xE1, 3, cpu_op_POPHL, 0, false),
    OPM(LDIOCA, 0xE2, 2, cpu_op_LDIOCA, 0, false),
    OPM(XX, 0xE3, 1, cpu_op_undefined, 0, true),
    OPM(XX, 0xE4, 1, cpu_op_undefined, 0, true),
    OPM(PUSHHL, 0xE5, 3, cpu_op_PUSHHL, 0, false),
    OPM(ANDn, 0xE6, 2, cpu_op_unimplemented, 1, false),
    OPM(RST20, 0xE7, 3, cpu_op_unimplemented, 0, true),
    OPM(ADDSPn, 0xE8, 4, cpu_op_unimplemented, 1, false),
    OPM(JPHL, 0xE9, 1, cpu_op_JPHL, 0, true),
    OPM(LDmmA, 0xEA, 4, cpu_op_LDmmA, 2, false),
    OPM(XX, 0xEB, 1, cpu_op_undefined, 0, true),
    OPM(XX, 0xEC, 1, cpu_op_undefined, 0, true),
    OPM(XX, 0xED, 1, cpu_op_undefined, 0, true),
    OPM(XORn, 0xEE, 2, cpu_op_unimplemented, 1, false),
    OPM(RST28, 0xEF, 3, cpu_op_unimplemented, 0, true),

    // 0xF0
    OPM(LDAIOn, 0xF0, 3, cpu_op_LDAIOn, 1, false),
    OPM(POPAF, 0xF1, 3, cpu_op_POPAF, 0, false),
    OPM(LDAIOC, 0xF2, 2, cpu_op_LDAIOC, 0, false),
    OPM(DI, 0xF3, 1, cpu_op_DI, 0, false),
    OPM(XX, 0xF4, 1, cpu_op_undefined, 0, true),
    OPM(PUSHAF, 0xF5, 3, cpu_op_PUSHAF, 0, false),
    OPM(ORn, 0xF6, 2, cpu_op_unimplemented, 1, false),
    OPM(RST30, 0xF7, 3, cpu_op_unimplemented, 0, true),
    OPM(LDHLSPn, 0xF8, 3, cpu_op_unimplemented, 1, false),
    OPM(XX, 0xF9, 1, cpu_op_undefined, 0, true),
    OPM(LDAmm, 0xFA, 4, cpu_op_LDAmm, 2, false),
    OPM(EI, 0xFB, 1, cpu_op_EI, 0, false),
    OPM(XX, 0xFC, 1, cpu_op_undefined, 0, true),
    OPM(XX, 0xFD, 1, cpu_op_undefined, 0, true),
    OPM(CPn, 0xFE, 2, cpu_op_CPn, 1, false),
    OPM(RST38, 0xFF, 3, cpu_op_unimplemented, 0, true)
};

static cpu_op_metadata_s cpu_op_metadata_cb[256] = {
    // 0x00
    OPM(RLCr_b, 0x0, 2, cpu_op_unimplemented, 0, false),
    OPM(RLCr_c, 0x01, 2, cpu_op_unimplemented, 0, false),
    OPM(RLCr_d, 0x02, 2, cpu_op_unimplemented, 0, false),
    OPM(RLCr_e, 0x03, 2, cpu_op_unimplemented, 0, false),
    OPM(RLCr_h, 0x04, 2, cpu_op_unimplemented, 0, false),
    OPM(RLCr_l, 0x05, 2, cpu_op_unimplemented, 0, false),
    OPM(RLCHL, 0x06, 4, cpu_op_unimplemented, 0, false),
    OPM(RLCr_a, 0x07, 2, cpu_op_unimplemented, 0, false),
    OPM(RRCr_b, 0x08, 2, cpu_op_unimplemented, 0, false),
    OPM(RRCr_c, 0x09, 2, cpu_op_unimplemented, 0, false),
    OPM(RRCr_d, 0x0A, 2, cpu_op_unimplemented, 0, false),
    OPM(RRCr_e, 0x0B, 2, cpu_op_unimplemented, 0, false),
    OPM(RRCr_h, 0x0C, 2, cpu_op_unimplemented, 0, false),
    OPM(RRCr_l, 0x0D, 2, cpu_op_unimplemented, 0, false),
    OPM(RRCHL, 0x0E, 4, cpu_op_unimplemented, 0, false),
    OPM(RRCr_a, 0x0F, 2, cpu_op_unimplemented, 0, false),

    // 0x10
    OPM(RLr_b, 0x10, 2, cpu_op_RLr_b, 0, false),
    OPM(RLr_c, 0x11, 2, cpu_op_RLr_c, 0, false),
    OPM(RLr_d, 0x12, 2, cpu_op_RLr_d, 0, false),
    OPM(RLr_e, 0x13, 2, cpu_op_RLr_e, 0, false),
    OPM(RLr_h, 0x14, 2, cpu_op_RLr_h, 0, false),
    OPM(RLr_l, 0x15, 2, cpu_op_RLr_l, 0, false),
    OPM(RLHL, 0x16, 4, cpu_op_unimplemented, 0, false),
    OPM(RLr_a, 0x17, 2, cpu_op_RLr_a, 0, false),
    OPM(RRr_b, 0x18, 2, cpu_op_unimplemented, 0, false),
    OPM(RRr_c, 0x19, 2, cpu_op_unimplemented, 0, false),
    OPM(RRr_d, 0x1A, 2, cpu_op_unimplemented, 0, false),
    OPM(RRr_e, 0x1B, 2, cpu_op_unimplemented, 0, false),
    OPM(RRr_h, 0x1C, 2, cpu_op_unimplemented, 0, false),
    OPM(RRr_l, 0x1D, 2, cpu_op_unimplemented, 0, false),
    OPM(RRHL, 0x1E, 4, cpu_op_unimplemented, 0, false),
    OPM(RRr_a, 0x1F, 2, cpu_op_unimplemented, 0, false),

    // 0x20
    OPM(SLAr_b, 0x20, 2, cpu_op_unimplemented, 0, false),
    OPM(SLAr_c, 0x21, 2, cpu_op_unimplemented, 0, false),
    OPM(SLAr_d, 0x22, 2, cpu_op_unimplemented, 0, false),
    OPM(SLAr_e, 0x23, 2, cpu_op_unimplemented, 0, false),
    OPM(SLAr_h, 0x24, 2, cpu_op_unimplemented, 0, false),
    OPM(SLAr_l, 0x25, 2, cpu_op_unimplemented, 0, false),
    OPM(XX, 0x26, 0, cpu_op_undefined, 0, true),
    OPM(SLAr_a, 0x27, 2, cpu_op_unimplemented, 0, false),
    OPM(SRAr_b, 0x28, 2, cpu_op_unimplemented, 0, false),
    OPM(SRAr_c, 0x29, 2, cpu_op_unimplemented, 0, false),
    OPM(SRAr_d, 0x2A, 2, cpu_op_unimplemented, 0, false),
    OPM(SRAr_e, 0x2B, 2, cpu_op_unimplemented, 0, false),
    OPM(SRAr_h, 0x2C, 2, cpu_op_unimplemented, 0, false),
    OPM(SRAr_l, 0x2D, 2, cpu_op_unimplemented, 0, false),
    OPM(XX, 0x2E, 0, cpu_op_undefined, 0, true),
    OPM(SRAr_a, 0x2F, 2, cpu_op_unimplemented, 0, false),

    // 0x30
    OPM(SWAPr_b, 0x30, 1, cpu_op_SWAPr_b, 0, false),
    OPM(SWAPr_c, 0x31, 1, cpu_op_SWAPr_c, 0, false),
    OPM(SWAPr_d, 0x32, 1, cpu_op_SWAPr_d, 0, false),
    OPM(SWAPr_e, 0x33, 1, cpu_op_SWAPr_e, 0, false),
    OPM(SWAPr_h, 0x34, 1, cpu_op_SWAPr_h, 0, false),
    OPM(SWAPr_l, 0x35, 1, cpu_op_SWAPr_l, 0, false),
    OPM(XX, 0x36, 0, cpu_op_undefined, 0, true),
    OPM(SWAPr_a, 0x37, 1, cpu_op_SWAPr_a, 0, false),
    OPM(SRLr_b, 0x38, 2, cpu_op_unimplemented, 0, false),
    OPM(SRLr_c, 0x39, 2, cpu_op_unimplemented, 0, false),
    OPM(SRLr_d, 0x3A, 2, cpu_op_unimplemented, 0, false),
    OPM(SRLr_e, 0x3B, 2, cpu_op_unimplemented, 0, false),
    OPM(SRLr_h, 0x3C, 2, cpu_op_unimplemented, 0, false),
    OPM(SRLr_l, 0x3D, 2, cpu_op_unimplemented, 0, false),
    OPM(XX, 0x3E, 0, cpu_op_undefined, 0, true),
    OPM(SRLr_a, 0x3F, 2, cpu_op_unimplemented, 0, false),

    // 0x40
    OPM(BIT0b, 0x40, 2, cpu_op_BIT0b, 0, false),
    OPM(BIT0c, 0x41, 2, cpu_op_BIT0c, 0, false),
    OPM(BIT0d, 0x42, 2, cpu_op_BIT0d, 0, false),
    OPM(BIT0e, 0x43, 2, cpu_op_BIT0e, 0, false),
    OPM(BIT0h, 0x44, 2, cpu_op_BIT0h, 0, false),
    OPM(BIT0l, 0x45, 2, cpu_op_BIT0l, 0, false),
    OPM(BIT0m, 0x46, 3, cpu_op_BIT0m, 0, false),
    OPM(BIT0a, 0x47, 2, cpu_op_BIT0a, 0, false),
    OPM(BIT1b, 0x48, 2, cpu_op_BIT1b, 0, false),
    OPM(BIT1c, 0x49, 2, cpu_op_BIT1c, 0, false),
    OPM(BIT1d, 0x4A, 2, cpu_op_BIT1d, 0, false),
    OPM(BIT1e, 0x4B, 2, cpu_op_BIT1e, 0, false),
    OPM(BIT1h, 0x4C, 2, cpu_op_BIT1h, 0, false),
    OPM(BIT1l, 0x4D, 2, cpu_op_BIT1l, 0, false),
    OPM(BIT1m, 0x4E, 3, cpu_op_BIT1m, 0, false),
    OPM(BIT1a, 0x4F, 2, cpu_op_BIT1a, 0, false),

    // 0x50
    OPM(BIT2b, 0x50, 2, cpu_op_BIT2b, 0, false),
    OPM(BIT2c, 0x51, 2, cpu_op_BIT2c, 0, false),
    OPM(BIT2d, 0x52, 2, cpu_op_BIT2d, 0, false),
    OPM(BIT2e, 0x53, 2, cpu_op_BIT2e, 0, false),
    OPM(BIT2h, 0x54, 2, cpu_op_BIT2h, 0, false),
    OPM(BIT2l, 0x55, 2, cpu_op_BIT2l, 0, false),
    OPM(BIT2m, 0x56, 3, cpu_op_BIT2m, 0, false),
    OPM(BIT2a, 0x57, 2, cpu_op_BIT2a, 0, false),
    OPM(BIT3b, 0x58, 2, cpu_op_BIT3b, 0, false),
    OPM(BIT3c, 0x59, 2, cpu_op_BIT3c, 0, false),
    OPM(BIT3d, 0x5A, 2, cpu_op_BIT3d, 0, false),
    OPM(BIT3e, 0x5B, 2, cpu_op_BIT3e, 0, false),
    OPM(BIT3h, 0x5C, 2, cpu_op_BIT3h, 0, false),
    OPM(BIT3l, 0x5D, 2, cpu_op_BIT3l, 0, false),
    OPM(BIT3m, 0x5E, 3, cpu_op_BIT3m, 0, false),
    OPM(BIT3a, 0x5F, 2, cpu_op_BIT3a, 0, false),

    // 0x60
    OPM(BIT4b, 0x60, 2, cpu_op_BIT4b, 0, false),
    OPM(BIT4c, 0x61, 2, cpu_op_BIT4c, 0, false),
    OPM(BIT4d, 0x62, 2, cpu_op_BIT4d, 0, false),
    OPM(BIT4e, 0x63, 2, cpu_op_BIT4e, 0, false),
    OPM(BIT4h, 0x64, 2, cpu_op_BIT4h, 0, false),
    OPM(BIT4l, 0x65, 2, cpu_op_BIT4l, 0, false),
    OPM(BIT4m, 0x66, 3, cpu_op_BIT4m, 0, false),
    OPM(BIT4a, 0x67, 2, cpu_op_BIT4a, 0, false),
    OPM(BIT5b, 0x68, 2, cpu_op_BIT5b, 0, false),
    OPM(BIT5c, 0x69, 2, cpu_op_BIT5c, 0, false),
    OPM(BIT5d, 0x6A, 2, cpu_op_BIT5d, 0, false),
    OPM(BIT5e, 0x6B, 2, cpu_op_BIT5e, 0, false),
    OPM(BIT5h, 0x6C, 2, cpu_op_BIT5h, 0, false),
    OPM(BIT5l, 0x6D, 2, cpu_op_BIT5l, 0, false),
    OPM(BIT5m, 0x6E, 3, cpu_op_BIT5m, 0, false),
    OPM(BIT5a, 0x6F, 2, cpu_op_BIT5a, 0, false),

    // 0x70
    OPM(BIT6b, 0x70, 2, cpu_op_BIT6b, 0, false),
    OPM(BIT6c, 0x71, 2, cpu_op_BIT6c, 0, false),
    OPM(BIT6d, 0x72, 2, cpu_op_BIT6d, 0, false),
    OPM(BIT6e, 0x73, 2, cpu_op_BIT6e, 0, false),
    OPM(BIT6h, 0x74, 2, cpu_op_BIT6h, 0, false),
    OPM(BIT6l, 0x75, 2, cpu_op_BIT6l, 0, false),
    OPM(BIT6m, 0x76, 3, cpu_op_BIT6m, 0, false),
    OPM(BIT6a, 0x77, 2, cpu_op_BIT6a, 0, false),
    OPM(BIT7b, 0x78, 2, cpu_op_BIT7b, 0, false),
    OPM(BIT7c, 0x79, 2, cpu_op_BIT7c, 0, false),
    OPM(BIT7d, 0x7A, 2, cpu_op_BIT7d, 0, false),
    OPM(BIT7e, 0x7B, 2, cpu_op_BIT7e, 0, false),
    OPM(BIT7h, 0x7C, 2, cpu_op_BIT7h, 0, false),
    OPM(BIT7l, 0x7D, 2, cpu_op_BIT7l, 0, false),
    OPM(BIT7m, 0x7E, 3, cpu_op_BIT7m, 0, false),
    OPM(BIT7a, 0x7F, 2, cpu_op_BIT7a, 0, false),

    // 0x80
    OPM(RES0b, 0x80, 2, cpu_op_unimplemented, 0, false),
    OPM(RES0c, 0x81, 2, cpu_op_unimplemented, 0, false),
    OPM(RES0d, 0x82, 2, cpu_op_unimplemented, 0, false),
    OPM(RES0e, 0x83, 2, cpu_op_unimplemented, 0, false),
    OPM(RES0h, 0x84, 2, cpu_op_unimplemented, 0, false),
    OPM(RES0l, 0x85, 2, cpu_op_unimplemented, 0, false),
    OPM(RES0m, 0x86, 4, cpu_op_unimplemented, 0, false),
    OPM(RES0a, 0x87, 2, cpu_op_unimplemented, 0, false),
    OPM(RES1b, 0x88, 2, cpu_op_unimplemented, 0, false),
    OPM(RES1c, 0x89, 2, cpu_op_unimplemented, 0, false),
    OPM(RES1d, 0x8A, 2, cpu_op_unimplemented, 0, false),
    OPM(RES1e, 0x8B, 2, cpu_op_unimplemented, 0, false),
    OPM(RES1h, 0x8C, 2, cpu_op_unimplemented, 0, false),
    OPM(RES1l, 0x8D, 2, cpu_op_unimplemented, 0, false),
    OPM(RES1m, 0x8E, 4, cpu_op_unimplemented, 0, false),
    OPM(RES1a, 0x8F, 2, cpu_op_unimplemented, 0, false),

    // 0x90
    OPM(RES2b, 0x90, 2, cpu_op_unimplemented, 0, false),
    OPM(RES2c, 0x91, 2, cpu_op_unimplemented, 0, false),
    OPM(RES2d, 0x92, 2, cpu_op_unimplemented, 0, false),
    OPM(RES2e, 0x93, 2, cpu_op_unimplemented, 0, false),
    OPM(RES2h, 0x94, 2, cpu_op_unimplemented, 0, false),
    OPM(RES2l, 0x95, 2, cpu_op_unimplemented, 0, false),
    OPM(RES2m, 0x96, 4, cpu_op_unimplemented, 0, false),
    OPM(RES2a, 0x97, 2, cpu_op_unimplemented, 0, false),
    OPM(RES3b, 0x98, 2, cpu_op_unimplemented, 0, false),
    OPM(RES3c, 0x99, 2, cpu_op_unimplemented, 0, false),
    OPM(RES3d, 0x9A, 2, cpu_op_unimplemented, 0, false),
    OPM(RES3e, 0x9B, 2, cpu_op_unimplemented, 0, false),
    OPM(RES3h, 0x9C, 2, cpu_op_unimplemented, 0, false),
    OPM(RES3l, 0x9D, 2, cpu_op_unimplemented, 0, false),
    OPM(RES3m, 0x9E, 4, cpu_op_unimplemented, 0, false),
    OPM(RES3a, 0x9F, 2, cpu_op_unimplemented, 0, false),

    // 0xA0
    OPM(RES4b, 0xA0, 2, cpu_op_unimplemented, 0, false),
    OPM(RES4c, 0xA1, 2, cpu_op_unimplemented, 0, false),
    OPM(RES4d, 0xA2, 2, cpu_op_unimplemented, 0, false),
    OPM(RES4e, 0xA3, 2, cpu_op_unimplemented, 0, false),
    OPM(RES4h, 0xA4, 2, cpu_op_unimplemented, 0, false),
    OPM(RES4l, 0xA5, 2, cpu_op_unimplemented, 0, false),
    OPM(RES4m, 0xA6, 4, cpu_op_unimplemented, 0, false),
    OPM(RES4a, 0xA7, 2, cpu_op_unimplemented, 0, false),
    OPM(RES5b, 0xA8, 2, cpu_op_unimplemented, 0, false),
    OPM(RES5c, 0xA9, 2, cpu_op_unimplemented, 0, false),
    OPM(RES5d, 0xAA, 2, cpu_op_unimplemented, 0, false),
    OPM(RES5e, 0xAB, 2, cpu_op_unimplemented, 0, false),
    OPM(RES5h, 0xAC, 2, cpu_op_unimplemented, 0, false),
    OPM(RES5l, 0xAD, 2, cpu_op_unimplemented, 0, false),
    OPM(RES5m, 0xAE, 4, cpu_op_unimplemented, 0, false),
    OPM(RES5a, 0xAF, 2, cpu_op_unimplemented, 0, false),

    // 0xB0
    OPM(RES6b, 0xB0, 2, cpu_op_unimplemented, 0, false),
    OPM(RES6c, 0xB1, 2, cpu_op_unimplemented, 0, false),
    OPM(RES6d, 0xB2, 2, cpu_op_unimplemented, 0, false),
    OPM(RES6e, 0xB3, 2, cpu_op_unimplemented, 0, false),
    OPM(RES6h, 0xB4, 2, cpu_op_unimplemented, 0, false),
    OPM(RES6l, 0xB5, 2, cpu_op_unimplemented, 0, false),
    OPM(RES6m, 0xB6, 4, cpu_op_unimplemented, 0, false),
    OPM(RES6a, 0xB7, 2, cpu_op_unimplemented, 0, false),
    OPM(RES7b, 0xB8, 2, cpu_op_unimplemented, 0, false),
    OPM(RES7c, 0xB9, 2, cpu_op_unimplemented, 0, false),
    OPM(RES7d, 0xBA, 2, cpu_op_unimplemented, 0, false),
    OPM(RES7e, 0xBB, 2, cpu_op_unimplemented, 0, false),
    OPM(RES7h, 0xBC, 2, cpu_op_unimplemented, 0, false),
    OPM(RES7l, 0xBD, 2, cpu_op_unimplemented, 0, false),
    OPM(RES7m, 0xBE, 4, cpu_op_unimplemented, 0, false),
    OPM(RES7a, 0xBF, 2, cpu_op_unimplemented, 0, false),

    // 0xC0
    OPM(SET0b, 0xC0, 2, cpu_op_unimplemented, 0, false),
    OPM(SET0c, 0xC1, 2, cpu_op_unimplemented, 0, false),
    OPM(SET0d, 0xC2, 2, cpu_op_unimplemented, 0, false),
    OPM(SET0e, 0xC3, 2, cpu_op_unimplemented, 0, false),
    OPM(SET0h, 0xC4, 2, cpu_op_unimplemented, 0, false),
    OPM(SET0l, 0xC5, 2, cpu_op_unimplemented, 0, false),
    OPM(SET0m, 0xC6, 4, cpu_op_unimplemented, 0, false),
    OPM(SET0a, 0xC7, 2, cpu_op_unimplemented, 0, false),
    OPM(SET1b, 0xC8, 2, cpu_op_unimplemented, 0, false),
    OPM(SET1c, 0xC9, 2, cpu_op_unimplemented, 0, false),
    OPM(SET1d, 0xCA, 2, cpu_op_unimplemented, 0, false),
    OPM(SET1e, 0xCB, 2, cpu_op_unimplemented, 0, false),
    OPM(SET1h, 0xCC, 2, cpu_op_unimplemented, 0, false),
    OPM(SET1l, 0xCD, 2, cpu_op_unimplemented, 0, false),
    OPM(SET1m, 0xCE, 4, cpu_op_unimplemented, 0, false),
    OPM(SET1a, 0xCF, 2, cpu_op_unimplemented, 0, false),

    // 0xD0
    OPM(SET2b, 0xD0, 2, cpu_op_unimplemented, 0, false),
    OPM(SET2c, 0xD1, 2, cpu_op_unimplemented, 0, false),
    OPM(SET2d, 0xD2, 2, cpu_op_unimplemented, 0, false),
    OPM(SET2e, 0xD3, 2, cpu_op_unimplemented, 0, false),
    OPM(SET2h, 0xD4, 2, cpu_op_unimplemented, 0, false),
    OPM(SET2l, 0xD5, 2, cpu_op_unimplemented, 0, false),
    OPM(SET2m, 0xD6, 4, cpu_op_unimplemented, 0, false),
    OPM(SET2a, 0xD7, 2, cpu_op_unimplemented, 0, false),
    OPM(SET3b, 0xD8, 2, cpu_op_unimplemented, 0, false),
    OPM(SET3c, 0xD9, 2, cpu_op_unimplemented, 0, false),
    OPM(SET3d, 0xDA, 2, cpu_op_unimplemented, 0, false),
    OPM(SET3e, 0xDB, 2, cpu_op_unimplemented, 0, false),
    OPM(SET3h, 0xDC, 2, cpu_op_unimplemented, 0, false),
    OPM(SET3l, 0xDD, 2, cpu_op_unimplemented, 0, false),
    OPM(SET3m, 0xDE, 4, cpu_op_unimplemented, 0, false),
    OPM(SET3a, 0xDF, 2, cpu_op_unimplemented, 0, false),

    // 0xE0
    OPM(SET4b, 0xE0, 2, cpu_op_unimplemented, 0, false),
    OPM(SET4c, 0xE1, 2, cpu_op_unimplemented, 0, false),
    OPM(SET4d, 0xE2, 2, cpu_op_unimplemented, 0, false),
    OPM(SET4e, 0xE3, 2, cpu_op_unimplemented, 0, false),
    OPM(SET4h, 0xE4, 2, cpu_op_unimplemented, 0, false),
    OPM(SET4l, 0xE5, 2, cpu_op_unimplemented, 0, false),
    OPM(SET4m, 0xE6, 4, cpu_op_unimplemented, 0, false),
    OPM(SET4a, 0xE7, 2, cpu_op_unimplemented, 0, false),
    OPM(SET5b, 0xE8, 2, cpu_op_unimplemented, 0, false),
    OPM(SET5c, 0xE9, 2, cpu_op_unimplemented, 0, false),
    OPM(SET5d, 0xEA, 2, cpu_op_unimplemented, 0, false),
    OPM(SET5e, 0xEB, 2, cpu_op_unimplemented, 0, false),
    OPM(SET5h, 0xEC, 2, cpu_op_unimplemented, 0, false),
    OPM(SET5l, 0xED, 2, cpu_op_unimplemented, 0, false),
    OPM(SET5m, 0xEE, 4, cpu_op_unimplemented, 0, false),
    OPM(SET5a, 0xEF, 2, cpu_op_unimplemented, 0, false),

    // 0xF0
    OPM(SET6b, 0xF0, 2, cpu_op_unimplemented, 0, false),
    OPM(SET6c, 0xF1, 2, cpu_op_unimplemented, 0, false),
    OPM(SET6d, 0xF2, 2, cpu_op_unimplemented, 0, false),
    OPM(SET6e, 0xF3, 2, cpu_op_unimplemented, 0, false),
    OPM(SET6h, 0xF4, 2, cpu_op_unimplemented, 0, false),
    OPM(SET6l, 0xF5, 2, cpu_op_unimplemented, 0, false),
    OPM(SET6m, 0xF6, 4, cpu_op_unimplemented, 0, false),
    OPM(SET6a, 0xF7, 2, cpu_op_unimplemented, 0, false),
    OPM(SET7b, 0xF8, 2, cpu_op_unimplemented, 0, false),
    OPM(SET7c, 0xF9, 2, cpu_op_unimplemented, 0, false),
    OPM(SET7d, 0xFA, 2, cpu_op_unimplemented, 0, false),
    OPM(SET7e, 0xFB, 2, cpu_op_unimplemented, 0, false),
    OPM(SET7h, 0xFC, 2, cpu_op_unimplemented, 0, false),
    OPM(SET7l, 0xFD, 2, cpu_op_unimplemented, 0, false),
    OPM(SET7m, 0xFE, 4, cpu_op_unimplemented, 0, false),
    OPM(SET7a, 0xFF, 2, cpu_op_unimplemented, 0, false)
};

#undef OPM
#endif
