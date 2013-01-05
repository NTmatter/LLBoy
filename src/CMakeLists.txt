# Copyright (c) 2011 Thomas Johnson
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.


cmake_minimum_required (VERSION 2.8)
project (LLBoy)

set (LLBoy_VERSION_MAJOR 0)
set (LLBoy_VERSION_MINOR 1)
set (LLBoy_VERSION_MICRO 0)

ENABLE_TESTING()

# Pull in LLVM and find clang/clang++
find_package(LLVM REQUIRED)
add_definitions(${LLVM_DEFINITIONS})
include_directories( ${LLVM_INCLUDE_DIRS} )
link_directories( ${LLVM_LIBRARY_DIRS} )

# TODO Reduce to required LLVM components.
llvm_map_components_to_libraries(REQ_LLVM_LIBRARIES
	core jit linker runtimedyld analysis native
	transformutils vectorize instcombine ipa ipo instrumentation
	engine executionengine
    bitwriter bitreader)

find_program( LLVM_CLANG clang
	DOC "Clang binary from LLVM install"
	PATHS ${LLVM_INSTALL_PREFIX}
	PATH_SUFFIXES bin )

find_program( LLVM_LINK llvm-link
	DOC "Clang binary from LLVM install"
	PATHS ${LLVM_INSTALL_PREFIX}
	PATH_SUFFIXES bin )

# Core system library
add_subdirectory (sys)

add_executable (LLBoy main.cpp)
target_link_libraries (LLBoy ${REQ_LLVM_LIBRARIES})