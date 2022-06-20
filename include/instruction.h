#ifndef __6502_INSTRUCTION_H__
#define __6502_INSTRUCTION_H__

#include <types.h>

class Instruction {

    public:
        // LDA
        static constexpr byte LDA_IM       = 0xA9;  // 2 cycles
        static constexpr byte LDA_ZP       = 0xA5;  // 3 cycles
        static constexpr byte LDA_ZP_X     = 0xB5;  // 4 cycles
        static constexpr byte LDA_ZP_X_IND = 0xA1;  // 6 cycles
        static constexpr byte LDA_ABS      = 0xAD;  // 4 cycles

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

    public:
        const char *name;
        const byte cycles;

        Instruction(const Instruction &) = delete;
        Instruction(const Instruction &&) = delete;
        Instruction(const char *name, byte cycles);
};

#endif