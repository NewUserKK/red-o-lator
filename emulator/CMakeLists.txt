find_package(OpenCL REQUIRED)

add_executable(emulator
    util/util.cpp
    flow/wavefront.cpp
    alu/alu_sop1.cpp
    instr/operand.cpp
    reg/register.cpp
    instr/instruction.cpp
        main/KernelLoader.cpp
        main/KernelLoader.h
        main/main.cpp)

add_executable(emulator_test
        test/util/util_test.cpp
        util/util.cpp
)

target_link_libraries(emulator OpenCL::OpenCL)
#target_link_libraries(emulator driver)
