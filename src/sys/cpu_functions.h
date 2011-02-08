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


#include "system.h"
#define CPU_OP(name) void cpu_op_##name(system_t* state)

// -- Helper Functions -- //
/// Prints a simple Hello World
void cpu_hello();

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
static void* cpu_ops_basic[256] = {
    // 00
    OP(NOP), OP(LDBCnn), OP(unimplemented), OP(INCBC),
    OP(INCr_b), OP(DECr_b), OP(LDrn_b), OP(unimplemented),
    OP(unimplemented), OP(ADDHLBC), OP(LDABCm), OP(DECBC),
    OP(INCr_c), OP(DECr_c), OP(LDrn_c), OP(unimplemented),
    // 10
    OP(unimplemented), OP(LDDEnn), OP(unimplemented), OP(INCDE),
    OP(INCr_d), OP(DECr_d), OP(LDrn_d), OP(RLA),
    OP(JRn), OP(ADDHLDE), OP(LDADEm), OP(DECDE),
    OP(INCr_e), OP(DECr_e), OP(LDrn_e), OP(unimplemented),
    // 20
    OP(JRNZn), OP(LDHLnn), OP(LDHLIA), OP(INCHL),
    OP(INCr_h), OP(DECr_h), OP(LDrn_h), OP(unimplemented),
    OP(JRZn), OP(ADDHLHL), OP(LDAHLI), OP(DECHL),
    OP(INCr_l), OP(DECr_l), OP(LDrn_l), OP(unimplemented),
    // 30
    OP(JRNCn), OP(LDSPnn), OP(LDHLDA), OP(INCSP),
    OP(INCHLm), OP(DECHLm), OP(LDHLmn), OP(unimplemented),
    OP(JRCn), OP(unimplemented), OP(LDAHLD), OP(DECSP),
    OP(INCr_a), OP(DECr_a), OP(LDrn_a), OP(unimplemented),
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
    OP(SUBr_b), OP(SUBr_c), OP(SUBr_d), OP(SUBr_e),
    OP(SUBr_h), OP(SUBr_l), OP(unimplemented), OP(SUBr_a),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // A0
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(XORr_b), OP(XORr_c), OP(XORr_d), OP(XORr_e),
    OP(XORr_h), OP(XORr_l), OP(unimplemented), OP(XORr_a),
    // B0
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(CPr_b), OP(CPr_c), OP(CPr_d), OP(CPr_e),
    OP(CPr_h), OP(CPr_l), OP(CPHL), OP(CPr_a),
    // C0
    OP(RETNZ), OP(POPBC), OP(JPNZnn), OP(JPnn),
    OP(unimplemented), OP(PUSHBC), OP(unimplemented), OP(unimplemented),
    OP(RETZ), OP(RET), OP(JPZnn), cpu_op_cb,
    OP(unimplemented), OP(CALLnn), OP(unimplemented), OP(unimplemented),
    // D0
    OP(RETNC), OP(POPDE), OP(JPNCnn), OP(undefined),
    OP(unimplemented), OP(PUSHDE), OP(unimplemented), OP(unimplemented),
    OP(RETC), OP(unimplemented), OP(JPCnn), OP(undefined),
    OP(unimplemented), OP(undefined), OP(unimplemented), OP(unimplemented),
    // E0
    OP(LDIOnA), OP(POPHL), OP(LDIOCA), OP(undefined),
    OP(undefined), OP(PUSHHL), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(JPHL), OP(LDmmA), OP(undefined),
    OP(undefined), OP(undefined), OP(unimplemented), OP(unimplemented),
    // F0
    OP(LDAIOn), OP(POPAF), OP(LDAIOC), OP(DI),
    OP(undefined), OP(PUSHAF), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(undefined), OP(LDAmm), OP(unimplemented),
    OP(undefined), OP(undefined), OP(CPn), OP(unimplemented)
};

static void* cpu_ops_cb[256] = {
    // 00
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    // 10
    OP(RLr_b), OP(RLr_c), OP(RLr_d), OP(RLr_e),
    OP(RLr_h), OP(RLr_l), OP(unimplemented), OP(RLr_a),
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
    OP(BIT0b), OP(BIT0c), OP(BIT0d), OP(BIT0e),
    OP(BIT0h), OP(BIT0l), OP(BIT0m), OP(BIT0a),
    OP(BIT1b), OP(BIT1c), OP(BIT1d), OP(BIT1e),
    OP(BIT1h), OP(BIT1l), OP(BIT1m), OP(BIT1a),
    // 50
    OP(BIT2b), OP(BIT2c), OP(BIT2d), OP(BIT2e),
    OP(BIT2h), OP(BIT2l), OP(BIT2m), OP(BIT2a),
    OP(BIT3b), OP(BIT3c), OP(BIT3d), OP(BIT3e),
    OP(BIT3h), OP(BIT3l), OP(BIT3m), OP(BIT3a),
    // 60
    OP(BIT4b), OP(BIT4c), OP(BIT4d), OP(BIT4e),
    OP(BIT4h), OP(BIT4l), OP(BIT4m), OP(BIT4a),
    OP(BIT5b), OP(BIT5c), OP(BIT5d), OP(BIT5e),
    OP(BIT5h), OP(BIT5l), OP(BIT5m), OP(BIT5a),
    // 70
    OP(BIT6b), OP(BIT6c), OP(BIT6d), OP(BIT6e),
    OP(BIT6h), OP(BIT6l), OP(BIT6m), OP(BIT6a),
    OP(BIT7b), OP(BIT7c), OP(BIT7d), OP(BIT7e),
    OP(BIT7h), OP(BIT7l), OP(BIT7m), OP(BIT7a),
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
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(DI),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(EI),
    OP(unimplemented), OP(unimplemented), OP(unimplemented), OP(unimplemented)
};
#undef OP
#endif
