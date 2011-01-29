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
    COMMAND ${CLANG} -c -emit-llvm -I${CMAKE_CURRENT_SOURCE_DIR} ${SYSTEM_SOURCES_ABSOLUTE}
    COMMAND ${LLVM_LINKER} -o llboy.bc *.o
    COMMENT "Creating LLVM Bitcode objects for runtime load and optimization"
    SOURCES ${SYSTEM_SOURCES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_library (llboy ${SYSTEM_SOURCES})
add_library (llboy_system ${SYSTEM_SOURCES})
add_executable(llboyTest cpu_test.c)
target_link_libraries(llboyTest llboy_system)

add_executable(mmu_test_contiguous mmu_test_contiguous.c)
target_link_libraries(mmu_test_contiguous llboy_system)
# Tests
add_executable(cpu_test cpu_test.c)
target_link_libraries(cpu_test llboy_system)
add_test("Addition" cpu_test)

add_executable(cpu_test_controlflow cpu_test_controlflow.c)
target_link_libraries(cpu_test_controlflow llboy_system)
add_test("CpuControlFlow" cpu_test_controlflow)

add_executable(cpu_test_compare cpu_test_compare.c)
target_link_libraries(cpu_test_compare llboy_system)
add_test("CpuCompare" cpu_test_compare)

add_executable(cpu_test_bit cpu_test_bit.c)
target_link_libraries(cpu_test_bit llboy_system)
add_test("CpuBitOps" cpu_test_bit)

# MMU Tests
add_executable(mmu_test_rw mmu_test_rw.c)
target_link_libraries(mmu_test_rw llboy_system)
add_test("MmuReadWrite" mmu_test_rw)