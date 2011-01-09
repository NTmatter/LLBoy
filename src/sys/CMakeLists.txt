project("LLBoy System Emulation")
# TODO Compile with Clang to LLVM object file 
# clang -c -emit-llvm cpu.c -o $BUILT_PRODUCTS_DIR/cpu.o

set(SYSTEM_SOURCES cpu.c system.c)
set(SYSTEM_SOURCES_ABSOLUTE)
foreach(SOURCEFILE ${SYSTEM_SOURCES})
    find_file(SOURCEFILE_ABSOLUTE
        ${SOURCEFILE}
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}
        NO_DEFAULT_PATH)
    list(APPEND SYSTEM_SOURCES_ABSOLUTE ${SOURCEFILE_ABSOLUTE})
endforeach(SOURCEFILE)

message (STATUS "Converting ${SYSTEM_SOURCES} --> ${SYSTEM_SOURCES_ABSOLUTE}")

# Is this doable as a module?
add_custom_target(system-bitcode ALL
    COMMAND ${CLANG} -c -O4 -emit-llvm -I${CMAKE_CURRENT_SOURCE_DIR} ${SYSTEM_SOURCES_ABSOLUTE}
    COMMENT "Creating LLVM Bitcode for loading at runtime"
    SOURCES ${SYSTEM_SOURCES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_library (llboy_system ${SYSTEM_SOURCES})
add_executable(llboyTest cpu_test.c)
target_link_libraries(llboyTest llboy_system)
