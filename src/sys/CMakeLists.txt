project("LLBoy System Emulation")
# TODO Compile with Clang to LLVM object file 
# clang -c -emit-llvm cpu.c -o $BUILT_PRODUCTS_DIR/cpu.o
set(SYSTEM_SOURCES cpu.c mmu.c system.c)
set(SYSTEM_SOURCES_ABSOLUTE)

# Find absolute paths for original sources
foreach(SOURCEFILE ${SYSTEM_SOURCES})
    find_file(FOUND${SOURCEFILE}
        ${SOURCEFILE}
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}
        NO_DEFAULT_PATH)
    list(APPEND SYSTEM_SOURCES_ABSOLUTE ${FOUND${SOURCEFILE}})
    unset(FOUND${SOURCEFILE})
endforeach(SOURCEFILE)

# Create LLVM object files for sources
add_custom_target(system-bitcode ALL
    COMMAND ${LLVM_CLANG} -c -O4 -emit-llvm -I${CMAKE_CURRENT_SOURCE_DIR} ${SYSTEM_SOURCES_ABSOLUTE}
    COMMAND ${LLVM_LINK} -o ${CMAKE_CURRENT_BINARY_DIR}/llboy.bc *.o
    COMMENT "Creating LLVM Bitcode objects for runtime load and optimization"
    SOURCES ${SYSTEM_SOURCES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_library (llboy_system ${SYSTEM_SOURCES})

# Tests
# CPU Tests
add_executable(test_cpu_basic test_cpu_basic.c)
target_link_libraries(test_cpu_basic llboy_system)
add_test("CpuBasics" test_cpu_basic)

add_executable(test_cpu_arithmetic test_cpu_arithmetic.c)
target_link_libraries(test_cpu_arithmetic llboy_system)
add_test("CpuArithmetic" test_cpu_arithmetic)

add_executable(test_cpu_stack test_cpu_stack.c)
target_link_libraries(test_cpu_stack llboy_system)
add_test("CpuStack" test_cpu_stack)

add_executable(test_cpu_controlflow test_cpu_controlflow.c)
target_link_libraries(test_cpu_controlflow llboy_system)
add_test("CpuControlFlow" test_cpu_controlflow)

add_executable(test_cpu_compare test_cpu_compare.c)
target_link_libraries(test_cpu_compare llboy_system)
add_test("CpuCompare" test_cpu_compare)

add_executable(test_cpu_bit test_cpu_bit.c)
target_link_libraries(test_cpu_bit llboy_system)
add_test("CpuBitOps" test_cpu_bit)

# MMU Tests
add_executable(test_mmu_contiguous test_mmu_contiguous.c)
target_link_libraries(test_mmu_contiguous llboy_system)
add_test("MmuRegions" test_mmu_contiguous)

add_executable(test_mmu_rw test_mmu_rw.c)
target_link_libraries(test_mmu_rw llboy_system)
add_test("MmuReadWrite" test_mmu_rw)

# System Tests
add_executable(test_system_bios test_system_bios.c)
target_link_libraries(test_system_bios llboy_system)
add_test("SystemBios" test_system_bios)
