# LLBoy

- GameBoy emulator utilizing LLVM for translating GameBoy bytecode to native
- Sources at https://github.com/NTmatter/LLBoy
- More detailed documentation at http://www.axante.net/projects/llboy
- Based directly upon http://imrannazar.com/GameBoy-Emulation-in-JavaScript

## Dependencies:

- LLVM Core 3.2 (compiled-in to generate native translation)
- Clang 3.2 (binary only, builds LTO opcode bitcode file)
- CMake 2.8 (binary only, for building)
- QT 4.7.0 (will be required later)
 
## Compilation Instructions
LLVM and Clang 3.2 headers and binaries should be installed on the system. In
some cases, the development headers will be missing, or the cmake configuration
files may not be present. It is generally easiest to download the latest from llvm.org.

To install LLVM and Clang to the location of your choosing:
<pre>
  # Extract llvm and clang sources
  tar xzf llvm-3.2.src.tar.gz
  tar xzf clang-3.2.src.tar.gz

  # Move clang sources into llvm for automatic build
  mv clang-3.2.src llvm-3.2.src/tools/clang

  # Do an out-of-tree build
  mkdir llvm-3.2.build
  cd llvm-3.2.build
  cmake -DCMAKE_INSTALL_PREFIX:PATH=/example/clang+llvm-3.2 ../llvm-3.2.src
  make
  sudo make install
</pre>

Build LLboy:
<pre>
  cd LLboy
  mkdir bin
  cd bin
  CC=clang CXX=clang++ cmake -DCMAKE_BUILD_TYPE=Debug -DLLVM_ROOT:path=/example/clang+llvm-3.2 ../src
  make all test
</pre>

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