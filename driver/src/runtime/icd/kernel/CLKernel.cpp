#include <common/utils/common.hpp>
#include <cstddef>
#include <string>
#include <utility>

#include "CLKernel.h"
#include "runtime-commons.h"

CLKernel::CLKernel(IcdDispatchTable* const dispatchTable,
                   std::string name,
                   std::vector<std::string> config,
                   std::vector<std::string> instructions,
                   std::vector<KernelArgument> arguments)
    : dispatchTable(dispatchTable),
      name(std::move(name)),
      config(std::move(config)),
      instructions(std::move(instructions)),
      arguments(std::move(arguments)) {}

CLKernel::~CLKernel() {
    if (program) {
        clReleaseProgram(program);
    }
}

void CLKernel::setArgument(cl_uint index, size_t size, const void* value) {
    if (index >= arguments.size()) {
        throw KernelArgumentOutOfBoundsError(
            "Attempt to set argument at index " + std::to_string(index) +
            " of kernel with " + std::to_string(arguments.size()) +
            " arguments");
    }

    const auto argInfo = arguments[index].info;

    KernelArgumentValueType data;
    if (!value) {
        data = nullptr;
    } else if (std::dynamic_pointer_cast<PointerKernelArgumentInfo>(argInfo)) {
        data = *const_cast<cl_mem*>(static_cast<const cl_mem*>(value));
    } else {
        auto* temp = new std::byte[size];
        memcpy(temp, value, size);
        data = temp;
    }

    arguments[index].value = KernelArgumentValue(index, size, data);
}

KernelArgument CLKernel::getArgument(cl_uint index) const {
    if (index >= arguments.size()) {
        throw KernelArgumentOutOfBoundsError(
            "Attempt to get argument at index " + std::to_string(index) +
            " of kernel with " + std::to_string(arguments.size()) +
            " arguments");
    }

    return arguments[index];
}

const std::vector<KernelArgument>& CLKernel::getArguments() const {
    return arguments;
}

int CLKernel::argumentCount() const {
    return arguments.size();
}

CLKernel* CLKernelBuilder::build() const {
    std::vector<KernelArgument> args;
    std::transform(argumentInfo.begin(), argumentInfo.end(),
                   std::back_inserter(args), [](auto& info) {
                       return KernelArgument(info);
                   });

    return new CLKernel(kDispatchTable, name, config, instructions, args);
}
