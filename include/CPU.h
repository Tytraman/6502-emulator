#ifndef __6502_CPU_H__
#define __6502_CPU_H__

#include <types.h>
#include <memory.h>

class CPU {

    public:
        typedef union {
            byte all;
            struct {
                byte n : 1;
                byte v : 1;
                byte u : 1;
                byte b : 1;
                byte d : 1;
                byte i : 1;
                byte z : 1;
                byte c : 1;
            } bits;
        } Flags;

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
        word pc;    // Program counter (Emplacement de la prochaine instruction à exécuter)
        byte sp;    // Stack pointer (Emplacement de la dernière valeur dans la pile)

        byte acc;   // Accumulateur
        byte x, y;  // Registres

        Flags flags;

        Memory mem;

    public:
        CPU(unsigned int maxMemoryCapacity);

        void reset();

        void execute(byte cycles);
        byte fetchByte(byte &cycles);
        word fetchWord(byte &cycles);

        byte readByte(byte &cycles, word address);
        word readWord(byte &cycles, word address);

        void writeStackByte(byte &cycles, byte value);
        void writeStackWord(byte &cycles, word value);

        byte negate(byte value) const;

        void setStatusLDA();
        void setStatusADC(byte toAdd, word result);
        void setStatusSBC(byte toAdd, word result);

        void printData() const;
};

#endif