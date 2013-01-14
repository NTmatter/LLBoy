#ifndef __LLGB_CART_METADATA_H
#define __LLGB_CART_METADATA_H
/*
 Copyright (c) 2011 Thomas Johnson
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

/// Provide information about a particular location in Cart memory.
/// This is used to store and build instruction sequences.
typedef struct {
    bool isVisited;
    bool isInstruction;
    bool isLanding;
} cart_metadata_s;

#define MD(offset, value, visited, instruction, landing) \
	{.isVisited = visited, .isInstruction = instruction, .isLanding = landing}
static cart_metadata_s bios_metadata[] = {
	// 0x00
	MD(0x00, 0x31, true, true, true),
	MD(0x01, 0xFE, true, false, false),
	MD(0x02, 0xFF, true, false, false),
	MD(0x03, 0xAF, true, true, false),
	MD(0x04, 0x21, true, true, false),
	MD(0x05, 0xFF, true, false, false),
	MD(0x06, 0x9F, true, false, false),
	MD(0x07, 0x32, true, true, true),
	MD(0x08, 0xCB, true, true, false),
	MD(0x09, 0x7C, true, false, false),
	MD(0x0A, 0x20, true, true, false),
	MD(0x0B, 0xFB, true, false, false),
	MD(0x0C, 0x21, true, true, false),
	MD(0x0D, 0x26, true, false, false),
	MD(0x0E, 0xFF, true, false, false),
	MD(0x0F, 0x0E, true, true, false),

	// 0x10
	MD(0x10, 0x11, true, false, false),
	MD(0x11, 0x3E, true, true, false),
	MD(0x12, 0x80, true, false, false),
	MD(0x13, 0x32, true, true, false),
	MD(0x14, 0xE2, true, true, false),
	MD(0x15, 0x0C, true, true, false),
	MD(0x16, 0x3E, true, true, false),
	MD(0x17, 0xF3, true, false, false),
	MD(0x18, 0xE2, true, true, false),
	MD(0x19, 0x32, true, true, false),
	MD(0x1A, 0x3E, true, true, false),
	MD(0x1B, 0x77, true, false, false),
	MD(0x1C, 0x77, true, true, false),
	MD(0x1D, 0x3E, true, true, false),
	MD(0x1E, 0xFC, true, false, false),
	MD(0x1F, 0xE0, true, true, false),

	// 0x20
	MD(0x20, 0x47, true, false, false),
	MD(0x21, 0x11, true, true, false),
	MD(0x22, 0x04, true, false, false),
	MD(0x23, 0x01, true, false, false),
	MD(0x24, 0x21, true, true, false),
	MD(0x25, 0x10, true, false, false),
	MD(0x26, 0x80, true, false, false),
	MD(0x27, 0x1A, true, true, false),
	MD(0x28, 0xCD, true, true, false),
	MD(0x29, 0x95, true, false, false),
	MD(0x2A, 0x00, true, false, false),
	MD(0x2B, 0xCD, true, true, false),
	MD(0x2C, 0x96, true, false, false),
	MD(0x2D, 0x00, true, false, false),
	MD(0x2E, 0x13, true, true, false),
	MD(0x2F, 0x7B, true, true, false),

	// 0x30
	MD(0x30, 0xFE, true, true, false),
	MD(0x31, 0x34, true, false, false),
	MD(0x32, 0x20, true, true, false),
	MD(0x33, 0xF3, true, true, false),
	MD(0x34, 0x11, true, true, false),
	MD(0x35, 0xD8, true, false, false),
	MD(0x36, 0x00, true, false, false),
	MD(0x37, 0x06, true, true, true),
	MD(0x38, 0x08, true, false, false),
	MD(0x39, 0x1A, true, true, false),
	MD(0x3A, 0x13, true, true, false),
	MD(0x3B, 0x22, true, true, false),
	MD(0x3C, 0x23, true, true, false),
	MD(0x3D, 0x05, true, true, false),
	MD(0x3E, 0x20, true, true, false),
	MD(0x3F, 0xF9, true, false, false),

	// 0x40
	MD(0x40, 0x3E, true, true, false),
	MD(0x41, 0x19, true, false, false),
	MD(0x42, 0xEA, true, true, false),
	MD(0x43, 0x10, true, false, false),
	MD(0x44, 0x99, true, false, false),
	MD(0x45, 0x21, true, true, false),
	MD(0x46, 0x2F, true, false, false),
	MD(0x47, 0x99, true, false, false),
	MD(0x48, 0x0E, true, true, true),
	MD(0x49, 0x0C, true, false, false),
	MD(0x4A, 0x3D, true, true, true),
	MD(0x4B, 0x28, true, true, false),
	MD(0x4C, 0x08, true, false, false),
	MD(0x4D, 0x32, true, true, false),
	MD(0x4E, 0x0D, true, true, false),
	MD(0x4F, 0x20, true, true, false),

	// 0x50
	MD(0x50, 0xF9, true, false, false),
	MD(0x51, 0x2E, true, true, false),
	MD(0x52, 0x0F, true, false, false),
	MD(0x53, 0x18, true, true, false),
	MD(0x54, 0xF3, true, false, false),
	MD(0x55, 0x67, true, true, true),
	MD(0x56, 0x3E, true, true, false),
	MD(0x57, 0x64, true, false, false),
	MD(0x58, 0x57, true, true, false),
	MD(0x59, 0xE0, true, true, false),
	MD(0x5A, 0x42, true, false, false),
	MD(0x5B, 0x3E, true, true, false),
	MD(0x5C, 0x91, true, false, false),
	MD(0x5D, 0xE0, true, true, false),
	MD(0x5E, 0x40, true, false, false),
	MD(0x5F, 0x04, true, true, true),

	// 0x60
	MD(0x60, 0x1E, true, true, true),
	MD(0x61, 0x02, true, false, false),
	MD(0x62, 0x0E, true, true, false),
	MD(0x63, 0x0C, true, false, false),
	MD(0x64, 0xF0, true, true, true),
	MD(0x65, 0x44, true, false, false),
	MD(0x66, 0xFE, true, true, false),
	MD(0x67, 0x90, true, false, false),
	MD(0x68, 0x20, true, true, false),
	MD(0x69, 0xFA, true, false, false),
	MD(0x6A, 0x0D, true, true, false),
	MD(0x6B, 0x20, true, true, false),
	MD(0x6C, 0xF7, true, false, false),
	MD(0x6D, 0x1D, true, true, false),
	MD(0x6E, 0x20, true, true, false),
	MD(0x6F, 0xF2, true, false, false),

	// 0x70
	MD(0x70, 0x0E, true, true, false),
	MD(0x71, 0x13, true, false, false),
	MD(0x72, 0x24, true, true, false),
	MD(0x73, 0x7C, true, true, false),
	MD(0x74, 0x1E, true, true, false),
	MD(0x75, 0x83, true, false, false),
	MD(0x76, 0xFE, true, true, false),
	MD(0x77, 0x62, true, false, false),
	MD(0x78, 0x28, true, true, false),
	MD(0x79, 0x06, true, false, false),
	MD(0x7A, 0x1E, true, true, false),
	MD(0x7B, 0xC1, true, false, false),
	MD(0x7C, 0xFE, true, true, false),
	MD(0x7D, 0x64, true, false, false),
	MD(0x7E, 0x20, true, true, false),
	MD(0x7F, 0x06, true, false, false),

	// 0x80
	MD(0x80, 0x7B, true, true, true),
	MD(0x81, 0xE2, true, true, false),
	MD(0x82, 0x0C, true, true, false),
	MD(0x83, 0x3E, true, true, false),
	MD(0x84, 0x87, true, false, false),
	MD(0x85, 0xF2, true, true, false),
	MD(0x86, 0xF0, true, true, true),
	MD(0x87, 0x42, true, false, false),
	MD(0x88, 0x90, true, true, false),
	MD(0x89, 0xE0, true, true, false),
	MD(0x8A, 0x42, true, false, false),
	MD(0x8B, 0x15, true, true, false),
	MD(0x8C, 0x20, true, true, false),
	MD(0x8D, 0xD2, true, false, false),
	MD(0x8E, 0x05, true, true, false),
	MD(0x8F, 0x20, true, true, false),

	// 0x90
	MD(0x90, 0x4F, true, false, false),
	MD(0x91, 0x16, true, true, false),
	MD(0x92, 0x20, true, false, false),
	MD(0x93, 0x18, true, true, false),
	MD(0x94, 0xCB, true, false, false),
	MD(0x95, 0x4F, true, true, true),
	MD(0x96, 0x06, true, true, true),
	MD(0x97, 0x04, true, false, false),
	MD(0x98, 0xC5, true, true, true),
	MD(0x99, 0xCB, true, true, false),
	MD(0x9A, 0x11, true, false, false),
	MD(0x9B, 0x17, true, true, false),
	MD(0x9C, 0xC1, true, true, false),
	MD(0x9D, 0xCB, true, true, false),
	MD(0x9E, 0x11, true, false, false),
	MD(0x9F, 0x17, true, true, false),

	// 0xA0
	MD(0xA0, 0x05, true, true, false),
	MD(0xA1, 0x20, true, true, false),
	MD(0xA2, 0xF5, true, false, false),
	MD(0xA3, 0x22, true, true, false),
	MD(0xA4, 0x23, true, true, false),
	MD(0xA5, 0x22, true, true, false),
	MD(0xA6, 0x23, true, true, false),
	MD(0xA7, 0xC9, true, true, false),
	MD(0xA8, 0xCE, false, false, false),
	MD(0xA9, 0xED, false, false, false),
	MD(0xAA, 0x66, false, false, false),
	MD(0xAB, 0x66, false, false, false),
	MD(0xAC, 0xCC, false, false, false),
	MD(0xAD, 0x0D, false, false, false),
	MD(0xAE, 0x00, false, false, false),
	MD(0xAF, 0x0B, false, false, false),

	// 0xB0
	MD(0xB0, 0x03, false, false, false),
	MD(0xB1, 0x73, false, false, false),
	MD(0xB2, 0x00, false, false, false),
	MD(0xB3, 0x83, false, false, false),
	MD(0xB4, 0x00, false, false, false),
	MD(0xB5, 0x0C, false, false, false),
	MD(0xB6, 0x00, false, false, false),
	MD(0xB7, 0x0D, false, false, false),
	MD(0xB8, 0x00, false, false, false),
	MD(0xB9, 0x08, false, false, false),
	MD(0xBA, 0x11, false, false, false),
	MD(0xBB, 0x1F, false, false, false),
	MD(0xBC, 0x88, false, false, false),
	MD(0xBD, 0x89, false, false, false),
	MD(0xBE, 0x00, false, false, false),
	MD(0xBF, 0x0E, false, false, false),

	// 0xC0
	MD(0xC0, 0xDC, false, false, false),
	MD(0xC1, 0xCC, false, false, false),
	MD(0xC2, 0x6E, false, false, false),
	MD(0xC3, 0xE6, false, false, false),
	MD(0xC4, 0xDD, false, false, false),
	MD(0xC5, 0xDD, false, false, false),
	MD(0xC6, 0xD9, false, false, false),
	MD(0xC7, 0x99, false, false, false),
	MD(0xC8, 0xBB, false, false, false),
	MD(0xC9, 0xBB, false, false, false),
	MD(0xCA, 0x67, false, false, false),
	MD(0xCB, 0x63, false, false, false),
	MD(0xCC, 0x6E, false, false, false),
	MD(0xCD, 0x0E, false, false, false),
	MD(0xCE, 0xEC, false, false, false),
	MD(0xCF, 0xCC, false, false, false),

	// 0xD0
	MD(0xD0, 0xDD, false, false, false),
	MD(0xD1, 0xDC, false, false, false),
	MD(0xD2, 0x99, false, false, false),
	MD(0xD3, 0x9F, false, false, false),
	MD(0xD4, 0xBB, false, false, false),
	MD(0xD5, 0xB9, false, false, false),
	MD(0xD6, 0x33, false, false, false),
	MD(0xD7, 0x3E, false, false, false),
	MD(0xD8, 0x3c, false, false, false),
	MD(0xD9, 0x42, false, false, false),
	MD(0xDA, 0xB9, false, false, false),
	MD(0xDB, 0xA5, false, false, false),
	MD(0xDC, 0xB9, false, false, false),
	MD(0xDD, 0xA5, false, false, false),
	MD(0xDE, 0x42, false, false, false),
	MD(0xDF, 0x4C, false, false, false),

	// 0xE0
	MD(0xE0, 0x21, true, true, true),
	MD(0xE1, 0x04, true, false, false),
	MD(0xE2, 0x01, true, false, false),
	MD(0xE3, 0x11, true, true, false),
	MD(0xE4, 0xA8, true, false, false),
	MD(0xE5, 0x00, true, false, false),
	MD(0xE6, 0x1A, true, true, true),
	MD(0xE7, 0x13, true, true, false),
	MD(0xE8, 0xBE, true, true, false),
	MD(0xE9, 0x20, true, true, true),
	MD(0xEA, 0xFE, true, false, false),
	MD(0xEB, 0x23, true, true, false),
	MD(0xEC, 0x7D, true, true, false),
	MD(0xED, 0xFE, true, true, false),
	MD(0xEE, 0x34, true, false, false),
	MD(0xEF, 0x20, true, true, false),

	// 0xF0
	MD(0xF0, 0xF5, true, false, false),
	MD(0xF1, 0x06, true, true, false),
	MD(0xF2, 0x19, true, false, false),
	MD(0xF3, 0x78, true, true, false),
	MD(0xF4, 0x86, true, true, true),
	MD(0xF5, 0x23, true, true, false),
	MD(0xF6, 0x05, true, true, false),
	MD(0xF7, 0x20, true, true, false),
	MD(0xF8, 0xFB, true, false, false),
	MD(0xF9, 0x86, true, true, false),
	MD(0xFA, 0x20, true, true, true),
	MD(0xFB, 0xFE, true, false, false),
	MD(0xFC, 0x3E, true, true, false),
	MD(0xFD, 0x01, true, false, false),
	MD(0xFE, 0xE0, true, true, false),
	MD(0xFF, 0x50, true, false, false)
};
#undef MD
#endif
