//
// Created by Diana Kudaiberdieva
//

#include "wavefront.h"

Wavefront::Wavefront() : EXEC(0), PC(0), STATUS_REG(0), MODE_REG(0) {
    std::fill(S_REG_FILE.begin(), S_REG_FILE.end(), 0);
}