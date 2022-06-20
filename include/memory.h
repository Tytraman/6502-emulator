#ifndef __6502_MEMORY_H__
#define __6502_MEMORY_H__

#include <types.h>

class Memory {

    public:
        unsigned int max;
        byte *data;

        Memory(const Memory &) = delete;
        Memory(const Memory &&) = delete;

        Memory(unsigned int max);
        ~Memory();

        void init();

        void printPage(byte page) const;
        void printStack() const;

};

#endif