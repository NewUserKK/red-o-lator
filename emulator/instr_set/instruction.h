/**
 * @author dkudaiberdieva
 */

#include <unordered_map>

using namespace std;

enum InstructionKey {

    // SMEM
    /**
     * Read 1 dword from scalar data cache. If the offset is specified as an
     * SGPR, the SGPR contains an UNSIGNED BYTE OFFSET (the 2 LSBs are ignored).
     * If the offset is specified as an immediate 21-bit constant, the constant
     * is a SIGNED BYTE offset.
     */
    S_LOAD_DWORD,
    /**
     * Read 2 dwords from scalar data cache. See S_LOAD_DWORD for details on the
     * offset input
     */
    S_LOAD_DWORDX2,

    // SOPC
    /**
     * Syntax: S_BITCMP0_B32 SSRC0, SSRC1
     * Operation:
     * SCC = (SSRC0 & (1U << (SSRC1&31))) == 0
     */
    S_BITCMP0_B32,
    /**
     * Syntax: S_BITCMP0_B64 SSRC0(2), SSRC1
     *Operation:
     * SCC = (SSRC0 & (1ULL << (SSRC1&63))) == 0
     */
    S_BITCMP0_B64,
    /**
     * Syntax: S_BITCMP1_B32 SSRC0, SSRC1
     *Operation:
     * SCC = (SSRC0 & (1U << (SSRC1&31))) != 0
     */
    S_BITCMP1_B32,
    /**
     * Syntax: S_BITCMP1_B64 SSRC0(2), SSRC1
     * Operation:
     * SCC = (SSRC0 & (1ULL << (SSRC1&63))) != 0
     */
    S_BITCMP1_B64,
    /**
     * Syntax: S_CMP_EQ_I32 SSRC0, SSRC1
     * Operation:
     * SCC = SSRC0==SSRC1
     */
    S_CMP_EQ_I32,

    /**
     * Syntax: S_CMP_EQ_U32 SSRC0, SSRC1
     * Operation:
     * SCC = SSRC0==SSRC1
     */
    S_CMP_EQ_U32,
    /**
     * Syntax: S_CMP_EQ_U64 SSRC0(2), SSRC1(2)
     * Operation:
     * SCC = SSRC0==SSRC1
     */
    S_CMP_EQ_U64,
    /**
     * Syntax: S_CMP_GE_I32 SSRC0, SSRC1
     * Operation:
     * SCC = (INT32)SSRC0 >= (INT32)SSRC1
     */
    S_CMP_GE_I32,
    /**
     * Syntax: S_CMP_GE_U32 SSRC0, SSRC1
     * Operation:
     * SCC = SSRC0 >= SSRC1
     */
    S_CMP_GE_U32,
    /**
     * Syntax: S_CMP_GT_I32 SSRC0, SSRC1
     * Operation:
     * SCC = (INT32)SSRC0 > (INT32)SSRC1
     */
    S_CMP_GT_I32,
    /**
     * Syntax: S_CMP_GT_U32 SSRC0, SSRC1
     * Operation:
     * SCC = SSRC0 > SSRC1
     */
    S_CMP_GT_U32,
    /**
     * Syntax: S_CMP_LE_I32 SSRC0, SSRC1
     * Operation:
     * SCC = (INT32)SSRC0 <= (INT32)SSRC1
     */
    S_CMP_LE_I32,
    /**
     * Syntax: S_CMP_LE_U32 SSRC0, SSRC1
     * Operation:
     * SCC = SSRC0 <= SSRC1
     */
    S_CMP_LE_U32,
    /**
     * Syntax: S_CMP_LG_I32 SSRC0, SSRC1
     * Operation:
     * SCC = SSRC0!=SSRC1
     */
    S_CMP_LG_I32,
    /**
     *   Syntax: S_CMP_LG_I32 SSRC0, SSRC1
     *   Operation:
     *   SCC = SSRC0!=SSRC1
     */
    S_CMP_LG_U32,
    /**
     * Syntax: S_CMP_LG_U64 SSRC0(2), SSRC1(2)
     * Operation:
     * SCC = SSRC0!=SSRC1
     */
    S_CMP_LG_U64,
    /**
     * Syntax: S_CMP_NE_U64 SSRC0(2), SSRC1(2)
     * Operation:
     * SCC = SSRC0!=SSRC1
     */
    S_CMP_NE_U64,
    /**
     * Syntax: S_CMP_LT_I32 SSRC0, SSRC1
     * Operation:
     * SCC = (INT32)SSRC0 < (INT32)SSRC1
     */
    S_CMP_LT_I32,
    /**
     * Syntax: S_CMP_LT_U32 SSRC0, SSRC1
     * Operation:
     * SCC = SSRC0 < SSRC1
     */
    S_CMP_LT_U32,
    /**
     * Syntax:S_SET_GPR_IDX_ON SSRC0(0), IMM8
     * Operation:
     * MODE = (MODE & ~(1U<<27)) | (1U<<27)
     * M0 = (M0 & 0xffff0f00) | ((IMM8 & 15)<<12) | (SSRC0 & 0xff)
     */
    S_SET_GPR_IDX_ON,
    /**
     * Syntax: S_SETVSKIP SSRC0, SSRC1
     * Operation:
     * VSKIP = (SSRC0 & 1<<(SSRC1&31)) != 0
     */
    S_SETVSKIP,
    // END SOPC

    // SOPP
    /**
     * Syntax: S_BARRIER
     * Description: Synchronize waves within workgroup.
     */
    S_BARRIER,
    /**
     * Syntax: S_BRANCH RELADDR
     * Description: Jump to address RELADDR (store RELADDR to PC).
     * Operation:
     * PC = RELADDR
     */
    S_BRANCH,
    /**
     * Syntax: S_CBRANCH_CDBGSYS RELADDR
     * Description: Jump to address RELADDR if COND_DBG_SYS status bit is set.
     */
    S_CBRANCH_CDBGSYS,
    /**
     *  Syntax: S_CBRANCH_CDBGSYS_AND_USER RELADDR
     *  Description: Jump to address RELADDR if COND_DBG_SYS and COND_DBG_USER status bit is set.
     */
    S_CBRANCH_CDBGSYS_AND_USER,
    /**
     * Syntax: S_CBRANCH_CDBGSYS_OR_USER RELADDR
     * Description: Jump to address RELADDR if COND_DBG_SYS or COND_DBG_USER status bit is set.
     */
    S_CBRANCH_CDBGSYS_OR_USER,
    /**
     * Syntax: S_CBRANCH_CDBGUSER RELADDR
     * Description: Jump to address RELADDR if COND_DBG_USER status bit is set.
     */
    S_CBRANCH_CDBGUSER,
    /**
     *  Syntax: S_CBRANCH_EXECNZ RELADDR
     *  Description: If EXEC is not zero then jump to RELADDR, otherwise jump to
     *  next instruction.
     *  Operation:
     *  PC = EXEC!=0 ? RELADDR : PC+4
     */
    S_CBRANCH_EXECNZ,
    /**
     * Syntax: S_CBRANCH_EXECZ RELADDR
     * Description: If EXEC is zero then jump to RELADDR, otherwise jump to
     * next instruction.
     * Operation:
     * PC = EXEC == 0 ? RELADDR : PC+4
     */
    S_CBRANCH_EXECZ,
    /**
     * Syntax: S_CBRANCH_SCC0 RELADDR
     * Description: If SCC is zero then jump to RELADDR, otherwise jump to next instruction.
     * Operation:
     * PC = SCC0==0 ? RELADDR : PC+4
     */
    S_CBRANCH_SCC0,
    /**
     * Syntax: S_CBRANCH_SCC1 RELADDR
     * Description: If SCC is one then jump to RELADDR, otherwise jump to next instruction.
     * Operation:
     * PC = SCC0==1 ? RELADDR : PC+4
     */
    S_CBRANCH_SCC1,
    /**
     * Syntax: S_CBRANCH_VCCNZ RELADDR
     * Description: If VCC is not zero then jump to RELADDR, otherwise jump to
     * next instruction. Operation: PC = VCC!=0 ? RELADDR : PC+4
     */
    S_CBRANCH_VCCNZ,
    /**
     * Syntax: S_CBRANCH_VCCZ RELADDR
     * Description: If VCC is zero then jump to RELADDR, otherwise jump to next
     * instruction. Operation: PC = VCC==0 ? RELADDR : PC+4
     */
    S_CBRANCH_VCCZ,
    /**
     * Syntax: S_DECPERFLEVEL SIMM16
     * Description: Decrement performance counter specified in SIMM16&15 by 1.
     * Operation:
     * PERFCNT[SIMM16 & 15]--
     */
    S_DECPERFLEVEL,
    /**
     * Syntax: S_ENDPGM
     * Description: End program.
     */
    S_ENDPGM,
    /**
     *     Description: End of program; signal that a wave has exited its POPS
     * critical section and terminate wavefront. The hardware implicitly
     * executes S_WAITCNT 0 before executing this instruction. This instruction
     * is an optimization that combines S_SENDMSG(MSG_ORDERED_PS_DONE) and
     * S_ENDPGM. (from ISA manual)
     */
    S_ENDPGM_ORDERED_PS_DONE,
    /**
     * Syntax: S_ENDPGM_SAVED
     * Description: End of program; signal that a wave has been saved by the
     * context-switch trap handler, and terminate wavefront. The hardware
     * implicitly executes S_WAITCNT 0 before executing this instruction. Use
     * S_ENDPGM in all cases unless you are executing the context-switch save
     * handler. (from ISA manual)
     */
    S_ENDPGM_SAVED,
    /**
     * Syntax: S_ICACHE_INV
     * Description: Invalidate entire L1 instruction cache.
     */
    S_ICACHE_INV,
    /**
     * Syntax: S_INCPERFLEVEL SIMM16
     * Description: Increment performance counter specified in SIMM16&15 by 1.
     * Operation:
     * PERFCNT[SIMM16 & 15]++
     */
    S_INCPERFLEVEL,
    /**
     * Syntax: S_NOP SIMM16
     * Description: Do nothing by (SIMM16&7) + 1 cycles.
     * Operation: nothing
     */
    S_NOP,
    /**
     * Syntax: S_SENDMSG SENDMSG(MSG, GS_OP, STREAMID)
     * Description: Send message. List of messages:
     *      INTERRUPT, MSG_INTERRUPT - interrupt. M0&0xff - carries user data, IDs also sent (wave_id, cu_id, ...)
     *      GS, MSG_GS
     *      GS_DONE, MSG_GS_DONE
     *      SYSMSG, MSG_SYSMSG, SYSTEM, MSG_SYSTEM
     * List of the GSOP's:
     *      NOP, GS_NOP - M0&0xff defines wave id. only GS_DONE
     *      CUT, GS_CUT - (SIMM16 & 0x300)>>8 - streamid, EXEC also sent, M0&0xff - gs waveID
     *      EMIT, GS_EMIT - (SIMM16 & 0x300)>>8 - streamid, EXEC also sent, M0&0xff - gs waveID
     *      EMIT_CUT, GS_EMIT_CUT, EMIT-CUT - (SIMM16 & 0x300)>>8 - streamid, EXEC also sent, M0&0xff - gs waveID
     */
    S_SENDMSG,
    /**
     * Syntax: S_SENDMSGHALT SENDMSG(MSG, GS_OP, STREAMID)
     * Description: Send message and halt.
     */
    S_SENDMSGHALT,
    /**
     * Syntax: S_SET_GPR_IDX_MODE SIMM16
     * Description: Set GPR indexing mode (12-15 bits in MO).
     * Operation:
     * M0 = (M0 & 0xffff0fff) | ((SIMM16 & 15)<<12)
     */
    S_SET_GPR_IDX_MODE,
    /**
     * Syntax: S_SET_GPR_IDX_OFF
     * Description: Disables GPR indexing.
     * Operation:
     * MODE = (MODE & ~(1U<<27))
     */
    S_SET_GPR_IDX_OFF,
    /**
     * Syntax: S_SETHALT SIMM16
     * Description: Set HALT bit to value SIMM16&1. 1 - halt, 0 - resume. Halt
     * is ignored while PRIV is 1. Operation: HALT = SIMM16&1
     */
    S_SETHALT,
    /**
     * Syntax: S_SETKILL SIMM16
     * Description: Store SIMM16&1 to KILL.
     * Operation:
     * KILL = SIMM16&1
     */
    S_SETKILL,
    /**
     * Syntax: S_SETPRIO SIMM16
     * Description: Set priority to SIMM16&3.
     * Operation:
     * PRIORITY = SIMM16&3
     */
    S_SETPRIO,
    /**
     * Syntax: S_SLEEP SIMM16
     * Description: Sleep approximately by (SIMM16&0x7)*64 cycles.
     */
    S_SLEEP,
    /**
     * Syntax: S_TRAP SIMM16
     * Description: Enter the trap handler.
     */
    S_TRAP,
    /**
     *  Syntax: S_TTRACEDATA
     *  Description: Send M0 as user data to thread-trace.
     */
    S_TTRACEDATA,
    /**
     * Wait for the counts of outstanding lds, vector-memory and
     * export/vmem-write-data to be at or below the specified levels.
     * SIMM16[3:0] = vmcount (vector memory operations) lower bits [3:0],
     * SIMM16[6:4] = export/mem-write-data count,
     * SIMM16[11:8] = LGKM_cnt (scalar-mem/GDS/LDS count),
     * SIMM16[15:14] = vmcount (vector memory operations) upper bits [5:4]
     */
    S_WAITCNT,
    // END SOPP


    // SOP1
    /**
     * Syntax: S_ABS_B32 SDST, SSRC0
     * Operation:
     * SDST = ABS(SSRC0)
     * SCC = SDST!=0
     */
    S_ABS_I32,
    /**
     * Syntax: S_AND_SAVEEXEC_B64 SDST(2), SSRC0(2)
    Operation:
    SDST = EXEC
    EXEC = SSRC0 & EXEC
    SCC = EXEC!=0

     */
    S_AND_SAVEEXEC_B64,
    /**
     * Syntax: S_ANDN2_SAVEEXEC_B64 SDST(2), SSRC0(2)
     * Operation:
     * SDST = EXEC
     * EXEC = ~SSRC0 & EXEC
     * SCC = EXEC!=0
     */
    S_ANDN1_SAVEEXEC_B64,
    /**
     * Syntax: S_ANDN1_WREXEC_B64 SDST(2), SSRC0(2)
     * Operation:
     * EXEC = ~SSRC0 & EXEC
     * SDST = EXEC
     * SCC = EXEC!=0
     */
    S_ANDN1_WREXEC_B64,
    /**
     * Syntax: S_ANDN2_SAVEEXEC_B64 SDST(2), SSRC0(2)
     * Operation:
     * SDST = EXEC
     * EXEC = SSRC0 & ~EXEC
     * SCC = EXEC!=0
     */
    S_ANDN2_SAVEEXEC_B64,
    /**
     * Syntax: S_ANDN2_WREXEC_B64 SDST(2), SSRC0(2)
     * Operation:
     * EXEC = SSRC0 & ~EXEC
     * SDST = EXEC
     * SCC = EXEC!=0
     */
    S_ANDN2_WREXEC_B64,
    /**
     * Syntax: S_BCNT0_I32_B32 SDST, SSRC0
     * Operation:
     * SDST = BITCOUNT(~SSRC0)
     * SCC = SDST!=0
     */
    S_BCNT0_I32_B32,
    /**
     * Syntax: S_BCNT0_I32_B64 SDST, SSRC0(2)
     * Operation:
     * SDST = BITCOUNT(~SSRC0)
     * SCC = SDST!=0
     */
    S_BCNT0_I32_B64,
    /**
     * Syntax: S_BCNT1_I32_B64 SDST, SSRC0
     * Operation:
     * SDST = BITCOUNT(SSRC0)
     * SCC = SDST!=0
     */
    S_BCNT1_I32_B32,
    /**
     * Syntax: S_BCNT1_I32_B64 SDST, SSRC0(2)
     * Operation:
     * SDST = BITCOUNT(SSRC0)
     * SCC = SDST!=0
     */
    S_BCNT1_I32_B64,
    /**
     * Syntax: S_BITREPLICATE_B64_B32 SDST(2), SSRC0
     * Operation:
     * SDST = 0
     * for (BYTE I=0; I<32; I++)
     * SDST |= (((SSRC0>>I)&1)*3)<<(I<<1)
     */
    S_BITREPLICATE_B64_B32,
    /**
     * Syntax: S_BITSET0_B32 SDST, SSRC0
     * Operation:
     * SDST &= ~(1U << (SSRC0&31))
     */
    S_BITSET0_B32,
    /**
     * Syntax: S_BITSET0_B64 SDST(2), SSRC0
     * Operation:
     * SDST &= ~(1ULL << (SSRC0&63))
     */
    S_BITSET0_B64,
    /**
     * Syntax: S_BITSET1_B32 SDST, SSRC0
     * Operation:
     * SDST |= 1U << (SSRC0&31)
     */
    S_BITSET1_B32,
    /**
     * Syntax: S_BITSET1_B64 SDST(2), SSRC0
     * Operation:
     * SDST |= 1ULL << (SSRC0&63)
     */
    S_BITSET1_B64,
    /**
     * Syntax: S_BREV_B32 SDST, SSRC0
     * Operation:
     * SDST = REVBIT(SSRC0)
     */
    S_BREV_B32,
    /**
     * Syntax: S_BREV_B64 SDST(2), SSRC0(2)
     * Operation:
     * SDST = REVBIT(SSRC0)
     */
    S_BREV_B64,
    /**
     * Syntax: S_CBRANCH_JOIN SSRC0
     * Operation:
     * if (CSP==SSRC0)
     *   PC += 4
     * else {
     *   CSP--
     *   EXEC = SGPR[CSP*4:CSP*4+1]
     *   PC = SGPRS[CSP*4+2:CSP*4+3]
     * }
     */
    S_CBRANCH_JOIN,
    /**
     * Syntax: S_CMOV_B32 SDST, SSRC0
     * Operation:
     * SDST = SCC ? SSRC0 : SDST
     */
    S_CMOV_B32,
    /**
     * Syntax: S_CMOV_B64 SDST(2), SSRC0(2)
     * Operation:
     * SDST = SCC ? SSRC0 : SDST
     */
    S_CMOV_B64,
    /**
     * Syntax: S_FF0_I32_B32 SDST, SSRC0
     * Operation:
     * SDST = -1
     * for (UINT8 i = 0; i < 32; i++)
     * if ((1U<<i) & SSRC0) == 0)
     * { SDST = i; break; }
     */
    S_FF0_I32_B32,
    /**
     * Syntax: S_FF0_I32_B64 SDST, SSRC0(2)
     * Operation:
     * SDST = -1
     * for (UINT8 i = 0; i < 64; i++)
     * if ((1ULL<<i) & SSRC0) == 0)
     * { SDST = i; break; }
     */
    S_FF0_I32_B64,
    /**
     * Syntax: S_FF1_I32_B32 SDST, SSRC0
     * Operation:
     * SDST = -1
     * for (UINT8 i = 0; i < 32; i++)
     * if ((1U<<i) & SSRC0) != 0)
     * { SDST = i; break; }
     */
    S_FF1_I32_B32,
    /**
     * Syntax: S_FF0_I32_B64 SDST, SSRC0(2)
     * Operation:
     * SDST = -1
     * for (UINT8 i = 0; i < 64; i++)
     * if ((1ULL<<i) & SSRC0) != 0)
     * { SDST = i; break; }
     */
    S_FF1_I32_B64,
    /**
     * Syntax: S_FLBIT_I32_B32 SDST, SSRC0
     * Operation:
     * SDST = -1
     * for (INT8 i = 31; i >= 0; i--)
     * if ((1U<<i) & SSRC0) != 0)
     * { SDST = 31-i; break; }
     */
    S_FLBIT_I32_B32,
    /**
     * Syntax: S_FLBIT_I32_B64 SDST, SSRC0(2)
     * Operation:
     * SDST = -1
     * for (INT8 i = 63; i >= 0; i--)
     * if ((1ULL<<i) & SSRC0) != 0)
     * { SDST = 63-i; break; }
     */
    S_FLBIT_I32_B64,
    /**
     * Syntax: S_FLBIT_I32 SDST, SSRC0
     * Operation:
     * SDST = -1
     * UINT32 bitval = (INT32)SSRC0>=0 ? 1 : 0
     * for (INT8 i = 31; i >= 0; i--)
     * if ((1U<<i) & SSRC0) == (bitval<<i))
     *   { SDST = 31-i; break; }
     */
    S_FLBIT_I32,
    /**
     * Syntax: S_FLBIT_I32_I64 SDST, SSRC0(2)
    Operation:
    SDST = -1
    UINT64 bitval = (INT64)SSRC0>=0 ? 1 : 0
    for (INT8 i = 63; i >= 0; i--)
    if ((1U<<i) & SSRC0) == (bitval<<i))
    { SDST = 63-i; break; }

     */
    S_FLBIT_I32_I64,
    /**
     * Syntax: S_GETPC_B64 SDST(2)
     * Operation:
     * SDST = PC + 4
     */
    S_GETPC_B64,
    /**
     * Syntax: S_MOV_B32 SDST, SSRC0
     * Operation:
     * SDST = SSRC0
     */
    S_MOV_B32,
    /**
     * Syntax: S_MOV_B64 SDST(2), SSRC0(2)
     * Operation:
     * SDST = SSRC0
     */
    S_MOV_B64,
    /**
     * Syntax: S_MOVRELD_B32 SDST, SSRC0
     * Operation:
     * SGPR[SDST_NUMBER + M0] = SSRC0
     */
    S_MOVRELD_B32,
    /**
     * Syntax: S_MOVRELD_B64 SDST, SSRC0
     * Operation:
     * SGPR[SDST_NUMBER + M0 : SDST_NUMBER + M0 + 1] = SSRC0
     */
    S_MOVRELD_B64,
    /**
     * Syntax: S_MOVRELS_B32 SDST, SSRC0
     * Operation:
     * SDST = SGPR[SSRC0_NUMBER + M0]
     */
    S_MOVRELS_B32,
    /**
     * Syntax: S_MOVRELS_B64 SDST(2), SSRC0(2)
     * Operation:
     * SDST = SGPR[SSRC0_NUMBER + M0 : SSRC0_NUMBER + M0 + 1]
     */
    S_MOVRELS_B64,
    /**
     * Syntax: S_NAND_SAVEEXEC_B64 SDST(2), SSRC0(2)
     * Operation:
     * SDST = EXEC
     * EXEC = ~(SSRC0 & EXEC)
     * SCC = EXEC!=0
     */
    S_NAND_SAVEEXEC_B64,
    /**
     * Syntax: S_NOR_SAVEEXEC_B64 SDST(2), SSRC0(2)
     * Operation:
     * SDST = EXEC
     * EXEC = ~(SSRC0 | EXEC)
     * SCC = EXEC!=0
     */
    S_NOR_SAVEEXEC_B64,
    /**
     * Syntax: S_NOT_B32 SDST, SSRC0
     * Operation:
     * SDST = ~SSRC0
     * SCC = SDST!=0
     */
    S_NOT_B32,
    /**
     * Syntax: S_NOT_B64 SDST(2), SSRC0(2)
     * Operation:
     * SDST = ~SSRC0
     * SCC = SDST!=0
     */
    S_NOT_B64,
    /**
     * Syntax: S_OR_SAVEEXEC_B64 SDST(2), SDST(2)
     * Operation:
     * SDST = EXEC
     * EXEC = SSRC0 | EXEC
     * SCC = EXEC!=0
     */
    S_OR_SAVEEXEC_B64,
    /**
     * Syntax: S_ORN2_SAVEEXEC_B64 SDST(2), SSRC0(2)
     * Operation:
     * SDST = EXEC
     * EXEC = ~SSRC0 & EXEC
     * SCC = EXEC!=0
     */
    S_ORN2_SAVEEXEC_B64,
    /**
     * Syntax: S_QUADMASK_B32 SDST, SSRC0
     * Operation:
     * UINT32 temp = 0
     * for (UINT8 i = 0; i < 8; i++)
     * temp |= ((SSRC0>>(i<<2)) & 15)!=0 ? (1U<<i) : 0
     * SDST = temp
     * SCC = SDST!=0
     */
    S_QUADMASK_B32,
    /**
     * Syntax: S_QUADMASK_B64 SDST(2), SSRC0(2)
     * Operation:
     * UINT64 temp = 0
     * for (UINT8 i = 0; i < 16; i++)
     * temp |= ((SSRC0>>(i<<2)) & 15)!=0 ? (1U<<i) : 0
     * SDST = temp
     * SCC = SDST!=0
     */
    S_QUADMASK_B64,
    /**
     * Syntax: S_RFE_B64 SSRC0(2)
     * Operation: ???
     * PC = TTMP[0:1]
     */
    S_RFE_B64,
    /**
     * Syntax S_SET_GPR_IDX_IDX SSRC0(1)
     * Operation:
     * M0 = (M0 & 0xffffff00) | (SSRC0 & 0xff)
     */
    S_SET_GPR_IDX_IDX,
    /**
     * Syntax: S_SETPC_B64 SSRC0(2)
     * Operation:
     * PC = SSRC0
     */
    S_SETPC_B64,
    /**
     * Syntax: S_SEXT_I32_I8 SDST, SSRC0
     * Operation:
     * SDST = SEXT((INT8)SSRC0)
     */
    S_SEXT_I32_I8,
    /**
     * Syntax: S_SEXT_I32_I16 SDST, SSRC0
     * Operation:
     * SDST = SEXT((INT16)SSRC0)
     */
    S_SEXT_I32_I16,
    /**
     * Syntax: S_SWAPPC_B64 SDST(2), SSRC0(2)
     * Operation:
     * SDST = PC + 4
     * PC = SSRC0
     */
    S_SWAPPC_B64,
    /**
     * Syntax: S_WQM_B32 SDST, SSRC0
     * Operation:
     * UINT32 temp = 0
     * for (UINT8 i = 0; i < 32; i+=4)
     * temp |= ((SSRC0>>i) & 15)!=0 ? (15<<i) : 0
     * SDST = temp
     * SCC = SDST!=0
     */
    S_WQM_B32,
    /**
     * Syntax: S_WQM_B64 SDST(2), SSRC0(2)
     * Operation:
     * UINT64 temp = 0
     * for (UINT8 i = 0; i < 64; i+=4)
     * temp |= ((SSRC0>>i) & 15)!=0 ? (15ULL<<i) : 0
     * SDST = temp
     * SCC = SDST!=0
     */
    S_WQM_B64,
    /**
     * Syntax: S_XNOR_SAVEEXEC_B64 SDST(2), SSRC0(2)
     * Operation:
     * SDST = EXEC
     * EXEC = ~(SSRC0 ^ EXEC)
     * SCC = EXEC!=0
     */
    S_XNOR_SAVEEXEC_B64,
    /**
     * Syntax: S_XOR_SAVEEXEC_B64 SDST(2), SSRC0(2)
     * Operation:
     * SDST = EXEC
     * EXEC = SSRC0 ^ EXEC
     * SCC = EXEC!=0
     */
    S_XOR_SAVEEXEC_B64,
    // END SOP1

    // SOP2
    /**
     * Syntax: S_ABSDIFF_I32 SDST, SSRC0, SSRC1
     * Operation:
     * SDST = ABS(SSRC0 - SSRC1)
     * SCC = SDST!=0
     */
    S_ABSDIFF_I32,
    /**
     * UINT64 temp = (UINT64)SSRC0 + (UINT64)SSRC1 + SCC
     * SDST = temp
     * SCC = temp >> 32
     */
    S_ADDC_U32,
    /**
     *   SDST = SSRC0 + SSRC1
     *   INT64 temp = SEXT64(SSRC0) + SEXT64(SSRC1)
     *   SCC = temp > ((1LL<<31)-1) || temp < (-1LL<<31)
     */
    S_ADD_I32,
    /**
     * D.u = S0.u + S1.u;
     * SCC = (S0.u + S1.u >= 0x100000000ULL ? 1 : 0). // unsigned
     * overflow/carry-out, S_ADDC_U32
     */
    S_ADD_U32,
    /**
     * SDST = SSRC0 & SSRC1
     * SCC = SDST!=0
     */
    S_AND_B32,
    /**
     * SDST = SSRC0 & SSRC1
     * SCC = SDST!=0
     */
    S_AND_B64,
    /**
     * SDST = SSRC0 & ~SSRC1
     * SCC = SDST!=0
     */
    S_ANDN2_B32,
    /**
     *  SDST = SSRC0 & ~SSRC1
     *  SCC = SDST!=0
     */
    S_ANDN2_B64,
    /**
     * SDST = (INT32)SSRC0 >> (SSRC1 & 31)
     * SCC = SDST!=0
     */
    S_ASHR_I32,
    /**
     * SDST = (INT64)SSRC0 >> (SSRC1 & 63)
     * SCC = SDST!=0
     */
    S_ASHR_I64,
    /**
     * UINT8 shift = SSRC1 & 31
     * UINT8 length = (SSRC1>>16) & 0x7f
     * if (length==0)
     *  SDST = 0
     * if (shift+length < 32)
     *  SDST = (INT32)(SSRC0 << (32 - shift - length)) >> (32 - length)
     * else
     *  SDST = (INT32)SSRC0 >> shift
     * SCC = SDST!=0
     */
    S_BFE_I32,
    /**
     * UINT8 shift = SSRC1 & 63
     * UINT8 length = (SSRC1>>16) & 0x7f
     * if (length==0)
     *  SDST = 0
     * if (shift+length < 64)
     *  SDST = (INT64)(SSRC0 << (64 - shift - length)) >> (64 - length)
     *  else
     *  SDST = (INT64)SSRC0 >> shift
     *  SCC = SDST!=0
     */
    S_BFE_I64,
    /**
     * UINT8 shift = SSRC1 & 31
     * UINT8 length = (SSRC1>>16) & 0x7f
     * if (length==0)
     *   SDST = 0
     * if (shift+length < 32)
     *   SDST = SSRC0 << (32 - shift - length) >> (32 - length)
     * else
     *   SDST = SSRC0 >> shift
     * SCC = SDST!=0
     */
    S_BFE_U32,
    /**
     * UINT8 shift = SSRC1 & 63
     * UINT8 length = (SSRC1>>16) & 0x7f
     * if (length==0)
     *   SDST = 0
     * if (shift+length < 64)
     *   SDST = SSRC0 << (64 - shift - length) >> (64 - length)
     * else
     *   SDST = SSRC0 >> shift
     * SCC = SDST!=0
     */
    S_BFE_U64,
    /**
     * SDST = ((1U << (SSRC0&31))-1) << (SSRC1&31)
     */
    S_BFM_B32,
    /**
     * SDST = ((1ULL << (SSRC0&63))-1) << (SSRC1&63)
     */
    S_BFM_B64,
    /**
     * UINT64 passes = (EXEC & SSRC0)
     * UINT64 failures = (EXEC & ~SSRC0)
     * if (passes == EXEC)
     *   PC = SSRC1
     * else if (failures == EXEC)
     *   PC += 4
     * else if (BITCOUNT(failures) < BITCOUNT(passes)) {
     *   EXEC = failures
     *   SGPR[CSP*4:CSP*4+1] = passes
     *   SGPR[CSP*4+2:CSP*4+3] = SSRC1
     *   CSP++
     *   PC += 4 //jump to failure
     * } else {
     *   EXEC = passes
     *   SGPR[CSP*4:CSP*4+1] = failures
     *   SGPR[CSP*4+2:CSP*4+3] = PC+4
     *   CSP++
     *   PC = SSRC1  //jump to passes
     * }
     */
    S_CBRANCH_G_FORK,
    /**
     * SDST = SCC ? SSRC0 : SSRC1
     */
    S_CSELECT_B32,
    /**
     * SDST = SCC ? SSRC0 : SSRC1
     */
    S_CSELECT_B64,
    /**
     * SDST = SSRC0 << (SSRC1 & 31)
     * SCC = SDST != 0
     */
    S_LSHL_B32,
    /**
     * SDST = SSRC0 << (SSRC1 & 63)
     * SCC = SDST != 0
     */
    S_LSHL_B64,
    /**
     * UINT64 TMP = (SSRC0 << 1) + SSRC1
     * SDST = TMP & 0xffffffff
     * SCC = TMP >= (1ULL << 32)
     */
    S_LSHL1_ADD_U32,
    /**
     * UINT64 TMP = (SSRC0 << 2) + SSRC1
     * SDST = TMP & 0xffffffff
     * SCC = TMP >= (1ULL << 32)
     */
    S_LSHL2_ADD_U32,
    /**
     * UINT64 TMP = (SSRC0 << 3) + SSRC1
     * SDST = TMP & 0xffffffff
     * SCC = TMP >= (1ULL << 32)
     */
    S_LSHL3_ADD_U32,
    /**
     * UINT64 TMP = (SSRC0 << 4) + SSRC1
     * SDST = TMP & 0xffffffff
     * SCC = TMP >= (1ULL << 32)
     */
    S_LSHL4_ADD_U32,
    /**
     * SDST = SSRC0 >> (SSRC1 & 31)
     * SCC = SDST != 0
     */
    S_LSHR_B32,
    /**
     * SDST = SSRC0 >> (SSRC1 & 63)
     * SCC = SDST != 0
     */
    S_LSHR_B64,
    /**
     * SDST = MAX((INT32) SSRC0, (INT32) SSRC1)
     * SCC = (INT32) SSRC0 > (INT32) SSRC1
     */
    S_MAX_I32,
    /**
     * SDST = MAX(SSRC0, SSRC1)
     * SCC = SSRC0 > SSRC1
     */
    S_MAX_U32,
    /**
     * SDST = MIN((INT32) SSRC0, (INT32) SSRC1)
     * SCC = (INT32) SSRC0 < (INT32) SSRC1
     */
    S_MIN_I32,
    /**
     * SDST = MIN(SSRC0, SSRC1)
     * SCC = SSRC0 < SSRC1
     */
    S_MIN_U32,
    /**
     * SDST = ((INT64) SSRC0 * (INT32) SSRC1) >> 32
     */
    S_MUL_HI_I32,
    /**
     * SDST = ((UINT64) SSRC0 * SSRC1) >> 32
     */
    S_MUL_HI_U32,
    /**
     * SDST = SSRC0 * SSRC1
     */
    S_MUL_I32,
    /**
     * SDST = ~(SSRC0 & SSRC1)
     * SCC = SDST != 0
     */
    S_NAND_B32,
    /**
     * SDST = ~(SSRC0 & SSRC1)
     * SCC = SDST != 0
     */
    S_NAND_B64,
    /**
     * SDST = ~(SSRC0 | SSRC1)
     * SCC = SDST != 0
     */
    S_NOR_B32,
    /**
     * SDST = ~(SSRC0 | SSRC1)
     * SCC = SDST != 0
     */
    S_NOR_B64,
    /**
     * SDST = SSRC0 | SSRC1
     * SCC = SDST != 0
     */
    S_OR_B32,
    /**
     * SDST = SSRC0 | SSRC1
     * SCC = SDST != 0
     */
    S_OR_B64,
    /**
     * SDST = SSRC0 | ~SSRC1
     * SCC = SDST != 0
     */
    S_ORN2_B32,
    /**
     * SDST = SSRC0 | ~SSRC1
     * SCC = SDST != 0
     */
    S_ORN2_B64,
    /**
     * SDST = (SSRC0 >> 16) | (SSRC1 & 0xffff0000)
     */
    S_PACK_HH_B32_B16,
    /**
     * SDST = (SSRC0 & 0xffff) | (SSRC1 & 0xffff0000)
     */
    S_PACK_LH_B32_B16,
    /**
     * Operation:
     * SDST = (SSRC0 & 0xffff) | ((SSRC1 & 0xffff) << 16)
     */
    S_PACK_LL_B32_B16,
    /**
     * Syntax: S_RFE_RESTORE_B64 SDST(2), SSRC0(1)
     * Description: Return from exception handler and set: INST_ATC =
     * SSRC1.U32[0] ???
     */
    S_RFE_RESTORE_B64,
    /**
     * Syntax: S_SUBB_U32 SDST, SSRC0, SSRC1
     * Operation:
     * UINT64 temp = (UINT64)
     * SSRC0 - (UINT64)SSRC1 - SCC
     * SDST = temp
     * SCC = (temp >> 32) & 1
     */
    S_SUBB_U32,
    /**
     * Syntax: S_SUB_I32 SDST, SSRC0, SSRC1
     * Operation:
     * SDST = SSRC0 - SSRC1
     * INT64 temp = SEXT64(SSRC0) - SEXT64(SSRC1)
     * SCC = temp > ((1LL << 31) - 1) || temp < (-1LL << 31)
     */
    S_SUB_I32,
    /**
     * Syntax: S_SUB_U32 SDST, SSRC0, SSRC1
     * Operation:
     * UINT64 temp = (UINT64)
     * SSRC0 - (UINT64)SSRC1
     * SDST = temp
     * SCC = (temp >> 32) != 0
     */
    S_SUB_U32,
    /**
     * Syntax: S_XNOR_B32 SDST, SSRC0, SSRC1
     * Operation:
     * SDST = ~(SSRC0 ^ SSRC1)
     * SCC = SDST != 0
     */
    S_XNOR_B32,
    /**
     * Syntax: S_XNOR_B64 SDST(2), SSRC0(2), SSRC1(2)
     * Operation:
     * SDST = ~(SSRC0 ^ SSRC1)
     * SCC = SDST != 0
     */
    S_XNOR_B64,
    /**
     * Syntax: S_XOR_B32 SDST, SSRC0, SSRC1
     * Operation:
     * SDST = SSRC0 ^SSRC1
     * SCC = SDST != 0
     */
    S_XOR_B32,
    /**
     * Syntax: S_XOR_B64 SDST(2), SSRC0(2), SSRC1(2)
     * Operation:
     * SDST = SSRC0 ^SSRC1
     * SCC = SDST != 0
     */
    S_XOR_B64,
    // END SOP2

    // SOPK
    /**
     * Syntax: S_ADDK_I32 SDST, SIMM16
     * Operation:
     * SDST = SDST + SIMM16
     * INT64 temp = SEXT64(SDST) + SEXT64(SIMM16)
     * SCC = temp > ((1LL<<31)-1) || temp < (-1LL<<31)
     */
    S_ADDK_I32,
    /**
     * Syntax: S_CALL_B64 SDST(2), RELADDR
     * Operation:
     * SDST = PC + 4
     * PC = RELADDR
     */
    S_CALL_B64,
    /**
     * Syntax: S_CBRANCH_I_FORK SSRC0(2), RELADDR
     * Operation:
     * UINT64 passes = (EXEC & SSRC0)
     * UINT64 failures = (EXEC & ~SSRC0)
     * if (passes == EXEC)
     *  PC = RELADDR
     * else if (failures == EXEC)
     *  PC += 4
     * else if (BITCOUNT(failures) < BITCOUNT(passes)) {
     *  EXEC = failures
     *  SGPR[CSP*4:CSP*4+1] = passes
     *  SGPR[CSP*4+2:CSP*4+3] = RELADDR
     *  CSP++
     *  PC += 4 //jump to failure
     * } else {
     *  EXEC = passes
     *  SGPR[CSP*4:CSP*4+1] = failures
     *  SGPR[CSP*4+2:CSP*4+3] = PC+4
     *  CSP++
     *  PC = RELADDR //jump to passes
     * }
     */
    S_CBRANCH_I_FORK,
    /**
     * Syntax: S_MOVK_I32 SDST, SIMM16
     * Operation:
     * SDST = SCC ? SIMM16 : SDST
     */
    S_CMOVK_I32,
    /**
     * Syntax: S_CMPK_EQ_I32 SDST, SIMM16
     * Operation:
     * SCC = (INT32)SDST == SIMM16
     */
    S_CMPK_EQ_I32,
    /**
     * Syntax: S_CMPK_EQ_U32 SDST, IMM16
     * Operation:
     * SCC = SDST == IMM16
     */
    S_CMPK_EQ_U32,
    /**
     * Syntax: S_CMPK_GE_I32 SDST, SIMM16
     * Operation:
     * SCC = (INT32)SDST >= SIMM16
     */
    S_CMPK_GE_I32,
    /**
     * Syntax: S_CMPK_GE_U32 SDST, IMM16
     * Operation:
     * SCC = SDST >= IMM16
     */
    S_CMPK_GE_U32,
    /**
     * Syntax: S_CMPK_GT_I32 SDST, SIMM16
     * Operation:
     * SCC = (INT32)SDST > SIMM16
     */
    S_CMPK_GT_I32,
    /**
     * Syntax: S_CMPK_GT_U32 SDST, IMM16
     * Operation:
     * SCC = SDST > IMM16
     */
    S_CMPK_GT_U32,
    /**
     * Syntax: S_CMPK_LE_I32 SDST, SIMM16
     * Operation:
     * SCC = (INT32)SDST <= SIMM16
     */
    S_CMPK_LE_I32,
    /**
     * Syntax: S_CMPK_LE_U32 SDST, IMM16
     * Operation:
     * SCC = SDST <= IMM16
     */
    S_CMPK_LE_U32,
    /**
     * Syntax: S_CMPK_LG_I32 SDST, SIMM16
     * Operation:
     * SCC = (INT32)SDST != SIMM16
     */
    S_CMPK_LG_I32,
    /**
     * Syntax: S_CMPK_LG_U32 SDST, IMM16
     * Operation:
     * SCC = SDST != IMM16
     */
    S_CMPK_LG_U32,
    /**
     * Syntax: S_CMPK_LT_I32 SDST, SIMM16
     * Operation:
     * SCC = (INT32)SDST < SIMM16
     */
    S_CMPK_LT_I32,
    /**
     * Syntax: S_CMPK_LT_U32 SDST, IMM16
     * Operation:
     * SCC = SDST < IMM16
     */
    S_CMPK_LT_U32,
    /**
     * Syntax: S_GETREG_B32 SDST, HWREG(HWREGNAME, BITOFFSET, BITSIZE)
     * Operation:
     * SDST = (HWREG >> BITOFFSET) & ((1U << BITSIZE) - 1U)
     */
    S_GETREG_B32,
    /**
     * Syntax: S_GETREG_REGRD_B32 SDST, HWREG(HWREGNAME, BITOFFSET, BITSIZE)
     * Operation: ???
     */
    S_GETREG_REGRD_B32,
    /**
     * Syntax: S_MOVK_I32 SDST, SIMM16
     * Operation:
     * SCC = SIMM16
     */
    S_MOVK_I32,
    /**
     * Syntax: S_MULK_I32 SDST, SIMM16
     * Operation:
     * SDST = SDST * SIMM16
     */
    S_MULK_I32,
    /**
     * Syntax: S_SETREG_B32 HWREG(HWREGNAME, BITOFFSET, BITSIZE), SDST
     * Operation:
     * UINT32 mask = ((1U<<BITSIZE) - 1U) << BITOFFSET
     * HWREG = (HWREG & ~mask) | ((SDST<<BITOFFSET) & mask)
     */
    S_SETREG_B32,
    /**
     * Syntax: S_SETREG_B32 HWREG(HWREGNAME, BITOFFSET, BITSIZE), IMM32
     * Operation:
     * UINT32 mask = ((1U<<BITSIZE) - 1U) << BITOFFSET
     * HWREG = (HWREG & ~mask) | ((IMM32<<BITOFFSET) & mask)
     */
    S_SETREG_IMM32_B32,
    // END SOPK

    // VOP1
    /**
     * D.u = S0.u.
     * Input and output modifiers not supported; this is an untyped operation.
     */
    V_MOV_B32,

    // VOP2

    /**
     * D.u = S0.u + S1.u.
     */
    V_ADD_U32,

    /**
     * todo not in ofdoc
     */
    V_ADDC_U32,

    // VOP3A
    /**
     * D.u64 = S1.u64 << S0.u[5:0].
     */
    V_LSHLREV_B64,

    // VOPC
    /**
     * D.u64[threadId] = (S0 == S1).
     */
    V_CMP_EQ_I32,

    // FLAT
    /**
     * Untyped buffer store dword
     */
    FLAT_STORE_DWORD
};

struct InstructionInfo {
    InstructionKey key;

    const char* instr_word;

    InstructionInfo(InstructionKey key, const char* word) {
        this->key = key;
        this->instr_word = word;
    }
};

InstructionInfo get_instruction_info(InstructionKey instruction) {
    static std::unordered_map<InstructionKey, InstructionInfo> instruction_repo{
        // SOP1
        {S_ABS_I32, {S_ABS_I32, "s_abs_i32"}},
        {S_AND_SAVEEXEC_B64, {S_AND_SAVEEXEC_B64, "s_and_saveexec_b64"}},
        {S_ANDN1_SAVEEXEC_B64, {S_ANDN1_SAVEEXEC_B64, "s_andn1_saveexec_b64"}},
        {S_ANDN1_WREXEC_B64, {S_ANDN1_WREXEC_B64, "s_andn1_wrexec_b64"}},
        {S_ANDN2_SAVEEXEC_B64, {S_ANDN2_SAVEEXEC_B64, "s_andn2_saveexec_b64"}},
        {S_ANDN2_WREXEC_B64, {S_ANDN2_WREXEC_B64, "s_andn2_wrexec_b64"}},
        {S_BCNT0_I32_B32, {S_BCNT0_I32_B32, "s_bcnt0_i32_b32"}},
        {S_BCNT0_I32_B64, {S_BCNT0_I32_B64, "s_bcnt0_i32_b64"}},
        {S_BCNT1_I32_B32, {S_BCNT1_I32_B32, "s_bcnt1_i32_b32"}},
        {S_BCNT1_I32_B64, {S_BCNT1_I32_B64, "s_bcnt1_i32_b64"}},
        {S_BITREPLICATE_B64_B32,
         {S_BITREPLICATE_B64_B32, "s_bitreplicate_b64_b32"}},
        {S_BITSET0_B32, {S_BITSET0_B32, "s_bitset0_b32"}},
        {S_BITSET0_B64, {S_BITSET0_B64, "s_bitset0_b64"}},
        {S_BITSET1_B32, {S_BITSET1_B32, "s_bitset1_b32"}},
        {S_BITSET1_B64, {S_BITSET1_B64, "s_bitset1_b64"}},
        {S_BREV_B32, {S_BREV_B32, "s_brev_b32"}},
        {S_BREV_B64, {S_BREV_B64, "s_brev_b64"}},
        {S_CBRANCH_JOIN, {S_CBRANCH_JOIN, "s_cbranch_join"}},
        {S_CMOV_B32, {S_CMOV_B32, "s_cmov_b32"}},
        {S_CMOV_B64, {S_CMOV_B64, "s_cmov_b64"}},
        {S_FF0_I32_B32, {S_FF0_I32_B32, "s_ff0_i32_b32"}},
        {S_FF0_I32_B64, {S_FF0_I32_B64, "s_ff0_i32_b64"}},
        {S_FF1_I32_B32, {S_FF1_I32_B32, "s_ff1_i32_b32"}},
        {S_FF1_I32_B64, {S_FF1_I32_B64, "s_ff1_i32_b64"}},
        {S_FLBIT_I32_B32, {S_FLBIT_I32_B32, "s_flbit_i32_b32"}},
        {S_FLBIT_I32_B64, {S_FLBIT_I32_B64, "s_flbit_i32_b64"}},
        {S_FLBIT_I32, {S_FLBIT_I32, "s_flbit_i32"}},
        {S_FLBIT_I32_I64, {S_FLBIT_I32_I64, "s_flbit_i32_i64"}},
        {S_GETPC_B64, {S_GETPC_B64, "s_getpc_b64"}},
        {S_MOV_B32, {S_MOV_B32, "s_mov_b32"}},
        {S_MOV_B64, {S_MOV_B64, "s_mov_b64"}},
        {S_MOVRELD_B32, {S_MOVRELD_B32, "s_movreld_b32"}},
        {S_MOVRELD_B64, {S_MOVRELD_B64, "s_movreld_b64"}},
        {S_MOVRELS_B32, {S_MOVRELS_B32, "s_movrels_b32"}},
        {S_MOVRELS_B64, {S_MOVRELS_B64, "s_movrels_b64"}},
        {S_NAND_SAVEEXEC_B64, {S_NAND_SAVEEXEC_B64, "s_nand_saveexec_b64"}},
        {S_NOR_SAVEEXEC_B64, {S_NOR_SAVEEXEC_B64, "s_nor_saveexec_b64"}},
        {S_NOT_B32, {S_NOT_B32, "s_not_b32"}},
        {S_NOT_B64, {S_NOT_B64, "s_not_b64"}},
        {S_OR_SAVEEXEC_B64, {S_OR_SAVEEXEC_B64, "s_or_saveexec_b64"}},
        {S_ORN2_SAVEEXEC_B64, {S_ORN2_SAVEEXEC_B64, "s_orn2_saveexec_b64"}},
        {S_QUADMASK_B32, {S_QUADMASK_B32, "s_quadmask_b32"}},
        {S_QUADMASK_B64, {S_QUADMASK_B64, "s_quadmask_b64"}},
        {S_RFE_B64, {S_RFE_B64, "s_rfe_b64"}},
        {S_SET_GPR_IDX_IDX, {S_SET_GPR_IDX_IDX, "s_set_gpr_idx_idx"}},
        {S_SETPC_B64, {S_SETPC_B64, "s_setpc_b64"}},
        {S_SEXT_I32_I8, {S_SEXT_I32_I8, "s_sext_i32_i8"}},
        {S_SEXT_I32_I16, {S_SEXT_I32_I16, "s_sext_i32_i16"}},
        {S_SWAPPC_B64, {S_SWAPPC_B64, "s_swappc_b64"}},
        {S_WQM_B32, {S_WQM_B32, "s_wqm_b32"}},
        {S_WQM_B64, {S_WQM_B64, "s_wqm_b64"}},
        {S_XNOR_SAVEEXEC_B64, {S_XNOR_SAVEEXEC_B64, "s_xnor_saveexec_b64"}},
        {S_XOR_SAVEEXEC_B64, {S_XOR_SAVEEXEC_B64, "s_xor_saveexec_b64"}},

        // SOP2
        {S_ABSDIFF_I32, {S_ABSDIFF_I32, "s_absdiff_i32"}},
        {S_ADDC_U32, {S_ADDC_U32, "s_addc_u32"}},
        {S_ADD_I32, {S_ADD_I32, "s_add_i32"}},
        {S_ADD_U32, {S_ADD_U32, "s_add_u32"}},
        {S_AND_B32, {S_AND_B32, "s_and_b32"}},
        {S_AND_B64, {S_AND_B64, "s_and_b64"}},
        {S_ANDN2_B32, {S_ANDN2_B32, "s_andn2_b32"}},
        {S_ANDN2_B64, {S_ANDN2_B64, "s_andn2_b64"}},
        {S_ASHR_I32, {S_ASHR_I32, "s_ashr_i32"}},
        {S_ASHR_I64, {S_ASHR_I64, "s_ashr_i64"}},
        {S_BFE_I32, {S_BFE_I32, "s_bfe_i32"}},
        {S_BFE_I64, {S_BFE_I64, "s_bfe_i64"}},
        {S_BFE_U32, {S_BFE_U32, "s_bfe_u32"}},
        {S_BFE_U64, {S_BFE_U64, "s_bfe_u64"}},
        {S_BFM_B32, {S_BFM_B32, "s_bfm_b32"}},
        {S_BFM_B64, {S_BFM_B64, "s_bfm_b64"}},
        {S_CBRANCH_G_FORK, {S_CBRANCH_G_FORK, "s_cbranch_g_fork"}},
        {S_CSELECT_B32, {S_CSELECT_B32, "s_cselect_b32"}},
        {S_CSELECT_B64, {S_CSELECT_B64, "s_cselect_b64"}},
        {S_LSHL_B32, {S_LSHL_B32, "s_lshl_b32"}},
        {S_LSHL_B64, {S_LSHL_B64, "s_lshl_b64"}},
        {S_LSHL1_ADD_U32, {S_LSHL1_ADD_U32, "s_lshl1_add_u32"}},
        {S_LSHL2_ADD_U32, {S_LSHL2_ADD_U32, "s_lshl2_add_u32"}},
        {S_LSHL3_ADD_U32, {S_LSHL3_ADD_U32, "s_lshl3_add_u32"}},
        {S_LSHL4_ADD_U32, {S_LSHL4_ADD_U32, "s_lshl4_add_u32"}},
        {S_LSHR_B32, {S_LSHR_B32, "s_lshr_b32"}},
        {S_LSHR_B64, {S_LSHR_B64, "s_lshr_b64"}},
        {S_MAX_I32, {S_MAX_I32, "s_max_i32"}},
        {S_MAX_U32, {S_MAX_U32, "s_max_u32"}},
        {S_MIN_I32, {S_MIN_I32, "s_min_i32"}},
        {S_MIN_U32, {S_MIN_U32, "s_min_u32"}},
        {S_MUL_HI_I32, {S_MUL_HI_I32, "s_mul_hi_i32"}},
        {S_MUL_HI_U32, {S_MUL_HI_U32, "s_mul_hi_u32"}},
        {S_MUL_I32, {S_MUL_I32, "s_mul_i32"}},
        {S_NAND_B32, {S_NAND_B32, "s_nand_b32"}},
        {S_NAND_B64, {S_NAND_B64, "s_nand_b64"}},
        {S_NOR_B32, {S_NOR_B32, "s_nor_b32"}},
        {S_NOR_B64, {S_NOR_B64, "s_nor_b64"}},
        {S_OR_B32, {S_OR_B32, "s_or_b32"}},
        {S_OR_B64, {S_OR_B64, "s_or_b64"}},
        {S_ORN2_B32, {S_ORN2_B32, "s_orn2_b32"}},
        {S_ORN2_B64, {S_ORN2_B64, "s_orn2_b64"}},
        {S_PACK_HH_B32_B16, {S_PACK_HH_B32_B16, "s_pack_hh_b32_b16"}},
        {S_PACK_LH_B32_B16, {S_PACK_LH_B32_B16, "s_pack_lh_b32_b16"}},
        {S_PACK_LL_B32_B16, {S_PACK_LL_B32_B16, "s_pack_ll_b32_b16"}},
        {S_RFE_RESTORE_B64, {S_RFE_RESTORE_B64, "s_rfe_restore_b64"}},
        {S_SUBB_U32, {S_SUBB_U32, "s_subb_u32"}},
        {S_SUB_I32, {S_SUB_I32, "s_sub_i32"}},
        {S_SUB_U32, {S_SUB_U32, "s_sub_u32"}},
        {S_XNOR_B32, {S_XNOR_B32, "s_xnor_b32"}},
        {S_XNOR_B64, {S_XNOR_B64, "s_xnor_b64"}},
        {S_XOR_B32, {S_XOR_B32, "s_xor_b32"}},
        {S_XOR_B64, {S_XOR_B64, "s_xor_b64"}},

        // SOPK
        {S_ADDK_I32, {S_ADDK_I32, "s_addk_i32"}},
        {S_CALL_B64, {S_CALL_B64, "s_call_b64"}},
        {S_CBRANCH_I_FORK, {S_CBRANCH_I_FORK, "s_cbranch_i_fork"}},
        {S_CMOVK_I32, {S_CMOVK_I32, "s_cmovk_i32"}},
        {S_CMPK_EQ_I32, {S_CMPK_EQ_I32, "s_cmpk_eq_i32"}},
        {S_CMPK_EQ_U32, {S_CMPK_EQ_U32, "s_cmpk_eq_u32"}},
        {S_CMPK_GE_I32, {S_CMPK_GE_I32, "s_cmpk_ge_i32"}},
        {S_CMPK_GE_U32, {S_CMPK_GE_U32, "s_cmpk_ge_u32"}},
        {S_CMPK_GT_I32, {S_CMPK_GT_I32, "s_cmpk_gt_i32"}},
        {S_CMPK_GT_U32, {S_CMPK_GT_U32, "s_cmpk_gt_u32"}},
        {S_CMPK_LE_I32, {S_CMPK_LE_I32, "s_cmpk_le_i32"}},
        {S_CMPK_LE_U32, {S_CMPK_LE_U32, "s_cmpk_le_u32"}},
        {S_CMPK_LG_I32, {S_CMPK_LG_I32, "s_cmpk_lg_i32"}},
        {S_CMPK_LG_U32, {S_CMPK_LG_U32, "s_cmpk_lg_u32"}},
        {S_CMPK_LT_I32, {S_CMPK_LT_I32, "s_cmpk_lt_i32"}},
        {S_CMPK_LT_U32, {S_CMPK_LT_U32, "s_cmpk_lt_u32"}},
        {S_GETREG_B32, {S_GETREG_B32, "s_getreg_b32"}},
        {S_GETREG_REGRD_B32, {S_GETREG_REGRD_B32, "s_getreg_regrd_b32"}},
        {S_MOVK_I32, {S_MOVK_I32, "s_movk_i32"}},
        {S_MULK_I32, {S_MULK_I32, "s_mulk_i32"}},
        {S_SETREG_B32, {S_SETREG_B32, "s_setreg_b32"}},
        {S_SETREG_IMM32_B32, {S_SETREG_IMM32_B32, "s_setreg_imm32_b32"}},

        // SMEM
        {S_LOAD_DWORD, {S_LOAD_DWORD, "s_load_dword"}},
        {S_LOAD_DWORDX2, {S_LOAD_DWORDX2, "s_load_dwordx2"}},

        // SOPC
        {S_BITCMP0_B32, {S_BITCMP0_B32, "s_bitcmp0_b32"}},
        {S_BITCMP0_B64, {S_BITCMP0_B64, "s_bitcmp0_b64"}},
        {S_BITCMP1_B32, {S_BITCMP1_B32, "s_bitcmp1_b32"}},
        {S_BITCMP1_B64, {S_BITCMP1_B64, "s_bitcmp1_b64"}},
        {S_CMP_EQ_I32, {S_CMP_EQ_I32, "s_cmp_eq_i32"}},
        {S_CMP_EQ_U32, {S_CMP_EQ_U32, "s_cmp_eq_u32"}},
        {S_CMP_EQ_U64, {S_CMP_EQ_U64, "s_cmp_eq_u64"}},
        {S_CMP_GE_I32, {S_CMP_GE_I32, "s_cmp_ge_i32"}},
        {S_CMP_GE_U32, {S_CMP_GE_U32, "s_cmp_ge_u32"}},
        {S_CMP_GT_I32, {S_CMP_GT_I32, "s_cmp_gt_i32"}},
        {S_CMP_GT_U32, {S_CMP_GT_U32, "s_cmp_gt_u32"}},
        {S_CMP_LE_I32, {S_CMP_LE_I32, "s_cmp_le_i32"}},
        {S_CMP_LE_U32, {S_CMP_LE_U32, "s_cmp_le_u32"}},
        {S_CMP_LG_I32, {S_CMP_LG_I32, "s_cmp_lg_i32"}},
        {S_CMP_LG_U32, {S_CMP_LG_U32, "s_cmp_lg_u32"}},
        {S_CMP_LG_U64, {S_CMP_LG_U64, "s_cmp_lg_u64"}},
        {S_CMP_NE_U64, {S_CMP_NE_U64, "s_cmp_ne_u64"}},
        {S_CMP_LT_I32, {S_CMP_LT_I32, "s_cmp_lt_i32"}},
        {S_CMP_LT_U32, {S_CMP_LT_U32, "s_cmp_lt_u32"}},
        {S_SET_GPR_IDX_ON, {S_SET_GPR_IDX_ON, "s_set_gpr_idx_on"}},
        {S_SETVSKIP, {S_SETVSKIP, "s_setvskip"}},

        // SOPP
        {S_BARRIER, {S_BARRIER, "s_barrier"}},
        {S_BRANCH, {S_BRANCH, "s_branch"}},
        {S_CBRANCH_CDBGSYS, {S_CBRANCH_CDBGSYS, "s_cbranch_cdbgsys"}},
        {S_CBRANCH_CDBGSYS_AND_USER, {S_CBRANCH_CDBGSYS_AND_USER, "s_cbranch_cdbgsys_and_user"}},
        {S_CBRANCH_CDBGSYS_OR_USER, {S_CBRANCH_CDBGSYS_OR_USER, "s_cbranch_cdbgsys_or_user"}},
        {S_CBRANCH_CDBGUSER, {S_CBRANCH_CDBGUSER, "s_cbranch_cdbguser"}},
        {S_CBRANCH_EXECNZ, {S_CBRANCH_EXECNZ, "s_cbranch_execnz"}},
        {S_CBRANCH_EXECZ, {S_CBRANCH_EXECZ, "s_cbranch_execz"}},
        {S_CBRANCH_SCC0, {S_CBRANCH_SCC0, "s_cbranch_scc0"}},
        {S_CBRANCH_SCC1, {S_CBRANCH_SCC1, "s_cbranch_scc1"}},
        {S_CBRANCH_VCCNZ, {S_CBRANCH_VCCNZ, "s_cbranch_vccnz"}},
        {S_CBRANCH_VCCZ, {S_CBRANCH_VCCZ, "s_cbranch_vccz"}},
        {S_DECPERFLEVEL, {S_DECPERFLEVEL, "s_decperflevel"}},
        {S_ENDPGM, {S_ENDPGM, "s_endpgm"}},
        {S_ENDPGM_ORDERED_PS_DONE, {S_ENDPGM_ORDERED_PS_DONE, "s_endpgm_ordered_ps_done"}},
        {S_ENDPGM_SAVED, {S_ENDPGM_SAVED, "s_endpgm_saved"}},
        {S_ICACHE_INV, {S_ICACHE_INV, "s_icache_inv"}},
        {S_INCPERFLEVEL, {S_INCPERFLEVEL, "s_incperflevel"}},
        {S_NOP, {S_NOP, "s_nop"}},
        {S_SENDMSG, {S_SENDMSG, "s_sendmsg"}},
        {S_SENDMSGHALT, {S_SENDMSGHALT, "s_sendmsghalt"}},
        {S_SET_GPR_IDX_MODE, {S_SET_GPR_IDX_MODE, "s_set_gpr_idx_mode"}},
        {S_SET_GPR_IDX_OFF, {S_SET_GPR_IDX_OFF, "s_set_gpr_idx_off"}},
        {S_SETHALT, {S_SETHALT, "s_sethalt"}},
        {S_SETKILL, {S_SETKILL, "s_setkill"}},
        {S_SETPRIO, {S_SETPRIO, "s_setprio"}},
        {S_SLEEP, {S_SLEEP, "s_sleep"}},
        {S_TRAP, {S_TRAP, "s_trap"}},
        {S_TTRACEDATA, {S_TTRACEDATA, "s_ttracedata"}},
        {S_WAITCNT, {S_WAITCNT, "s_waitcnt"}},

        // VOP1
        {V_MOV_B32, {V_MOV_B32, "v_mov_b32"}},

        // VOP2
        {V_ADD_U32, {V_ADD_U32, "v_add_u32"}},
        {V_ADDC_U32, {V_ADDC_U32, "v_addc_u32"}},

        // VOP3A
        {V_LSHLREV_B64, {V_LSHLREV_B64, "v_lshlrev_b64"}},

        // VOPC
        {V_CMP_EQ_I32, {V_CMP_EQ_I32, "v_cmp_eq_i32"}},

        // FLAT
        {FLAT_STORE_DWORD, {FLAT_STORE_DWORD, "flat_store_dword"}}};

    auto it = instruction_repo.find(instruction);

    if (it == instruction_repo.end()) {
        throw std::runtime_error("Undefined instruction!");
    }

    return it->second;
}