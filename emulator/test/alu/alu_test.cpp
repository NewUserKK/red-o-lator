//
// Created by Diana Kudaiberdieva
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../alu/alu.h"
#include "../../doctest.h"

// SOP1
TEST_CASE("run_s_abs_i32 - stores absolute signed value of the SSRC0 into SDST.") {
    auto* wavefront = new Wavefront(nullptr, 2, 0);
    Instruction instruction = Instruction("", "s_abs_i32", {"s0", "s1"});

    SUBCASE("src0 is 0x80000000") {
        wavefront->scalarRegFile[1] = 0x80000000;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 0x80000000);
        CHECK(wavefront->sccReg);
    }
    SUBCASE("src0 is 0x80000001") {
        wavefront->scalarRegFile[1] = 0x80000001;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 0x7fffffff);
        CHECK(wavefront->sccReg);
    }
    SUBCASE("src0 is 0x80000002") {
        wavefront->scalarRegFile[1] = 0x80000002;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 0x7ffffffe);
        CHECK(wavefront->sccReg);
    }
    SUBCASE("src0 is 0xffffffff") {
        wavefront->scalarRegFile[1] = 0xffffffff;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 0x00000001);
        CHECK(wavefront->sccReg);
    }
    SUBCASE("src0 is 0x7fffffff") {
        wavefront->scalarRegFile[1] = 0x7fffffff;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 0x7fffffff);
        CHECK(wavefront->sccReg);
    }
    delete wavefront;
}

TEST_CASE("run_s_bcnt0_i32_b32") {
    auto* wavefront = new Wavefront(nullptr, 5, 0);
    Instruction instruction = Instruction("", "s_bcnt0_i32_b32", {"s2", "s4"});

    SUBCASE("S_BCNT0_I32_B32(0x00000000) => 32") {
        wavefront->scalarRegFile[4] = 0x00000000;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[2] == 32);
        CHECK(wavefront->sccReg);
    }
    SUBCASE("S_BCNT0_I32_B32(0xcccccccc) => 16") {
        wavefront->scalarRegFile[4] = 0xcccccccc;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[2] == 16);
        CHECK(wavefront->sccReg);
    }
    SUBCASE("S_BCNT0_I32_B32(0xffffffff) => 0") {
        wavefront->scalarRegFile[4] = 0xffffffff;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[2] == 0);
        CHECK(!wavefront->sccReg);
    }
}

TEST_CASE("run_s_bcnt0_i32_b64") {
    auto* wavefront = new Wavefront(nullptr, 6, 0);
    Instruction instruction = Instruction("", "s_bcnt0_i32_b64", {"s2", "s[4:5]"});

    SUBCASE("S_BCNT0_I32_B64(0x00000000) => 64") {
        wavefront->scalarRegFile[4] = 0x00000000;
        wavefront->scalarRegFile[5] = 0x00000000;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[2] == 64);
        CHECK(wavefront->sccReg);
    }
    SUBCASE("S_BCNT0_I32_B64(0xcccccccc) => 48") {
        wavefront->scalarRegFile[4] = 0x00000000;
        wavefront->scalarRegFile[5] = 0xcccccccc;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[2] == 48);
        CHECK(wavefront->sccReg);
    }
}

TEST_CASE("run_s_bcnt1_i32_b32}") {
    auto* wavefront = new Wavefront(nullptr, 7, 0);
    Instruction instruction = Instruction("", "s_bcnt1_i32_b32", {"s6", "s1"});

    SUBCASE("S_BCNT1_I32_B32(0x00000000) => 0") {
        wavefront->scalarRegFile[1] = 0x00000000;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[6] == 0);
        CHECK(!wavefront->sccReg);
    }
    SUBCASE("S_BCNT1_I32_B32(0xcccccccc) => 16") {
        wavefront->scalarRegFile[1] = 0xcccccccc;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[6] == 16);
        CHECK(wavefront->sccReg);
    }
    SUBCASE("S_BCNT1_I32_B32(0xffffffff) => 32") {
        wavefront->scalarRegFile[1] = 0xffffffff;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[6] == 32);
        CHECK(wavefront->sccReg);
    }
}
TEST_CASE("run_s_bcnt1_i32_b64}") {
    auto* wavefront = new Wavefront(nullptr, 4, 0);
    Instruction instruction = Instruction("", "s_bcnt1_i32_b64", {"s2", "s[2:3]"});
    SUBCASE("S_BCNT1_I32_B64(0x00000000) => 0") {
        wavefront->scalarRegFile[2] = 0x00000000;
        wavefront->scalarRegFile[3] = 0x00000000;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[2] == 0);
        CHECK(!wavefront->sccReg);
    }
    SUBCASE("S_BCNT1_I32_B64(0xcccccccc) => 16") {
        wavefront->scalarRegFile[2] = 0x00000000;
        wavefront->scalarRegFile[3] = 0xcccccccc;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[2] == 16);
        CHECK(wavefront->sccReg);
    }
}
TEST_CASE("run_s_ff0_i32_b32") {
    auto* wavefront = new Wavefront(nullptr, 1, 0);
    Instruction instruction = Instruction("", "s_ff0_i32_b32", {"s0", "s0"});

    SUBCASE("S_FF0_I32_B32(0xaaaaaaaa) => 0") {
        wavefront->scalarRegFile[0] = 0xaaaaaaaa;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 0);
    }
    SUBCASE("SS_FF0_I32_B32(0x00000000) => 0") {
        wavefront->scalarRegFile[0] = 0x00000000;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 0);
    }
    SUBCASE("S_FF0_I32_B32(0xfffeffff) => 16") {
        wavefront->scalarRegFile[0] = 0xfffeffff;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 16);
    }
    SUBCASE("S_FF0_I32_B32(0x55555555) => 1") {
        wavefront->scalarRegFile[0] = 0x55555555;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 1);
    }
    SUBCASE("S_FF0_I32_B32(0xffffffff) => 0xffffffff") {
        wavefront->scalarRegFile[0] = 0xffffffff;
        run_sop1(instruction, wavefront);
        CHECK(int32_t(wavefront->scalarRegFile[0]) == -1);
        CHECK(wavefront->scalarRegFile[0] == 0xffffffff);
    }
}
TEST_CASE("run_s_ff0_i32_b64") {
    auto* wavefront = new Wavefront(nullptr, 101, 0);
    Instruction instruction = Instruction("", "s_ff0_i32_b64", {"s0", "s[99:100]"});

    SUBCASE("S_FF0_I32_B64(0xffffffffffffffff) => 0xffffffff") {
        wavefront->scalarRegFile[99] = 0xffffffff;
        wavefront->scalarRegFile[100] = 0xffffffff;
        run_sop1(instruction, wavefront);
        CHECK(int32_t(wavefront->scalarRegFile[0]) == -1);
        CHECK(wavefront->scalarRegFile[0] == 0xffffffff);
    }
}
TEST_CASE("run_s_ff1_i32_b32") {
    auto* wavefront = new Wavefront(nullptr, 101, 0);
    Instruction instruction = Instruction("", "s_ff1_i32_b32", {"s99", "s100"});

    SUBCASE("S_FF1_I32_B32(0xaaaaaaaa) => 1") {
        wavefront->scalarRegFile[100] = 0xaaaaaaaa;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[99] == 1);
    }
    SUBCASE("S_FF1_I32_B32(0x00000000) => 0xffffffff") {
        wavefront->scalarRegFile[100] = 0x00000000;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[99] == 0xffffffff);
    }
    SUBCASE("S_FF1_I32_B32(0xffffffff) => 0") {
        wavefront->scalarRegFile[100] = 0xffffffff;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[99] == 0);
    }
    SUBCASE("S_FF1_I32_B32(0x00010000) => 16") {
        wavefront->scalarRegFile[100] = 0x00010000;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[99] == 16);
    }
}
TEST_CASE("run_s_flbit_i32_b32") {
    auto* wavefront = new Wavefront(nullptr, 1, 0);
    Instruction instruction = Instruction("", "s_flbit_i32_b32", {"s0", "s0"});

    SUBCASE("S_FLBIT_I32_B32(0x00000000) => 0xffffffff") {
        wavefront->scalarRegFile[0] = 0x00000000;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 0xffffffff);
    }
    SUBCASE("S_FLBIT_I32_B32(0x0000cccc) => 16") {
        wavefront->scalarRegFile[0] = 0x0000cccc;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 16);
    }
    SUBCASE("S_FLBIT_I32_B32(0xffff3333) => 0") {
        wavefront->scalarRegFile[0] = 0xffff3333;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 0);
    }
    SUBCASE("S_FLBIT_I32_B32(0x7fffffff) => 1") {
        wavefront->scalarRegFile[0] = 0x7fffffff;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 1);
    }
    SUBCASE("S_FLBIT_I32_B32(0x80000000) => 0") {
        wavefront->scalarRegFile[0] = 0x80000000;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 0);
    }
    SUBCASE("S_FLBIT_I32_B32(0xffffffff) => 0") {
        wavefront->scalarRegFile[0] = 0xffffffff;
        run_sop1(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[0] == 0);
    }
}

// SOP2
TEST_CASE(
    "run_s_absdiff_i32 - omputes the absolute value of difference between two values.") {
    auto* wavefront = new Wavefront(nullptr, 12, 0);
    Instruction instruction = Instruction("", "s_absdiff_i32", {"s6", "s10", "s11"});

    SUBCASE("src0 is 0x00000002, src1 is 0x00000005") {
        wavefront->scalarRegFile[10] = 0x00000002;
        wavefront->scalarRegFile[11] = 0x00000005;
        run_sop2(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[6] == 0x00000003);
        CHECK(wavefront->sccReg);
    }
    SUBCASE("src0 is 0x80000000, src1 is 0x00000001") {
        wavefront->scalarRegFile[10] = 0x80000000;
        wavefront->scalarRegFile[11] = 0x00000001;
        run_sop2(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[6] == 0x7fffffff);
        CHECK(wavefront->sccReg);
    }
    SUBCASE("src0 is 0x80000000, src1 is 0xffffffff") {
        wavefront->scalarRegFile[10] = 0x80000000;
        wavefront->scalarRegFile[11] = 0xffffffff;
        run_sop2(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[6] == 0x7fffffff);
        CHECK(wavefront->sccReg);
    }
    SUBCASE("src0 is 0x80000000, src1 is 0xfffffffe") {
        wavefront->scalarRegFile[10] = 0x80000000;
        wavefront->scalarRegFile[11] = 0xfffffffe;
        run_sop2(instruction, wavefront);
        CHECK(wavefront->scalarRegFile[6] == 0x7ffffffe);
        CHECK(wavefront->sccReg);
    }
}