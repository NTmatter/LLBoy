# LLBoy

- GameBoy emulator utilizing LLVM for emitting translated bytecode
- Sources at https://github.com/NTmatter/LLBoy
- More detailed documentation at http://www.axante.net/projects/llboy
- Based directly upon http://imrannazar.com/GameBoy-Emulation-in-JavaScript

## Dependencies:

- LLVM Core 2.8 (compiled-in to generate native translation)
- Clang 2.8 (binary only, builds LTO opcode bitcode file)
- CMake 2.8 (binary only, for building)
- QT 4.7.0 (will be required later)
 
## Compilation Instructions

<code><pre>
mkdir bin
cd bin
CC=clang CXX=clang++ cmake -DCMAKE_BUILD_TYPE=Debug -DLLVM_ROOT:string=/path/to/llvm/install ../src
make all test
</pre></code>

## Anti-Piracy Statement:

- Games, ROMs, or information pointing thereto will not be distributed by the project
- Software will be designed in a manner that requires an original version of the game cartridge
- The End-user is responsible for the fair-use format shifting required to use the emulator
- Hardware emulation is based upon publicly available information

## MIT Licence

LLBoy

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