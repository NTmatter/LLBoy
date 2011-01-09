project("LLBoy System Emulation")
# TODO Compile with Clang to LLVM object file 
# clang -c -emit-llvm cpu.c -o $BUILT_PRODUCTS_DIR/cpu.o

set(SYSTEM_SOURCES cpu.c system.c)

find_program(CLANG clang HINTS ${LLVM_ROOT_DIR} PATH_SUFFIXES bin)

# CMAKE_CURRENT_SOURCE_DIR

add_custom_target(Loadables
    COMMAND ${CLANG} -c -emit-llvm ${SYSTEM_SOURCES}
    COMMENT Creating objects for future loading
    SOURCES ${SYSTEM_SOURCES})

add_library (llboy_system ${SYSTEM_SOURCES})
add_executable(llboyTest cpu_test.c)
target_link_libraries(llboyTest llboy_system)
# add_dependencies(llboyTest Loadables)
