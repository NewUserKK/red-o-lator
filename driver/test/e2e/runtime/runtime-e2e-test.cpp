#include <string>
#include <iostream>
#include <vector>

#include <CL/opencl.h>
#include <common/test/doctest.h>
#include <common/utils/common.hpp>

TEST_CASE("a_plus_b") {
    cl_int error;

    cl_uint platformCount;
    error = clGetPlatformIDs(0, nullptr, &platformCount);
    CHECK(error == CL_SUCCESS);

    auto* platformList =
        (cl_platform_id*) malloc(platformCount * sizeof(cl_platform_id));

    error = clGetPlatformIDs(platformCount, platformList, nullptr);
    CHECK(error == CL_SUCCESS);

    const auto platform = platformList[0];

    for (int i = 0; i < platformCount; i++) {
        const auto currentPlatform = platformList[i];
        char platformName[128];
        error = clGetPlatformInfo(currentPlatform, CL_PLATFORM_NAME, 128,
                                  &platformName, nullptr);
        CHECK(error == CL_SUCCESS);
    }

    cl_uint num_devices;
    cl_device_id device;
    error =
        clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, &num_devices);
    CHECK(error == CL_SUCCESS);

    char deviceName[128];
    error = clGetDeviceInfo(device, CL_DEVICE_NAME, 128, deviceName, nullptr);
    CHECK(error == CL_SUCCESS);

    char deviceVersion[50];
    error =
        clGetDeviceInfo(device, CL_DEVICE_VERSION, 50, deviceVersion, nullptr);
    CHECK(error == CL_SUCCESS);

    cl_context context =
        clCreateContext(nullptr, 1, &device, nullptr, nullptr, &error);
    CHECK(error == CL_SUCCESS);

    cl_command_queue queue =
        clCreateCommandQueue(context, device, 0, &error);
    CHECK(error == CL_SUCCESS);

    const std::string binaryPath = "test/resources/kernels/a_plus_b.bin";
    const auto binary = utils::readBinaryFile(binaryPath);

    CHECK_FALSE(binary.empty());

    const size_t binarySize[1] = {binary.size()};
    const unsigned char* binaryData[1] = {binary.data()};

    cl_program program = clCreateProgramWithBinary(
        context, 1, &device, binarySize, binaryData, nullptr, &error);
    CHECK(error == CL_SUCCESS);

    error = clBuildProgram(program, 1, &device, nullptr, nullptr, nullptr);
    CHECK(error == CL_SUCCESS);

    const std::string kernelName = "a_plus_b";
    cl_kernel kernel = clCreateKernel(program, kernelName.c_str(), &error);
    CHECK(error == CL_SUCCESS);

    const size_t arraySize = 3;
    const size_t arraySizeBytes = arraySize * sizeof(cl_uint);

    std::vector<cl_uint> data1{};
    data1.assign(arraySize, 1);
    cl_mem mem1 =
        clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                       arraySizeBytes, data1.data(), &error);
    CHECK(error == CL_SUCCESS);

    std::vector<cl_uint> data2{};
    data2.assign(arraySize, 2);
    cl_mem mem2 =
        clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                       arraySizeBytes, data2.data(), &error);
    CHECK(error == CL_SUCCESS);

    cl_mem mem3 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, arraySizeBytes,
                                 nullptr, &error);
    CHECK(error == CL_SUCCESS);

    error = clSetKernelArg(kernel, 0, sizeof(cl_mem), &mem1);
    CHECK(error == CL_SUCCESS);

    error = clSetKernelArg(kernel, 1, sizeof(cl_mem), &mem2);
    CHECK(error == CL_SUCCESS);

    error = clSetKernelArg(kernel, 2, sizeof(cl_mem), &mem3);
    CHECK(error == CL_SUCCESS);

    size_t globalWorkSize[1];
    globalWorkSize[0] = arraySizeBytes;

    size_t localWorkSize[1];
    localWorkSize[0] = 0;

    error =
        clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, globalWorkSize,
                               localWorkSize, 0, nullptr, nullptr);
    CHECK(error == CL_SUCCESS);

    error = clFlush(queue);
    CHECK(error == CL_SUCCESS);

    std::vector<cl_uint> bufferData(arraySize);
    error = clEnqueueReadBuffer(queue, mem3, true, 0, arraySizeBytes,
                                bufferData.data(), 0, nullptr, nullptr);
    CHECK(error == CL_SUCCESS);
    CHECK(utils::joinToString<cl_uint>(bufferData, " ", [](auto value) {
              return std::to_string(value);
          }) == "0 0 0");

    error = clReleaseKernel(kernel);
    CHECK(error == CL_SUCCESS);

    error = clReleaseMemObject(mem3);
    CHECK(error == CL_SUCCESS);

    error = clReleaseMemObject(mem2);
    CHECK(error == CL_SUCCESS);

    error = clReleaseMemObject(mem1);
    CHECK(error == CL_SUCCESS);

    error = clReleaseProgram(program);
    CHECK(error == CL_SUCCESS);

    error = clReleaseCommandQueue(queue);
    CHECK(error == CL_SUCCESS);

    error = clReleaseContext(context);
    CHECK(error == CL_SUCCESS);
}
