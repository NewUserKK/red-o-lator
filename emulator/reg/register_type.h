/**
 * @author dkudaiberdieva
 */

enum RegisterType {
    /**
     * Points to the memory address of the next shader instruction to
     * execute.
     */
    PC,

    /**
     * S0-S103 - Scalar general-purpose register
     */
    S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15, S16, S17, S18, S19, S20, S21, S22, S23, S24, S25, S26, S27, S28, S29, S30, S31, S32, S33, S34, S35, S36, S37, S38, S39, S40, S41, S42, S43, S44, S45, S46, S47, S48, S49, S50, S51, S52, S53, S54, S55, S56, S57, S58, S59, S60, S61, S62, S63, S64, S65, S66, S67, S68, S69, S70, S71, S72, S73, S74, S75, S76, S77, S78, S79, S80, S81, S82, S83, S84, S85, S86, S87, S88, S89, S90, S91, S92, S93, S94, S95, S96, S97, S98, S99, S100, S101,

    /**
     *  A bit mask with one bit per thread, which is applied to vector
     * instructions and controls that threads execute and that ignore the
     * instruction.
     */
    EXEC,

    /**
     * A bit mask with one bit per thread; it holds the result of a vector
     * compare operation.
     */
    VCC,
    /**
     * The base address of scratch memory
     */
    FLAT_SCRATCH,
    /**
     * Bit mask of threads that have failed their address translation.
     */
    XNACK_MASK,
    /**
     * Read-only shader status bar
     */
    STATUS,
    /**
     * Writable shader mode bits
     */
    MODE,
    /**
     * A temporary register that has various uses, including GPR indexing and
     * bounds checking
     */
    M0,
    /**
     * Holds information about exceptions and pending traps
     */
    TRAPSTS,
    /**
     * Holds the pointer to the current trap handler program
     */
    TBA,
    /**
     * Temporary register for shader operations. For example, can hold a pointer
     * to memory used by the trap handler
     */
    TMA,

    /**
     * TTMP0-TTMP15 - Trap Temporary SGPRs. 16 SGPRs available only to the Trap
     * Handler for temporary storage.
     */
    TTMP0,
    TTMP1,
    TTMP2,
    TTMP3,
    TTMP4,
    TTMP5,
    TTMP6,
    TTMP7,
    TTMP8,
    TTMP9,
    TTMP10,
    TTMP11,
    TTMP12,
    TTMP13,
    TTMP14,
    TTMP15,

    /**
     * Counts the number of VMEM instructions issued but not yet completed
     */
    VMCNT,
    /**
     * Counts the number of Export and GDS instructions issued but not yet
     * completed. Also counts VMEM writes that have not yet sent their
     * write-data to the TC.
     */
    EXPCNT,
    /**
     * Counts the number of LDS, GDS, constant-fetch (scalar memory read), and
     * message instructions issued but not yet completed
     */
    LGKMCNT,

    /**
     * V0-V255 - Vector general-purpose register
     */
    V0,
    V1,
    V2,
    V3,
    V4,
    V5,
    V6,
    V7,
    V8,
    V9,
    V10,
    V11,
    V12,
    V13,
    V14,
    V15,
    V16,
    V17,
    V18,
    V19,
    V20,
    V21,
    V22,
    V23,
    V24,
    V25,
    V26,
    V27,
    V28,
    V29,
    V30,
    V31,
    V32,
    V33,
    V34,
    V35,
    V36,
    V37,
    V38,
    V39,
    V40,
    V41,
    V42,
    V43,
    V44,
    V45,
    V46,
    V47,
    V48,
    V49,
    V50,
    V51,
    V52,
    V53,
    V54,
    V55,
    V56,
    V57,
    V58,
    V59,
    V60,
    V61,
    V62,
    V63,
    V64,
    V65,
    V66,
    V67,
    V68,
    V69,
    V70,
    V71,
    V72,
    V73,
    V74,
    V75,
    V76,
    V77,
    V78,
    V79,
    V80,
    V81,
    V82,
    V83,
    V84,
    V85,
    V86,
    V87,
    V88,
    V89,
    V90,
    V91,
    V92,
    V93,
    V94,
    V95,
    V96,
    V97,
    V98,
    V99,
    V100,
    V101,
    V102,
    V103,
    V104,
    V105,
    V106,
    V107,
    V108,
    V109,
    V110,
    V111,
    V112,
    V113,
    V114,
    V115,
    V116,
    V117,
    V118,
    V119,
    V120,
    V121,
    V122,
    V123,
    V124,
    V125,
    V126,
    V127,
    V128,
    V129,
    V130,
    V131,
    V132,
    V133,
    V134,
    V135,
    V136,
    V137,
    V138,
    V139,
    V140,
    V141,
    V142,
    V143,
    V144,
    V145,
    V146,
    V147,
    V148,
    V149,
    V150,
    V151,
    V152,
    V153,
    V154,
    V155,
    V156,
    V157,
    V158,
    V159,
    V160,
    V161,
    V162,
    V163,
    V164,
    V165,
    V166,
    V167,
    V168,
    V169,
    V170,
    V171,
    V172,
    V173,
    V174,
    V175,
    V176,
    V177,
    V178,
    V179,
    V180,
    V181,
    V182,
    V183,
    V184,
    V185,
    V186,
    V187,
    V188,
    V189,
    V190,
    V191,
    V192,
    V193,
    V194,
    V195,
    V196,
    V197,
    V198,
    V199,
    V200,
    V201,
    V202,
    V203,
    V204,
    V205,
    V206,
    V207,
    V208,
    V209,
    V210,
    V211,
    V212,
    V213,
    V214,
    V215,
    V216,
    V217,
    V218,
    V219,
    V220,
    V221,
    V222,
    V223,
    V224,
    V225,
    V226,
    V227,
    V228,
    V229,
    V230,
    V231,
    V232,
    V233,
    V234,
    V235,
    V236,
    V237,
    V238,
    V239,
    V240,
    V241,
    V242,
    V243,
    V244,
    V245,
    V246,
    V247,
    V248,
    V249,
    V250,
    V251,
    V252,
    V253,
    V254,
    V255
};

struct RegisterTypeInfo {
    RegisterType type;

    // register size in bit
    int size = 0;

    OperandInfo operandInfo;

    RegisterTypeInfo(RegisterType type, int size) {
        this->type = type;
        this->size = size;
    }
};

RegisterTypeInfo get_register_type_info(RegisterType registerType) {
    static std::unordered_map<RegisterType, RegisterTypeInfo> registers = {
        {PC, {PC, 48}},
        {EXEC, {EXEC, 64}},
        {VCC, {VCC, 64}},
        {FLAT_SCRATCH, {FLAT_SCRATCH, 64}},
        {XNACK_MASK, {XNACK_MASK, 64}},
        {STATUS, {STATUS, 32}},
        {MODE, {MODE, 32}},
        {M0, {M0, 32}},
        {TRAPSTS, {TRAPSTS, 32}},
        {TBA, {TBA, 64}},
        {TMA, {TMA, 64}},
        {TTMP0, {TTMP0, 32}},
        {TTMP1, {TTMP1, 32}},
        {TTMP2, {TTMP2, 32}},
        {TTMP3, {TTMP3, 32}},
        {TTMP4, {TTMP4, 32}},
        {TTMP5, {TTMP5, 32}},
        {TTMP6, {TTMP6, 32}},
        {TTMP7, {TTMP7, 32}},
        {TTMP8, {TTMP8, 32}},
        {TTMP9, {TTMP9, 32}},
        {TTMP10, {TTMP10, 32}},
        {TTMP11, {TTMP11, 32}},
        {TTMP12, {TTMP12, 32}},
        {TTMP13, {TTMP13, 32}},
        {TTMP14, {TTMP14, 32}},
        {TTMP15, {TTMP15, 32}},
        {VMCNT, {VMCNT, 6}},
        {EXPCNT, {EXPCNT, 3}},
        {LGKMCNT, {LGKMCNT, 4}},

        {S0, {S0, 32}},
        {S1, {S1, 32}},
        {S2, {S2, 32}},
        {S3, {S3, 32}},
        {S4, {S4, 32}},
        {S5, {S5, 32}},
        {S6, {S6, 32}},
        {S7, {S7, 32}},
        {S8, {S8, 32}},
        {S9, {S9, 32}},
        {S10, {S10, 32}},
        {S11, {S11, 32}},
        {S12, {S12, 32}},
        {S13, {S13, 32}},
        {S14, {S14, 32}},
        {S15, {S15, 32}},
        {S16, {S16, 32}},
        {S17, {S17, 32}},
        {S18, {S18, 32}},
        {S19, {S19, 32}},
        {S20, {S20, 32}},
        {S21, {S21, 32}},
        {S22, {S22, 32}},
        {S23, {S23, 32}},
        {S24, {S24, 32}},
        {S25, {S25, 32}},
        {S26, {S26, 32}},
        {S27, {S27, 32}},
        {S28, {S28, 32}},
        {S29, {S29, 32}},
        {S30, {S30, 32}},
        {S31, {S31, 32}},
        {S32, {S32, 32}},
        {S33, {S33, 32}},
        {S34, {S34, 32}},
        {S35, {S35, 32}},
        {S36, {S36, 32}},
        {S37, {S37, 32}},
        {S38, {S38, 32}},
        {S39, {S39, 32}},
        {S40, {S40, 32}},
        {S41, {S41, 32}},
        {S42, {S42, 32}},
        {S43, {S43, 32}},
        {S44, {S44, 32}},
        {S45, {S45, 32}},
        {S46, {S46, 32}},
        {S47, {S47, 32}},
        {S48, {S48, 32}},
        {S49, {S49, 32}},
        {S50, {S50, 32}},
        {S51, {S51, 32}},
        {S52, {S52, 32}},
        {S53, {S53, 32}},
        {S54, {S54, 32}},
        {S55, {S55, 32}},
        {S56, {S56, 32}},
        {S57, {S57, 32}},
        {S58, {S58, 32}},
        {S59, {S59, 32}},
        {S60, {S60, 32}},
        {S61, {S61, 32}},
        {S62, {S62, 32}},
        {S63, {S63, 32}},
        {S64, {S64, 32}},
        {S65, {S65, 32}},
        {S66, {S66, 32}},
        {S67, {S67, 32}},
        {S68, {S68, 32}},
        {S69, {S69, 32}},
        {S70, {S70, 32}},
        {S71, {S71, 32}},
        {S72, {S72, 32}},
        {S73, {S73, 32}},
        {S74, {S74, 32}},
        {S75, {S75, 32}},
        {S76, {S76, 32}},
        {S77, {S77, 32}},
        {S78, {S78, 32}},
        {S79, {S79, 32}},
        {S80, {S80, 32}},
        {S81, {S81, 32}},
        {S82, {S82, 32}},
        {S83, {S83, 32}},
        {S84, {S84, 32}},
        {S85, {S85, 32}},
        {S86, {S86, 32}},
        {S87, {S87, 32}},
        {S88, {S88, 32}},
        {S89, {S89, 32}},
        {S90, {S90, 32}},
        {S91, {S91, 32}},
        {S92, {S92, 32}},
        {S93, {S93, 32}},
        {S94, {S94, 32}},
        {S95, {S95, 32}},
        {S96, {S96, 32}},
        {S97, {S97, 32}},
        {S98, {S98, 32}},
        {S99, {S99, 32}},
        {S100, {S100, 32}},
        {S101, {S101, 32}},

        {V0, {V0, 32}},
        {V1, {V1, 32}},
        {V2, {V2, 32}},
        {V3, {V3, 32}},
        {V4, {V4, 32}},
        {V5, {V5, 32}},
        {V6, {V6, 32}},
        {V7, {V7, 32}},
        {V8, {V8, 32}},
        {V9, {V9, 32}},
        {V10, {V10, 32}},
        {V11, {V11, 32}},
        {V12, {V12, 32}},
        {V13, {V13, 32}},
        {V14, {V14, 32}},
        {V15, {V15, 32}},
        {V16, {V16, 32}},
        {V17, {V17, 32}},
        {V18, {V18, 32}},
        {V19, {V19, 32}},
        {V20, {V20, 32}},
        {V21, {V21, 32}},
        {V22, {V22, 32}},
        {V23, {V23, 32}},
        {V24, {V24, 32}},
        {V25, {V25, 32}},
        {V26, {V26, 32}},
        {V27, {V27, 32}},
        {V28, {V28, 32}},
        {V29, {V29, 32}},
        {V30, {V30, 32}},
        {V31, {V31, 32}},
        {V32, {V32, 32}},
        {V33, {V33, 32}},
        {V34, {V34, 32}},
        {V35, {V35, 32}},
        {V36, {V36, 32}},
        {V37, {V37, 32}},
        {V38, {V38, 32}},
        {V39, {V39, 32}},
        {V40, {V40, 32}},
        {V41, {V41, 32}},
        {V42, {V42, 32}},
        {V43, {V43, 32}},
        {V44, {V44, 32}},
        {V45, {V45, 32}},
        {V46, {V46, 32}},
        {V47, {V47, 32}},
        {V48, {V48, 32}},
        {V49, {V49, 32}},
        {V50, {V50, 32}},
        {V51, {V51, 32}},
        {V52, {V52, 32}},
        {V53, {V53, 32}},
        {V54, {V54, 32}},
        {V55, {V55, 32}},
        {V56, {V56, 32}},
        {V57, {V57, 32}},
        {V58, {V58, 32}},
        {V59, {V59, 32}},
        {V60, {V60, 32}},
        {V61, {V61, 32}},
        {V62, {V62, 32}},
        {V63, {V63, 32}},
        {V64, {V64, 32}},
        {V65, {V65, 32}},
        {V66, {V66, 32}},
        {V67, {V67, 32}},
        {V68, {V68, 32}},
        {V69, {V69, 32}},
        {V70, {V70, 32}},
        {V71, {V71, 32}},
        {V72, {V72, 32}},
        {V73, {V73, 32}},
        {V74, {V74, 32}},
        {V75, {V75, 32}},
        {V76, {V76, 32}},
        {V77, {V77, 32}},
        {V78, {V78, 32}},
        {V79, {V79, 32}},
        {V80, {V80, 32}},
        {V81, {V81, 32}},
        {V82, {V82, 32}},
        {V83, {V83, 32}},
        {V84, {V84, 32}},
        {V85, {V85, 32}},
        {V86, {V86, 32}},
        {V87, {V87, 32}},
        {V88, {V88, 32}},
        {V89, {V89, 32}},
        {V90, {V90, 32}},
        {V91, {V91, 32}},
        {V92, {V92, 32}},
        {V93, {V93, 32}},
        {V94, {V94, 32}},
        {V95, {V95, 32}},
        {V96, {V96, 32}},
        {V97, {V97, 32}},
        {V98, {V98, 32}},
        {V99, {V99, 32}},
        {V100, {V100, 32}},
        {V101, {V101, 32}},
        {V102, {V102, 32}},
        {V103, {V103, 32}},
        {V104, {V104, 32}},
        {V105, {V105, 32}},
        {V106, {V106, 32}},
        {V107, {V107, 32}},
        {V108, {V108, 32}},
        {V109, {V109, 32}},
        {V110, {V110, 32}},
        {V111, {V111, 32}},
        {V112, {V112, 32}},
        {V113, {V113, 32}},
        {V114, {V114, 32}},
        {V115, {V115, 32}},
        {V116, {V116, 32}},
        {V117, {V117, 32}},
        {V118, {V118, 32}},
        {V119, {V119, 32}},
        {V120, {V120, 32}},
        {V121, {V121, 32}},
        {V122, {V122, 32}},
        {V123, {V123, 32}},
        {V124, {V124, 32}},
        {V125, {V125, 32}},
        {V126, {V126, 32}},
        {V127, {V127, 32}},
        {V128, {V128, 32}},
        {V129, {V129, 32}},
        {V130, {V130, 32}},
        {V131, {V131, 32}},
        {V132, {V132, 32}},
        {V133, {V133, 32}},
        {V134, {V134, 32}},
        {V135, {V135, 32}},
        {V136, {V136, 32}},
        {V137, {V137, 32}},
        {V138, {V138, 32}},
        {V139, {V139, 32}},
        {V140, {V140, 32}},
        {V141, {V141, 32}},
        {V142, {V142, 32}},
        {V143, {V143, 32}},
        {V144, {V144, 32}},
        {V145, {V145, 32}},
        {V146, {V146, 32}},
        {V147, {V147, 32}},
        {V148, {V148, 32}},
        {V149, {V149, 32}},
        {V150, {V150, 32}},
        {V151, {V151, 32}},
        {V152, {V152, 32}},
        {V153, {V153, 32}},
        {V154, {V154, 32}},
        {V155, {V155, 32}},
        {V156, {V156, 32}},
        {V157, {V157, 32}},
        {V158, {V158, 32}},
        {V159, {V159, 32}},
        {V160, {V160, 32}},
        {V161, {V161, 32}},
        {V162, {V162, 32}},
        {V163, {V163, 32}},
        {V164, {V164, 32}},
        {V165, {V165, 32}},
        {V166, {V166, 32}},
        {V167, {V167, 32}},
        {V168, {V168, 32}},
        {V169, {V169, 32}},
        {V170, {V170, 32}},
        {V171, {V171, 32}},
        {V172, {V172, 32}},
        {V173, {V173, 32}},
        {V174, {V174, 32}},
        {V175, {V175, 32}},
        {V176, {V176, 32}},
        {V177, {V177, 32}},
        {V178, {V178, 32}},
        {V179, {V179, 32}},
        {V180, {V180, 32}},
        {V181, {V181, 32}},
        {V182, {V182, 32}},
        {V183, {V183, 32}},
        {V184, {V184, 32}},
        {V185, {V185, 32}},
        {V186, {V186, 32}},
        {V187, {V187, 32}},
        {V188, {V188, 32}},
        {V189, {V189, 32}},
        {V190, {V190, 32}},
        {V191, {V191, 32}},
        {V192, {V192, 32}},
        {V193, {V193, 32}},
        {V194, {V194, 32}},
        {V195, {V195, 32}},
        {V196, {V196, 32}},
        {V197, {V197, 32}},
        {V198, {V198, 32}},
        {V199, {V199, 32}},
        {V200, {V200, 32}},
        {V201, {V201, 32}},
        {V202, {V202, 32}},
        {V203, {V203, 32}},
        {V204, {V204, 32}},
        {V205, {V205, 32}},
        {V206, {V206, 32}},
        {V207, {V207, 32}},
        {V208, {V208, 32}},
        {V209, {V209, 32}},
        {V210, {V210, 32}},
        {V211, {V211, 32}},
        {V212, {V212, 32}},
        {V213, {V213, 32}},
        {V214, {V214, 32}},
        {V215, {V215, 32}},
        {V216, {V216, 32}},
        {V217, {V217, 32}},
        {V218, {V218, 32}},
        {V219, {V219, 32}},
        {V220, {V220, 32}},
        {V221, {V221, 32}},
        {V222, {V222, 32}},
        {V223, {V223, 32}},
        {V224, {V224, 32}},
        {V225, {V225, 32}},
        {V226, {V226, 32}},
        {V227, {V227, 32}},
        {V228, {V228, 32}},
        {V229, {V229, 32}},
        {V230, {V230, 32}},
        {V231, {V231, 32}},
        {V232, {V232, 32}},
        {V233, {V233, 32}},
        {V234, {V234, 32}},
        {V235, {V235, 32}},
        {V236, {V236, 32}},
        {V237, {V237, 32}},
        {V238, {V238, 32}},
        {V239, {V239, 32}},
        {V240, {V240, 32}},
        {V241, {V241, 32}},
        {V242, {V242, 32}},
        {V243, {V243, 32}},
        {V244, {V244, 32}},
        {V245, {V245, 32}},
        {V246, {V246, 32}},
        {V247, {V247, 32}},
        {V248, {V248, 32}},
        {V249, {V249, 32}},
        {V250, {V250, 32}},
        {V251, {V251, 32}},
        {V252, {V252, 32}},
        {V253, {V253, 32}},
        {V254, {V254, 32}},
        {V255, {V255, 32}}};

    auto it = registers.find(registerType);

    if (it == registers.end()) {
        throw std::runtime_error("Undefined register type");
    }

    return it->second;
}
