#ifndef __6502_CPU_H__
#define __6502_CPU_H__

#include <types.h>
#include <memory.h>
#include <instruction.h>

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
        word pc;    // Program counter (Emplacement de la prochaine instruction à exécuter)
        byte sp;    // Stack pointer (Emplacement de la dernière valeur dans la pile)

        byte acc;   // Accumulateur
        byte x, y;  // Registres

        Flags flags;

        Memory mem;

        Instruction *instructions;
        byte instruction;
        byte cycles;

    public:
        CPU(unsigned int maxMemoryCapacity, Instruction instructions[256]);

        void reset();

        bool execute();
        byte fetchByte();
        word fetchWord();

        byte readByte(word address);
        word readWord(word address);

        void writeByte(word address, byte value);
        void writeWord(word address, word value);

        byte readStackByte();
        word readStackWord();

        void writeStackByte(byte value);
        void writeStackWord(word value);

        byte negate(byte value) const;

        void setStatusLDA();
        void setStatusLDX();
        void setStatusLDY();
        void setStatusADC(byte toAdd, word result);
        void setStatusSBC(byte toAdd, word result);

        void printData() const;
};

#endif