find_package(OpenCL REQUIRED)

add_executable(emulator
        main/KernelLoader.cpp
        main/KernelLoader.h
        main/main.cpp)

target_link_libraries(emulator OpenCL::OpenCL)
