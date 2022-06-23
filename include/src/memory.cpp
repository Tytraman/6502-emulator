#include <memory.h>

#include <string.h>
#include <stdio.h>


Memory::Memory(unsigned int max) {
    this->max = max;
    this->data = new byte[this->max];
}


Memory::~Memory() {
    delete this->data;
}

void Memory::init() {
    memset(this->data, 0, this->max);
}

void Memory::printStack() const {
    byte i = 0xFF;
    byte count = 0;
    printf("===[ STACK ]===\n");
    while(1) {
        if(count == 0)
            printf("| ");
        printf("%02x ", data[0x0100 | i]);
        if(count == 15) {
            printf("|\n");
            count = 0;
        }else
            count++;
        if(i == 0) break;
        i--;
    }
}

void Memory::printPage(byte page) const {
    byte i = 0x00;
    byte count = 0;
    word address = (word) (page << 8);
    printf("===[ PAGE %d ]===\n", page);
    while(1) {
        address &= 0xFF00;
        address |= i;
        if(count == 0)
            printf("| ");
        printf("%02x ", data[address]);
        if(count == 15) {
            printf("|\n");
            count = 0;
        }else
            count++;
        if(i == 0xFF) break;
        i++;
    }
}
