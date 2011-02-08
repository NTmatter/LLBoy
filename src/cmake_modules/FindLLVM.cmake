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


# Find the full LLVM package using LLVM_ROOT as a hint
# Reference Material:
# http://eris.liralab.it/wiki/CMake_and_FIND_PACKAGE
# http://www.cmake.org/cgi-bin/viewcvs.cgi/Modules/readme.txt?root=CMake&view=markup
set(LLVM_ROOT "" CACHE PATH "Root of LLVM install.")
if(NOT EXISTS ${LLVM_ROOT}/include/llvm)
    message(FATAL_ERROR "LLVM_ROOT (${LLVM_ROOT}) is not a valid LLVM install.")
endif()

find_program(LLVM_CONFIG llvm-config PATH ${LLVM_ROOT} PATH_SUFFIXES bin)
execute_process(COMMAND ${LLVM_CONFIG} --libdir
    OUTPUT_VARIABLE LLVM_LIBRARY_DIRS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --includedir
    OUTPUT_VARIABLE LLVM_INCLUDE_DIRS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --cflags
    OUTPUT_VARIABLE LLVM_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --cxxflags
    OUTPUT_VARIABLE LLVM_CXXFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    LLVM
    REQUIRED_VARS LLVM_INCLUDE_DIRS LLVM_LIBRARY_DIRS LLVM_ROOT)

if(LLVM_FOUND)
    set(LLVM_DEFINITIONS -D__STDC_LIMIT_MACROS=1 -D__STDC_CONSTANT_MACROS=1)
    set(LLVM_LIBRARIES
            LLVMpic16passes LLVMMCDisassembler LLVMXCoreCodeGen
            LLVMXCoreAsmPrinter LLVMXCoreInfo LLVMSystemZCodeGen
            LLVMSystemZAsmPrinter LLVMSystemZInfo LLVMSparcCodeGen
            LLVMSparcAsmPrinter LLVMSparcInfo LLVMPowerPCCodeGen
            LLVMPowerPCAsmPrinter LLVMPowerPCInfo LLVMPIC16AsmPrinter
            LLVMPIC16CodeGen LLVMPIC16Info LLVMMipsAsmPrinter
            LLVMMipsCodeGen LLVMMipsInfo LLVMMSP430CodeGen
            LLVMMSP430AsmPrinter LLVMMSP430Info LLVMMBlazeAsmPrinter
            LLVMMBlazeCodeGen LLVMMBlazeInfo LLVMLinker
            LLVMipo LLVMInterpreter LLVMInstrumentation
            LLVMJIT LLVMExecutionEngine LLVMCppBackend
            LLVMCppBackendInfo LLVMCellSPUCodeGen LLVMCellSPUAsmPrinter
            LLVMCellSPUInfo LLVMCBackend LLVMCBackendInfo
            LLVMBlackfinCodeGen LLVMBlackfinAsmPrinter LLVMBlackfinInfo
            LLVMBitWriter LLVMX86Disassembler LLVMX86AsmParser
            LLVMX86CodeGen LLVMX86AsmPrinter LLVMX86Info
            LLVMAsmParser LLVMARMDisassembler LLVMARMAsmParser
            LLVMARMCodeGen LLVMARMAsmPrinter LLVMARMInfo
            LLVMArchive LLVMBitReader LLVMAlphaCodeGen
            LLVMSelectionDAG LLVMAlphaAsmPrinter LLVMAsmPrinter
            LLVMMCParser LLVMCodeGen LLVMScalarOpts
            LLVMInstCombine LLVMTransformUtils LLVMipa
            LLVMAnalysis LLVMTarget LLVMMC
            LLVMCore LLVMAlphaInfo LLVMSupport
            LLVMSystem)
endif(LLVM_FOUND)
#   HINTS ${LLVM_HOME}/lib)
# list(LENGTH LLVM_LIB tmp)
# message ("Found LLVM LIB: ${tmp}" )