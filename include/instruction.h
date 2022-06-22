#ifndef __6502_INSTRUCTION_H__
#define __6502_INSTRUCTION_H__

#include <types.h>

class Instruction {

    public:
        // LDA
        static constexpr byte LDA_IMM          = 0xA9;      // 2 cycles
        static constexpr byte LDA_ZP           = 0xA5;      // 3 cycles
        static constexpr byte LDA_ZP_X         = 0xB5;      // 4 cycles
        static constexpr byte LDA_ZP_X_IND     = 0xA1;      // 6 cycles
        static constexpr byte LDA_ZP_IND_Y_IDX = 0xB1;      // 5+p cycles
        static constexpr byte LDA_ABS          = 0xAD;      // 4 cycles
        static constexpr byte LDA_ABS_X        = 0xBD;      // 4+p cycles
        static constexpr byte LDA_ABS_Y        = 0xB9;      // 4+p cycles

        // LDX
        static constexpr byte LDX_IMM   = 0xA2;     // 2 cycles
        static constexpr byte LDX_ZP    = 0xA6;     // 3 cycles
        static constexpr byte LDX_ZP_Y  = 0xB6;     // 4 cycles
        static constexpr byte LDX_ABS   = 0xAE;     // 4 cycles
        static constexpr byte LDX_ABS_Y = 0xBE;     // 4+p cycles

        // LDY
        static constexpr byte LDY_IMM   = 0xA0;     // 2 cycles
        static constexpr byte LDY_ZP    = 0xA4;     // 3 cycles
        static constexpr byte LDY_ZP_X  = 0xB4;     // 4 cycles
        static constexpr byte LDY_ABS   = 0xAC;     // 4 cycles
        static constexpr byte LDY_ABS_X = 0xBC;     // 4+p cycles

        // STA
        static constexpr byte STA_ZP           = 0x85;      // 3 cycles
        static constexpr byte STA_ZP_X         = 0x95;      // 4 cycles
        static constexpr byte STA_ABS          = 0x8D;      // 4 cycles
        static constexpr byte STA_ABS_X        = 0x9D;      // 5 cycles
        static constexpr byte STA_ABS_Y        = 0x99;      // 5 cycles
        static constexpr byte STA_ZP_X_IND     = 0x81;      // 6 cycles
        static constexpr byte STA_ZP_IND_Y_IDX = 0x91;      // 6 cycles

        // STX
        static constexpr byte STX_ZP   = 0x86;      // 3 cycles
        static constexpr byte STX_ZP_Y = 0x96;      // 4 cycles
        static constexpr byte STX_ABS  = 0x8E;      // 4 cycles

        // STY
        static constexpr byte STY_ZP   = 0x84;      // 3 cycles
        static constexpr byte STY_ZP_X = 0x94;      // 4 cycles
        static constexpr byte STY_ABS  = 0x8C;      // 4 cycles

        // JUMP
        static constexpr byte JMP_ABS = 0x4C;       // 3 cycles
        static constexpr byte JMP_ABS_IND = 0x6C;   // 5 cycles
        static constexpr byte JSR = 0x20;           // 6 cycles

        // Add Memory to Accumulator with Carry
        static constexpr byte ADC_IM = 0x69;    // 2 cycles

        // Substract Memory from Accumulator with Borrow
        static constexpr byte SBC_IM = 0xE9;    // 2 cycles

        // Decimal Flag
        static constexpr byte CLD = 0xD8;   // 2 cycles
        static constexpr byte SED = 0xF8;   // 2 cycles

        // Interrupt Flag
        static constexpr byte CLI = 0x58;   // 2 cycles
        static constexpr byte SEI = 0x78;   // 2 cycles

        // Carry Flag
        static constexpr byte CLC = 0x18;   // 2 cycles
        static constexpr byte SEC = 0x38;   // 2 cycles

        // Overflow Flag
        static constexpr byte CLV = 0xB8;   // 2 cycles

        static constexpr byte RTS = 0x60;   // 6 cycles

    public:
        const char *name;
        const byte cycles;

        Instruction(const Instruction &) = delete;
        Instruction(const Instruction &&) = delete;
        Instruction(const char *name, byte cycles);
};

#endif