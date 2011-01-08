# Find the full LLVM package using LLVM_ROOT as a hint
# Reference Material:
# http://eris.liralab.it/wiki/CMake_and_FIND_PACKAGE
# http://www.cmake.org/cgi-bin/viewcvs.cgi/Modules/readme.txt?root=CMake&view=markup

if(LLVM_ROOT_DIR)
    message("Using LLVM Root: ${LLVM_ROOT_DIR}")
else(LLVM_ROOT_DIR)
    message("LLVM Root directory was unspecified")
endif(LLVM_ROOT_DIR)

set(LLVM_INCLUDE_DIRS ${LLVM_ROOT_DIR}/include)
set(LLVM_LIBRARY_DIRS ${LLVM_ROOT_DIR}/lib)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    LLVM
    REQUIRED_VARS LLVM_INCLUDE_DIRS LLVM_LIBRARY_DIRS LLVM_ROOT_DIR)

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