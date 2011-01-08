project("LLBoy System Emulation")
# TODO Compile with Clang to LLVM object file 
# clang -c -emit-llvm cpu.c -o $BUILT_PRODUCTS_DIR/cpu.o
add_library (llboy_system cpu.c system.c)

add_executable(llboyTest cpu_test.c)
target_link_libraries(llboyTest llboy_system)