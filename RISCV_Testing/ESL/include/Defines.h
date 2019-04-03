#ifndef PROJECT_DEFINES_H
#define PROJECT_DEFINES_H

/// Addressing
#define MEM_DEPTH       0x40000 // 1024*1024*32 // 32 MB ram
#define MEM_START_ADDR  0x00000000
#define MEM_END_ADDR    MEM_START_ADDR + MEM_DEPTH

#define CLINT_START_ADDR    0x02000000
#define CLINT_END_ADDR      0x0200ffff
    #define CLINT_msip_ADDR     0x02000000
    #define CLINT_mtimecmp_ADDR 0x02004000
    #define CLINT_mtime_ADDR    0x0200BFF8

#define PLIC_START_ADDR     0x0C000000
#define PLIC_END_ADDR       0x0C200008
    #define PLIC_Priority_ADDR          0x0C000000
    #define PLIC_Pending_ADDR           0x0C001000
    #define PLIC_Interrupt_Enables_ADDR 0x0C002000
    #define PLIC_Threshold_ADDR         0x0C200000
    #define PLIC_Claim_Complete_ADDR    0x0C200004

#define CORETEMPSENSOR_START_ADDR     0x40000000
#define CORETEMPSENSOR_END_ADDR       0x40000008
    #define CORETEMPSENSOR_Tthreshold_ADDR  0x40000000
    #define CORETEMPSENSOR_Tcur_ADDR        0x40000004

/// Instructions
#define OPCODE_R    0x33 //0110011
#define OPCODE_I_I  0x13 //0010011
#define OPCODE_I_L  0x03 //0000011
#define OPCODE_I_J  0x67 //1100111
#define OPCODE_S    0x23 //0100011
#define OPCODE_B    0x63 //1100011
#define OPCODE_U1   0x37 //0110111
#define OPCODE_U2   0x17 //0010111
#define OPCODE_J    0x6F //1101111
#define OPCODE_I_M  0x0F //0001111
#define OPCODE_I_S  0x73 //1110011

#define OPCODE_FIELD(x) ((x) & 0x7F)
#define FUNCT3_FIELD(x) (((x) >> 12) & 0x07)
#define FUNCT7_FIELD(x) (((x) >> 25) & 0x7F)
#define RS1_FIELD(x)    (((x) >> 15) & 0x1F)
#define RS2_FIELD(x)    (((x) >> 20) & 0x1F)
#define RD_FIELD(x)     (((x) >>  7) & 0x1F)
#define SIGN_FIELD(x)   (((x) >> 31) & 0x01)

#define POS_IMM_I_FIELD(x)  ((x) >> 20)
#define POS_IMM_S_FIELD(x)  ((((x) >> 20) & 0xFE0) | (((x) >> 7) & 0x1F))
#define POS_IMM_B_FIELD(x)  ((((x) << 4) & 0x800) | (((x) >> 20) & 0x7E0) | (((x) >> 7) & 0x1E))
#define POS_IMM_J_FIELD(x)  (((x) & 0xFF000) | (((x) >> 9) & 0x800) | (((x) >> 20) & 0x7FE))
#define NEG_IMM_I_FIELD(x)  (static_cast<unsigned int>(0xFFFFF000) | POS_IMM_I_FIELD(x))
#define NEG_IMM_S_FIELD(x)  (static_cast<unsigned int>(0xFFFFF000) | POS_IMM_S_FIELD(x))
#define NEG_IMM_B_FIELD(x)  (static_cast<unsigned int>(0xFFFFF000) | POS_IMM_B_FIELD(x))
#define NEG_IMM_J_FIELD(x)  (static_cast<unsigned int>(0xFFF00000) | POS_IMM_J_FIELD(x))
#define IMM_U_FIELD(x)      ((x) & static_cast<unsigned int>(0xFFFFF000))

enum InstrType {
    INSTR_UNKNOWN,
    INSTR_ADD, INSTR_SUB, INSTR_SLL, INSTR_SLT, INSTR_SLTU, INSTR_XOR, INSTR_SRL, INSTR_SRA, INSTR_OR, INSTR_AND,   // R format
    INSTR_ADDI, INSTR_SLLI, INSTR_SLTI, INSTR_SLTUI, INSTR_XORI, INSTR_SRLI, INSTR_SRAI, INSTR_ORI, INSTR_ANDI,     // I format (I_I)
    INSTR_LB, INSTR_LH, INSTR_LW, INSTR_LBU, INSTR_LHU,                                                             // I format (I_L)
    INSTR_JALR,                                                                                                     // I format (I_J)
    INSTR_FENCE, INSTR_FENCEI,                                                                                      // I format (I_M)
    INSTR_PRIV, INSTR_CSRRW, INSTR_CSRRS, INSTR_CSRRC, INSTR_CSRRWI, INSTR_CSRRSI, INSTR_CSRRCI,                    // I format (I_S)
    INSTR_SB, INSTR_SH, INSTR_SW,                                                                                   // S format
    INSTR_BEQ, INSTR_BNE, INSTR_BLT, INSTR_BGE, INSTR_BLTU, INSTR_BGEU,                                             // B format
    INSTR_LUI, INSTR_AUIPC,                                                                                         // U format
    INSTR_JAL                                                                                                       // J format
};


enum PrivInstrType {
    INSTR_PRIV_UNKNOWN,
    INSTR_ECALL, INSTR_EBREAK, INSTR_MRET//, INSTR_WFI, INSTR_SFENCEVMA //, URET, SRET
};

enum EncType {
    ENC_R, ENC_I_I, ENC_I_L, ENC_I_J, ENC_I_M, ENC_I_S, ENC_S, ENC_B, ENC_U, ENC_J, ENC_ERR
};

enum ALUfuncType {
    ALU_X, ALU_ADD, ALU_SUB, ALU_SLL, ALU_SRL, ALU_SRA, ALU_AND, ALU_OR, ALU_XOR, ALU_SLT, ALU_SLTU, ALU_COPY1
};


// register file input interface
struct RegfileWriteType {
    unsigned int dst;
    unsigned int dstData;
};

// register file output interface
struct RegfileType {
    unsigned int reg_file_01;
    unsigned int reg_file_02;
    unsigned int reg_file_03;
    unsigned int reg_file_04;
    unsigned int reg_file_05;
    unsigned int reg_file_06;
    unsigned int reg_file_07;
    unsigned int reg_file_08;
    unsigned int reg_file_09;
    unsigned int reg_file_10;
    unsigned int reg_file_11;
    unsigned int reg_file_12;
    unsigned int reg_file_13;
    unsigned int reg_file_14;
    unsigned int reg_file_15;
    unsigned int reg_file_16;
    unsigned int reg_file_17;
    unsigned int reg_file_18;
    unsigned int reg_file_19;
    unsigned int reg_file_20;
    unsigned int reg_file_21;
    unsigned int reg_file_22;
    unsigned int reg_file_23;
    unsigned int reg_file_24;
    unsigned int reg_file_25;
    unsigned int reg_file_26;
    unsigned int reg_file_27;
    unsigned int reg_file_28;
    unsigned int reg_file_29;
    unsigned int reg_file_30;
    unsigned int reg_file_31;
};

// register file output interface
struct RegfileEcallType {
    unsigned int reg_file_10;
    unsigned int reg_file_11;
    unsigned int reg_file_12;
    unsigned int reg_file_17;
};

struct CSRfileType {
    unsigned int mstatus;
//    unsigned int misa;
    unsigned int mie;
    unsigned int mtvec;
//    unsigned int mscratch;
    unsigned int mepc;
    unsigned int mcause;
//    unsigned int mtval;
    unsigned int mip;
//    unsigned int mvendorid;
//    unsigned int marchid;
//    unsigned int mimpid;
//    unsigned int mhartid;
};

#endif // PROJECT_DEFINES_H