//
// Created by Diana Kudaiberdieva
//

#ifndef RED_O_LATOR_WAVEFRONT_H
#define RED_O_LATOR_WAVEFRONT_H

#include <array>
#include <cstdint>

struct Wavefront {
    uint64_t EXEC;
    uint64_t PC;
    uint64_t STATUS_REG;
    uint64_t MODE_REG;

    std::array<uint32_t, 102> S_REG_FILE;

    Wavefront();
};


#endif  // RED_O_LATOR_WAVEFRONT_H
