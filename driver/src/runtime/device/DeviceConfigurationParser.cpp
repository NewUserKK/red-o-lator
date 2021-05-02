#include <cstring>
#include <fstream>
#include <iostream>
#include <numeric>
#include <unordered_set>

#include "runtime/runtime-commons.h"
#include "DeviceConfigurationParser.h"
#include "common/common.hpp"

template <typename T>
T parseNumber(const std::string& value);

cl_bool parseClBool(const std::string& value);
cl_bitfield parseBitfield(const std::string& value,
                          cl_bitfield parseFunction(const std::string& value));

template <typename T>
std::vector<T> parseArray(const std::string& value,
                          T parseFunction(const std::string& value));

cl_device_local_mem_type parseDeviceLocalMemType(const std::string& value);
cl_device_exec_capabilities parseDeviceExecCapabilities(
    const std::string& value);
cl_command_queue_properties parseCommandQueueProperties(
    const std::string& value);
cl_device_type parseDeviceType(const std::string& value);
cl_device_mem_cache_type parseDeviceMemCacheType(const std::string& value);
cl_device_partition_property parseDevicePartitionProperty(
    const std::string& value);
cl_device_affinity_domain parseDeviceAffinityDomain(const std::string& value);
cl_device_fp_config parseDeviceFpConfig(const std::string& value);

void DeviceConfigurationParser::load(const std::string& configurationFilePath) {
    std::ifstream configurationFile(configurationFilePath);

    if (!configurationFile.is_open()) {
        throw DeviceConfigurationParseException("Failed to open " +
                                                configurationFilePath);
    }

    std::unordered_map<cl_device_info, DeviceConfigurationParameterValue>
        parameters;
    std::string line;

    while (getline(configurationFile, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        const auto [parameterName, parameterValue] = splitTwo(line, '=');
        const auto parsedParameter =
            parseParameter(trim(parameterName), trim(parameterValue));

        parameters.emplace(parsedParameter.name, parsedParameter.value);
    }

    parameters.emplace(
        CL_DEVICE_PLATFORM,
        DeviceConfigurationParameterValue(kPlatform, sizeof(cl_platform_id)));

    parameters.emplace(
        CL_DEVICE_PARENT_DEVICE,
        DeviceConfigurationParameterValue(nullptr, sizeof(cl_device_id)));

    mConfigurationPath = configurationFilePath;
    mParameters = parameters;
}

std::optional<DeviceConfigurationParameterValue>
DeviceConfigurationParser::getParameter(cl_device_info parameter) const {
    if (mParameters.find(parameter) != mParameters.end()) {
        return mParameters.at(parameter);
    }

    const auto isValidOpenCLParameter =
        parameter >= CL_DEVICE_TYPE &&
        parameter <= CL_DEVICE_PRINTF_BUFFER_SIZE;
    if (isValidOpenCLParameter) {
        std::cout << "Parameter " << parameter << " was not found in config"
                  << std::endl;
        return DeviceConfigurationParameterValue(nullptr, 0);
    }

    return std::nullopt;
}

#define PARSE_PARAMETER_WITH_BODY(param, fn) \
    if (parameterName == #param) {           \
        clParameter = param;                 \
        fn();                                \
    }

#define PARSE_PARAMETER(param, type, parseFn)                      \
    if (parameterName == #param) {                                 \
        clParameter = param;                                       \
        resultSize = sizeof(type);                                 \
        result = reinterpret_cast<void*>(parseFn(parameterValue)); \
    }

#define PARSE_BITFIELD_PARAMETER(param, type, parseFn)                       \
    if (parameterName == #param) {                                           \
        clParameter = param;                                                 \
        resultSize = sizeof(type);                                           \
        result =                                                             \
            reinterpret_cast<void*>(parseBitfield(parameterValue, parseFn)); \
    }

#define PARSE_NUMBER_PARAMETER(param, type)                                  \
    if (parameterName == #param) {                                           \
        clParameter = param;                                                 \
        resultSize = sizeof(type);                                           \
        result = reinterpret_cast<void*>(parseNumber<type>(parameterValue)); \
    }

#define PARSE_BOOL_PARAMETER(param)                                    \
    if (parameterName == #param) {                                     \
        clParameter = param;                                           \
        resultSize = sizeof(cl_bool);                                  \
        result = reinterpret_cast<void*>(parseClBool(parameterValue)); \
    }

#define PARSE_STRING_PARAMETER(param) \
    if (parameterName == #param) {    \
        clParameter = param;          \
        result = parameterValue;      \
    }

#define IGNORE_PARAMETER(param)    \
    if (parameterName == #param) { \
        clParameter = param;       \
        result = nullptr;        \
    }

DeviceConfigurationParser::ParsedParameter
DeviceConfigurationParser::parseParameter(const std::string& parameterName,
                                          const std::string& parameterValue) {
    size_t resultSize = 0;
    DeviceConfigurationParameterValueType result;
    cl_device_info clParameter = 0;

    IGNORE_PARAMETER(CL_DEVICE_PLATFORM)
    IGNORE_PARAMETER(CL_DEVICE_PARENT_DEVICE)

    PARSE_PARAMETER(CL_DEVICE_TYPE, cl_device_type, parseDeviceType)
    PARSE_STRING_PARAMETER(CL_DEVICE_NAME)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_VENDOR_ID,
                           cl_uint)  // TODO: parse hex correctly
    PARSE_STRING_PARAMETER(CL_DEVICE_VENDOR)
    PARSE_STRING_PARAMETER(CL_DRIVER_VERSION)
    PARSE_STRING_PARAMETER(CL_DEVICE_PROFILE)
    PARSE_STRING_PARAMETER(CL_DEVICE_VERSION)
    PARSE_STRING_PARAMETER(CL_DEVICE_OPENCL_C_VERSION)
    PARSE_STRING_PARAMETER(CL_DEVICE_EXTENSIONS)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_MAX_COMPUTE_UNITS, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, cl_uint)
    PARSE_PARAMETER_WITH_BODY(CL_DEVICE_MAX_WORK_ITEM_SIZES, [&]() {
        // TODO: get actual CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS value
        // TODO: CL_DEVICE_MAX_WORK_ITEM_SIZES not working
        const int maxWorkItemDimensions = 3;
        resultSize = maxWorkItemDimensions * sizeof(size_t);
        result = &parseArray(parameterValue, parseNumber<size_t>)[0];
    })
    PARSE_NUMBER_PARAMETER(CL_DEVICE_MAX_WORK_GROUP_SIZE, size_t)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_NATIVE_VECTOR_WIDTH_INT, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_MAX_CLOCK_FREQUENCY, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_ADDRESS_BITS, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_MAX_MEM_ALLOC_SIZE, cl_ulong)
    PARSE_BOOL_PARAMETER(CL_DEVICE_IMAGE_SUPPORT)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_MAX_READ_IMAGE_ARGS, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_MAX_WRITE_IMAGE_ARGS, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_IMAGE2D_MAX_WIDTH, size_t)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_IMAGE2D_MAX_HEIGHT, size_t)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_IMAGE3D_MAX_WIDTH, size_t)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_IMAGE3D_MAX_HEIGHT, size_t)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_IMAGE3D_MAX_DEPTH, size_t)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_IMAGE_MAX_BUFFER_SIZE, size_t)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_IMAGE_MAX_ARRAY_SIZE, size_t)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_MAX_SAMPLERS, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_MAX_PARAMETER_SIZE, size_t)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_MEM_BASE_ADDR_ALIGN, cl_uint)
    PARSE_BITFIELD_PARAMETER(CL_DEVICE_SINGLE_FP_CONFIG, cl_device_fp_config,
                             parseDeviceFpConfig)
    PARSE_BITFIELD_PARAMETER(CL_DEVICE_DOUBLE_FP_CONFIG, cl_device_fp_config,
                             parseDeviceFpConfig)
    PARSE_PARAMETER(CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, cl_device_mem_cache_type,
                    parseDeviceMemCacheType)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, cl_ulong)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_GLOBAL_MEM_SIZE, cl_ulong)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, cl_ulong)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_MAX_CONSTANT_ARGS, cl_uint)
    PARSE_PARAMETER(CL_DEVICE_LOCAL_MEM_TYPE, cl_device_local_mem_type,
                    parseDeviceLocalMemType)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_LOCAL_MEM_SIZE, cl_ulong)
    PARSE_BOOL_PARAMETER(CL_DEVICE_ERROR_CORRECTION_SUPPORT)
    PARSE_BOOL_PARAMETER(CL_DEVICE_HOST_UNIFIED_MEMORY)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_PROFILING_TIMER_RESOLUTION, size_t)
    PARSE_PARAMETER(CL_DEVICE_ENDIAN_LITTLE, cl_bool, parseClBool)
    PARSE_BOOL_PARAMETER(CL_DEVICE_AVAILABLE)
    PARSE_BOOL_PARAMETER(CL_DEVICE_COMPILER_AVAILABLE)
    PARSE_BOOL_PARAMETER(CL_DEVICE_LINKER_AVAILABLE)
    PARSE_BITFIELD_PARAMETER(CL_DEVICE_EXECUTION_CAPABILITIES,
                             cl_device_exec_capabilities,
                             parseDeviceExecCapabilities)
    PARSE_BITFIELD_PARAMETER(CL_DEVICE_QUEUE_PROPERTIES,
                             cl_command_queue_properties,
                             parseCommandQueueProperties)
    PARSE_PARAMETER_WITH_BODY(CL_DEVICE_BUILT_IN_KERNELS, [&]() {
        result = parameterValue == "0" ? "" : parameterValue.c_str();
    })
    PARSE_NUMBER_PARAMETER(CL_DEVICE_PRINTF_BUFFER_SIZE, size_t)
    PARSE_BOOL_PARAMETER(CL_DEVICE_PREFERRED_INTEROP_USER_SYNC)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_PARTITION_MAX_SUB_DEVICES, cl_uint)
    PARSE_PARAMETER(CL_DEVICE_PARTITION_PROPERTIES,
                    cl_device_partition_property, parseDevicePartitionProperty)
    PARSE_BITFIELD_PARAMETER(CL_DEVICE_PARTITION_AFFINITY_DOMAIN,
                             cl_device_affinity_domain,
                             parseDeviceAffinityDomain)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_PARTITION_TYPE, cl_uint)
    PARSE_NUMBER_PARAMETER(CL_DEVICE_REFERENCE_COUNT, cl_uint)

    if (!clParameter) {
        throw DeviceConfigurationParseException("Invalid parameterName: " +
                                                parameterName);
    }

    if (std::holds_alternative<std::string>(result)) {
        resultSize = strlen(std::get<std::string>(result).c_str()) + 1;
    }

    return ParsedParameter(
        clParameter, DeviceConfigurationParameterValue(result, resultSize));
}

// TODO: ignore PARENT_DEVICE_ID, cl_platform_id

template <typename T>
T parseNumber(const std::string& value) {
    try {
        return static_cast<T>(std::stoul(value));
    } catch (std::invalid_argument& e) {
        throw DeviceConfigurationParseException("Failed to parse number: " +
                                                value);
    }
}

cl_bitfield parseBitfield(const std::string& value,
                          cl_bitfield parseFunction(const std::string& value)) {
    // TODO: parse 0xNN?
    const auto splitBitfield = split(value, '|');

    const auto accumulator = [&](cl_bitfield acc, const auto& value) {
        return acc | parseFunction(trim(value));
    };

    return std::accumulate(splitBitfield.begin(), splitBitfield.end(), 0,
                           accumulator);
}

template <typename T>
std::vector<T> parseArray(const std::string& value,
                          T parseFunction(const std::string&)) {
    const auto splitValue = split(value, ',');

    std::vector<T> result;
    std::transform(splitValue.begin(), splitValue.end(),
                   std::back_inserter(result), [&](auto& value) {
                       return parseFunction(trim(value));
                   });

    return result;
}

cl_bool parseClBool(const std::string& value) {
    if (value == "true") {
        return CL_TRUE;
    } else if (value == "false") {
        return CL_FALSE;
    }

    throw DeviceConfigurationParseException("Failed to parse cl_bool: " +
                                            value);
}

cl_device_type parseDeviceType(const std::string& value) {
    if (value == "CL_DEVICE_TYPE_CPU") {
        return CL_DEVICE_TYPE_CPU;

    } else if (value == "CL_DEVICE_TYPE_GPU") {
        return CL_DEVICE_TYPE_GPU;

    } else if (value == "CL_DEVICE_TYPE_ACCELERATOR") {
        return CL_DEVICE_TYPE_ACCELERATOR;

    } else if (value == "CL_DEVICE_TYPE_DEFAULT") {
        return CL_DEVICE_TYPE_DEFAULT;

    } else if (value == "CL_DEVICE_TYPE_CUSTOM") {
        return CL_DEVICE_TYPE_CUSTOM;
    }

    throw DeviceConfigurationParseException("Unknown cl_device_type value: " +
                                            value);
}

cl_device_local_mem_type parseDeviceLocalMemType(const std::string& value) {
    if (value == "CL_LOCAL") {
        return CL_LOCAL;

    } else if (value == "CL_GLOBAL") {
        return CL_GLOBAL;

    } else if (value == "CL_NONE") {
        return CL_NONE;
    }

    throw DeviceConfigurationParseException(
        "Unknown cl_device_local_mem_type value: " + value);
}

cl_device_exec_capabilities parseDeviceExecCapabilities(
    const std::string& value) {
    if (value == "CL_EXEC_KERNEL") {
        return CL_EXEC_KERNEL;

    } else if (value == "CL_EXEC_NATIVE_KERNEL") {
        return CL_EXEC_NATIVE_KERNEL;
    }

    throw DeviceConfigurationParseException(
        "Unknown cl_device_exec_capabilities value: " + value);
}

cl_command_queue_properties parseCommandQueueProperties(
    const std::string& value) {
    if (value == "CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE") {
        return CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE;

    } else if (value == "CL_QUEUE_PROFILING_ENABLE") {
        return CL_QUEUE_PROFILING_ENABLE;
    }

    throw DeviceConfigurationParseException(
        "Unknown cl_command_queue_properties value: " + value);
}

cl_device_mem_cache_type parseDeviceMemCacheType(const std::string& value) {
    if (value == "CL_READ_ONLY_CACHE") {
        return CL_READ_ONLY_CACHE;

    } else if (value == "CL_READ_WRITE_CACHE") {
        return CL_READ_WRITE_CACHE;

    } else if (value == "CL_NONE") {
        return CL_NONE;
    }

    throw DeviceConfigurationParseException(
        "Unknown cl_device_mem_cache_type value: " + value);
}

cl_device_partition_property parseDevicePartitionProperty(
    const std::string& value) {
    // TODO: parse array

    if (value == "CL_DEVICE_PARTITION_EQUALLY") {
        return CL_DEVICE_PARTITION_EQUALLY;

    } else if (value == "CL_DEVICE_PARTITION_BY_COUNTS") {
        return CL_DEVICE_PARTITION_BY_COUNTS;

    } else if (value == "CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN") {
        return CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN;

    } else if (value == "0") {
        return 0;
    }

    throw DeviceConfigurationParseException(
        "Unknown cl_device_partition_property value: " + value);
}

cl_device_affinity_domain parseDeviceAffinityDomain(const std::string& value) {
    if (value == "CL_DEVICE_AFFINITY_DOMAIN_NUMA") {
        return CL_DEVICE_AFFINITY_DOMAIN_NUMA;

    } else if (value == "CL_DEVICE_AFFINITY_DOMAIN_L4_CACHE") {
        return CL_DEVICE_AFFINITY_DOMAIN_L4_CACHE;

    } else if (value == "CL_DEVICE_AFFINITY_DOMAIN_L3_CACHE") {
        return CL_DEVICE_AFFINITY_DOMAIN_L3_CACHE;

    } else if (value == "CL_DEVICE_AFFINITY_DOMAIN_L2_CACHE") {
        return CL_DEVICE_AFFINITY_DOMAIN_L2_CACHE;

    } else if (value == "CL_DEVICE_AFFINITY_DOMAIN_L1_CACHE") {
        return CL_DEVICE_AFFINITY_DOMAIN_L1_CACHE;

    } else if (value == "CL_DEVICE_AFFINITY_DOMAIN_NEXT_PARTITIONABLE") {
        return CL_DEVICE_AFFINITY_DOMAIN_NEXT_PARTITIONABLE;

    } else if (value == "0") {
        return 0;
    }

    throw DeviceConfigurationParseException(
        "Unknown cl_device_affinity_domain value: " + value);
}

cl_device_fp_config parseDeviceFpConfig(const std::string& value) {
    if (value == "CL_FP_DENORM") {
        return CL_FP_DENORM;

    } else if (value == "CL_FP_INF_NAN") {
        return CL_FP_INF_NAN;

    } else if (value == "CL_FP_ROUND_TO_NEAREST") {
        return CL_FP_ROUND_TO_NEAREST;

    } else if (value == "CL_FP_ROUND_TO_ZERO") {
        return CL_FP_ROUND_TO_ZERO;

    } else if (value == "CL_FP_ROUND_TO_INF") {
        return CL_FP_ROUND_TO_INF;

    } else if (value == "CL_FP_FMA") {
        return CL_FP_FMA;

    } else if (value == "CL_FP_SOFT_FLO") {
        return CL_FP_SOFT_FLOAT;

    } else if (value == "0") {
        return 0;
    }

    throw DeviceConfigurationParseException(
        "Unknown cl_device_fp_config value: " + value);
}
