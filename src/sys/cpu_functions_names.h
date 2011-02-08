#ifndef __LLGB_CPU_FUNCTIONS_NAMES_H
#define __LLGB_CPU_FUNCTIONS_NAMES_H

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


static const char* cpu_op_names_basic[256] = {
    // 00
    "cpu_op_NOP",		"cpu_op_LDBCnn",	"cpu_op_LDBCmA",	"cpu_op_INCBC",
    "cpu_op_INCr_b",	"cpu_op_DECr_b",	"cpu_op_LDrn_b",	"cpu_op_RLCA",
    "cpu_op_LDmmSP",	"cpu_op_ADDHLBC",	"cpu_op_LDABCm",	"cpu_op_DECBC",
    "cpu_op_INCr_c",	"cpu_op_DECr_c",	"cpu_op_LDrn_c",	"cpu_op_RRCA",
    // 10
    "cpu_op_DJNZn",	"cpu_op_LDDEnn",	"cpu_op_LDDEmA",	"cpu_op_INCDE",
    "cpu_op_INCr_d",	"cpu_op_DECr_d",	"cpu_op_LDrn_d",	"cpu_op_RLA",
    "cpu_op_JRn",		"cpu_op_ADDHLDE",	"cpu_op_LDADEm",	"cpu_op_DECDE",
    "cpu_op_INCr_e",	"cpu_op_DECr_e",	"cpu_op_LDrn_e",	"cpu_op_RRA",
    // 20
    "cpu_op_JRNZn",	"cpu_op_LDHLnn",	"cpu_op_LDHLIA",	"cpu_op_INCHL",
    "cpu_op_INCr_h",	"cpu_op_DECr_h",	"cpu_op_LDrn_h",	"cpu_op_DAA",
    "cpu_op_JRZn",	"cpu_op_ADDHLHL",	"cpu_op_LDAHLI",	"cpu_op_DECHL",
    "cpu_op_INCr_l",	"cpu_op_DECr_l",	"cpu_op_LDrn_l",	"cpu_op_CPL",
    // 30
    "cpu_op_JRNCn",	"cpu_op_LDSPnn",	"cpu_op_LDHLDA",	"cpu_op_INCSP",
    "cpu_op_INCHLm",	"cpu_op_DECHLm",	"cpu_op_LDHLmn",	"cpu_op_SCF",
    "cpu_op_JRCn",	"cpu_op_ADDHLSP",	"cpu_op_LDAHLD",	"cpu_op_DECSP",
    "cpu_op_INCr_a",	"cpu_op_DECr_a",	"cpu_op_LDrn_a",	"cpu_op_CCF",
    // 40
    "cpu_op_LDrr_bb",	"cpu_op_LDrr_bc",	"cpu_op_LDrr_bd",	"cpu_op_LDrr_be",
    "cpu_op_LDrr_bh",	"cpu_op_LDrr_bl",	"cpu_op_LDrHLm_b",	"cpu_op_LDrr_ba",
    "cpu_op_LDrr_cb",	"cpu_op_LDrr_cc",	"cpu_op_LDrr_cd",	"cpu_op_LDrr_ce",
    "cpu_op_LDrr_ch",	"cpu_op_LDrr_cl",	"cpu_op_LDrHLm_c",	"cpu_op_LDrr_ca",
    // 50
    "cpu_op_LDrr_db",	"cpu_op_LDrr_dc",	"cpu_op_LDrr_dd",	"cpu_op_LDrr_de",
    "cpu_op_LDrr_dh",	"cpu_op_LDrr_dl",	"cpu_op_LDrHLm_d",	"cpu_op_LDrr_da",
    "cpu_op_LDrr_eb",	"cpu_op_LDrr_ec",	"cpu_op_LDrr_ed",	"cpu_op_LDrr_ee",
    "cpu_op_LDrr_eh",	"cpu_op_LDrr_el",	"cpu_op_LDrHLm_e",	"cpu_op_LDrr_ea",
    // 60
    "cpu_op_LDrr_hb",	"cpu_op_LDrr_hc",	"cpu_op_LDrr_hd",	"cpu_op_LDrr_he",
    "cpu_op_LDrr_hh",	"cpu_op_LDrr_hl",	"cpu_op_LDrHLm_h",	"cpu_op_LDrr_ha",
    "cpu_op_LDrr_lb",	"cpu_op_LDrr_lc",	"cpu_op_LDrr_ld",	"cpu_op_LDrr_le",
    "cpu_op_LDrr_lh",	"cpu_op_LDrr_ll",	"cpu_op_LDrHLm_l",	"cpu_op_LDrr_la",
    // 70
    "cpu_op_LDHLmr_b",	"cpu_op_LDHLmr_c",	"cpu_op_LDHLmr_d",	"cpu_op_LDHLmr_e",
    "cpu_op_LDHLmr_h",	"cpu_op_LDHLmr_l",	"cpu_op_HALT",		"cpu_op_LDHLmr_a",
    "cpu_op_LDrr_ab",	"cpu_op_LDrr_ac",	"cpu_op_LDrr_ad",	"cpu_op_LDrr_ae",
    "cpu_op_LDrr_ah",	"cpu_op_LDrr_al",	"cpu_op_LDrHLm_a",	"cpu_op_LDrr_aa",
    // 80
    "cpu_op_ADDr_b",	"cpu_op_ADDr_c",	"cpu_op_ADDr_d",	"cpu_op_ADDr_e",
    "cpu_op_ADDr_h",	"cpu_op_ADDr_l",	"cpu_op_ADDHL",		"cpu_op_ADDr_a",
    "cpu_op_ADCr_b",	"cpu_op_ADCr_c",	"cpu_op_ADCr_d",	"cpu_op_ADCr_e",
    "cpu_op_ADCr_h",	"cpu_op_ADCr_l",	"cpu_op_ADCHL",		"cpu_op_ADCr_a",
    // 90
    "cpu_op_SUBr_b",	"cpu_op_SUBr_c",	"cpu_op_SUBr_d",	"cpu_op_SUBr_e",
    "cpu_op_SUBr_h",	"cpu_op_SUBr_l",	"cpu_op_SUBHL",		"cpu_op_SUBr_a",
    "cpu_op_SBCr_b",	"cpu_op_SBCr_c",	"cpu_op_SBCr_d",	"cpu_op_SBCr_e",
    "cpu_op_SBCr_h",	"cpu_op_SBCr_l",	"cpu_op_SBCHL",		"cpu_op_SBCr_a",
    // A0
    "cpu_op_ANDr_b",	"cpu_op_ANDr_c",	"cpu_op_ANDr_d",	"cpu_op_ANDr_e",
    "cpu_op_ANDr_h",	"cpu_op_ANDr_l",	"cpu_op_ANDHL",		"cpu_op_ANDr_a",
    "cpu_op_XORr_b",	"cpu_op_XORr_c",	"cpu_op_XORr_d",	"cpu_op_XORr_e",
    "cpu_op_XORr_h",	"cpu_op_XORr_l",	"cpu_op_XORHL",		"cpu_op_XORr_a",
    // B0
    "cpu_op_ORr_b",	"cpu_op_ORr_c",		"cpu_op_ORr_d",		"cpu_op_ORr_e",
    "cpu_op_ORr_h",	"cpu_op_ORr_l",		"cpu_op_ORHL",		"cpu_op_ORr_a",
    "cpu_op_CPr_b",	"cpu_op_CPr_c",		"cpu_op_CPr_d",		"cpu_op_CPr_e",
    "cpu_op_CPr_h",	"cpu_op_CPr_l",		"cpu_op_CPHL",		"cpu_op_CPr_a",
    // C0
    "cpu_op_RETNZ",	"cpu_op_POPBC",		"cpu_op_JPNZnn",	"cpu_op_JPnn",
    "cpu_op_CALLNZnn",	"cpu_op_PUSHBC",	"cpu_op_ADDn",		"cpu_op_RST00",
    "cpu_op_RETZ",	"cpu_op_RET",		"cpu_op_JPZnn",		"cpu_op_MAPcb",
    "cpu_op_CALLZnn",	"cpu_op_CALLnn",	"cpu_op_ADCn",		"cpu_op_RST08",
    // D0
    "cpu_op_RETNC",	"cpu_op_POPDE",		"cpu_op_JPNCnn",	"cpu_op_undefined",
    "cpu_op_CALLNCnn",	"cpu_op_PUSHDE",	"cpu_op_SUBn",		"cpu_op_RST10",
    "cpu_op_RETC",	"cpu_op_RETI",		"cpu_op_JPCnn",		"cpu_op_undefined",
    "cpu_op_CALLCnn",	"cpu_op_undefined",		"cpu_op_SBCn",		"cpu_op_RST18",
    // E0
    "cpu_op_LDIOnA",	"cpu_op_POPHL",		"cpu_op_LDIOCA",	"cpu_op_undefined",
    "cpu_op_undefined",		"cpu_op_PUSHHL",	"cpu_op_ANDn",		"cpu_op_RST20",
    "cpu_op_ADDSPn",	"cpu_op_JPHL",		"cpu_op_LDmmA",		"cpu_op_undefined",
    "cpu_op_undefined",		"cpu_op_undefined",		"cpu_op_XORn",		"cpu_op_RST28",
    // F0
    "cpu_op_LDAIOn",	"cpu_op_POPAF",		"cpu_op_LDAIOC",	"cpu_op_DI",
    "cpu_op_undefined",		"cpu_op_PUSHAF",	"cpu_op_ORn",		"cpu_op_RST30",
    "cpu_op_LDHLSPn",	"cpu_op_undefined",		"cpu_op_LDAmm",		"cpu_op_EI",
    "cpu_op_undefined",		"cpu_op_undefined",		"cpu_op_CPn",		"cpu_op_RST38"
};

static const char* cpu_op_names_cb[256] = {
    // CB00
    "cpu_op_RLCr_b",	"cpu_op_RLCr_c",	"cpu_op_RLCr_d",	"cpu_op_RLCr_e",
    "cpu_op_RLCr_h",	"cpu_op_RLCr_l",	"cpu_op_RLCHL",		"cpu_op_RLCr_a",
    "cpu_op_RRCr_b",	"cpu_op_RRCr_c",	"cpu_op_RRCr_d",	"cpu_op_RRCr_e",
    "cpu_op_RRCr_h",	"cpu_op_RRCr_l",	"cpu_op_RRCHL",		"cpu_op_RRCr_a",
    // CB10
    "cpu_op_RLr_b",	"cpu_op_RLr_c",		"cpu_op_RLr_d",		"cpu_op_RLr_e",
    "cpu_op_RLr_h",	"cpu_op_RLr_l",		"cpu_op_RLHL",		"cpu_op_RLr_a",
    "cpu_op_RRr_b",	"cpu_op_RRr_c",		"cpu_op_RRr_d",		"cpu_op_RRr_e",
    "cpu_op_RRr_h",	"cpu_op_RRr_l",		"cpu_op_RRHL",		"cpu_op_RRr_a",
    // CB20
    "cpu_op_SLAr_b",	"cpu_op_SLAr_c",	"cpu_op_SLAr_d",	"cpu_op_SLAr_e",
    "cpu_op_SLAr_h",	"cpu_op_SLAr_l",	"cpu_op_undefined",		"cpu_op_SLAr_a",
    "cpu_op_SRAr_b",	"cpu_op_SRAr_c",	"cpu_op_SRAr_d",	"cpu_op_SRAr_e",
    "cpu_op_SRAr_h",	"cpu_op_SRAr_l",	"cpu_op_undefined",		"cpu_op_SRAr_a",
    // CB30
    "cpu_op_SWAPr_b",	"cpu_op_SWAPr_c",	"cpu_op_SWAPr_d",	"cpu_op_SWAPr_e",
    "cpu_op_SWAPr_h",	"cpu_op_SWAPr_l",	"cpu_op_undefined",		"cpu_op_SWAPr_a",
    "cpu_op_SRLr_b",	"cpu_op_SRLr_c",	"cpu_op_SRLr_d",	"cpu_op_SRLr_e",
    "cpu_op_SRLr_h",	"cpu_op_SRLr_l",	"cpu_op_undefined",		"cpu_op_SRLr_a",
    // CB40
    "cpu_op_BIT0b",	"cpu_op_BIT0c",		"cpu_op_BIT0d",		"cpu_op_BIT0e",
    "cpu_op_BIT0h",	"cpu_op_BIT0l",		"cpu_op_BIT0m",		"cpu_op_BIT0a",
    "cpu_op_BIT1b",	"cpu_op_BIT1c",		"cpu_op_BIT1d",		"cpu_op_BIT1e",
    "cpu_op_BIT1h",	"cpu_op_BIT1l",		"cpu_op_BIT1m",		"cpu_op_BIT1a",
    // CB50
    "cpu_op_BIT2b",	"cpu_op_BIT2c",		"cpu_op_BIT2d",		"cpu_op_BIT2e",
    "cpu_op_BIT2h",	"cpu_op_BIT2l",		"cpu_op_BIT2m",		"cpu_op_BIT2a",
    "cpu_op_BIT3b",	"cpu_op_BIT3c",		"cpu_op_BIT3d",		"cpu_op_BIT3e",
    "cpu_op_BIT3h",	"cpu_op_BIT3l",		"cpu_op_BIT3m",		"cpu_op_BIT3a",
    // CB60
    "cpu_op_BIT4b",	"cpu_op_BIT4c",		"cpu_op_BIT4d",		"cpu_op_BIT4e",
    "cpu_op_BIT4h",	"cpu_op_BIT4l",		"cpu_op_BIT4m",		"cpu_op_BIT4a",
    "cpu_op_BIT5b",	"cpu_op_BIT5c",		"cpu_op_BIT5d",		"cpu_op_BIT5e",
    "cpu_op_BIT5h",	"cpu_op_BIT5l",		"cpu_op_BIT5m",		"cpu_op_BIT5a",
    // CB70
    "cpu_op_BIT6b",	"cpu_op_BIT6c",		"cpu_op_BIT6d",		"cpu_op_BIT6e",
    "cpu_op_BIT6h",	"cpu_op_BIT6l",		"cpu_op_BIT6m",		"cpu_op_BIT6a",
    "cpu_op_BIT7b",	"cpu_op_BIT7c",		"cpu_op_BIT7d",		"cpu_op_BIT7e",
    "cpu_op_BIT7h",	"cpu_op_BIT7l",		"cpu_op_BIT7m",		"cpu_op_BIT7a",
    // CB80
    "cpu_op_RES0b",	"cpu_op_RES0c",		"cpu_op_RES0d",		"cpu_op_RES0e",
    "cpu_op_RES0h",	"cpu_op_RES0l",		"cpu_op_RES0m",		"cpu_op_RES0a",
    "cpu_op_RES1b",	"cpu_op_RES1c",		"cpu_op_RES1d",		"cpu_op_RES1e",
    "cpu_op_RES1h",	"cpu_op_RES1l",		"cpu_op_RES1m",		"cpu_op_RES1a",
    // CB90
    "cpu_op_RES2b",	"cpu_op_RES2c",		"cpu_op_RES2d",		"cpu_op_RES2e",
    "cpu_op_RES2h",	"cpu_op_RES2l",		"cpu_op_RES2m",		"cpu_op_RES2a",
    "cpu_op_RES3b",	"cpu_op_RES3c",		"cpu_op_RES3d",		"cpu_op_RES3e",
    "cpu_op_RES3h",	"cpu_op_RES3l",		"cpu_op_RES3m",		"cpu_op_RES3a",
    // CBA0
    "cpu_op_RES4b",	"cpu_op_RES4c",		"cpu_op_RES4d",		"cpu_op_RES4e",
    "cpu_op_RES4h",	"cpu_op_RES4l",		"cpu_op_RES4m",		"cpu_op_RES4a",
    "cpu_op_RES5b",	"cpu_op_RES5c",		"cpu_op_RES5d",		"cpu_op_RES5e",
    "cpu_op_RES5h",	"cpu_op_RES5l",		"cpu_op_RES5m",		"cpu_op_RES5a",
    // CBB0
    "cpu_op_RES6b",	"cpu_op_RES6c",		"cpu_op_RES6d",		"cpu_op_RES6e",
    "cpu_op_RES6h",	"cpu_op_RES6l",		"cpu_op_RES6m",		"cpu_op_RES6a",
    "cpu_op_RES7b",	"cpu_op_RES7c",		"cpu_op_RES7d",		"cpu_op_RES7e",
    "cpu_op_RES7h",	"cpu_op_RES7l",		"cpu_op_RES7m",		"cpu_op_RES7a",
    // CBC0
    "cpu_op_SET0b",	"cpu_op_SET0c",		"cpu_op_SET0d",		"cpu_op_SET0e",
    "cpu_op_SET0h",	"cpu_op_SET0l",		"cpu_op_SET0m",		"cpu_op_SET0a",
    "cpu_op_SET1b",	"cpu_op_SET1c",		"cpu_op_SET1d",		"cpu_op_SET1e",
    "cpu_op_SET1h",	"cpu_op_SET1l",		"cpu_op_SET1m",		"cpu_op_SET1a",
    // CBD0
    "cpu_op_SET2b",	"cpu_op_SET2c",		"cpu_op_SET2d",		"cpu_op_SET2e",
    "cpu_op_SET2h",	"cpu_op_SET2l",		"cpu_op_SET2m",		"cpu_op_SET2a",
    "cpu_op_SET3b",	"cpu_op_SET3c",		"cpu_op_SET3d",		"cpu_op_SET3e",
    "cpu_op_SET3h",	"cpu_op_SET3l",		"cpu_op_SET3m",		"cpu_op_SET3a",
    // CBE0
    "cpu_op_SET4b",	"cpu_op_SET4c",		"cpu_op_SET4d",		"cpu_op_SET4e",
    "cpu_op_SET4h",	"cpu_op_SET4l",		"cpu_op_SET4m",		"cpu_op_SET4a",
    "cpu_op_SET5b",	"cpu_op_SET5c",		"cpu_op_SET5d",		"cpu_op_SET5e",
    "cpu_op_SET5h",	"cpu_op_SET5l",		"cpu_op_SET5m",		"cpu_op_SET5a",
    // CBF0
    "cpu_op_SET6b",	"cpu_op_SET6c",		"cpu_op_SET6d",		"cpu_op_SET6e",
    "cpu_op_SET6h",	"cpu_op_SET6l",		"cpu_op_SET6m",		"cpu_op_SET6a",
    "cpu_op_SET7b",	"cpu_op_SET7c",		"cpu_op_SET7d",		"cpu_op_SET7e",
    "cpu_op_SET7h",	"cpu_op_SET7l",		"cpu_op_SET7m",		"cpu_op_SET7a",
};
#endif