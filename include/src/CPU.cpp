#include <CPU.h>
#include <stdio.h>

CPU::CPU(unsigned int maxMemoryCapacity) : mem(maxMemoryCapacity) {}

void CPU::reset() {
    pc = 0xFFFC;

    flags.all = 0;

    sp = 0xFF;
    acc = x = y = 0;
    mem.init();
}

void CPU::execute(byte cycles) {
    byte instruction;
    byte value;

    while(cycles > 0) {
        instruction = fetchByte(cycles);
        switch(instruction) {
            default: break;
            case LDA_IM:{
                value = fetchByte(cycles);
                acc = value;
                setStatusLDA();
            } break;
            case LDA_ZP:{
                value = fetchByte(cycles);
                acc = readByte(cycles, value);
                setStatusLDA();
            } break;
            case LDA_ZP_X:{
                value = fetchByte(cycles);
                value += x;
                cycles--;
                acc = readByte(cycles, value);
                setStatusLDA();
            } break;
            case LDA_ZP_X_IND:{
                value = fetchByte(cycles);
                x += value;
                cycles--;
                word address = readWord(cycles, x);
                acc = readByte(cycles, address);
                setStatusLDA();
            } break;
            case LDA_ABS:{
                word address = fetchWord(cycles);
                acc = readByte(cycles, address);
                setStatusLDA();
            } break;
            case JMP_ABS:{
                pc = fetchWord(cycles);
            } break;
            case JMP_ABS_IND:{
                word address = fetchWord(cycles);
                pc = readWord(cycles, address);
            } break;
            case JSR:{
                word address = fetchWord(cycles);
                writeStackWord(cycles, pc - 1);
                pc = address;
                cycles--;
            } break;
            case ADC_IM:{
                value = fetchByte(cycles);
                word result = acc + value + flags.bits.c;
                setStatusADC(value, result);
                acc = result & 0x00FF;
            } break;
            case SBC_IM:{
                value = ~fetchByte(cycles);
                word result = acc + value + flags.bits.c;
                setStatusSBC(value, result);
                acc = result & 0x00FF;
            } break;
            case SEC:{
                flags.bits.c = 1;
                cycles--;
            } break;
        }
    }
}

byte CPU::fetchByte(byte &cycles) {
    byte data = mem.data[pc];
    pc++;
    cycles--;
    return data;
}

word CPU::fetchWord(byte &cycles) {
    word data = mem.data[pc];
    pc++;
    data |= (word) (mem.data[pc] << 8);
    pc++;
    cycles -= 2;
    return data;
}

byte CPU::readByte(byte &cycles, word address) {
    byte data = mem.data[address];
    cycles--;
    return data;
}

word CPU::readWord(byte &cycles, word address) {
    word data = mem.data[address];
    data |= (word) (mem.data[address + 1] << 8);
    cycles -= 2;
    return data;
}

void CPU::writeStackByte(byte &cycles, byte value) {
    sp--;
    mem.data[sp] = value;
    cycles--;
}

void CPU::writeStackWord(byte &cycles, word value) {
    sp--;
    mem.data[sp] = value >> 8;
    sp--;
    mem.data[sp] = value & 0x00FF;
    cycles -= 2;
}

byte CPU::negate(byte value) const {
    return (~value) + 1;
}

void CPU::setStatusLDA() {
    flags.bits.z = (acc == 0 ? 1 : 0);
    flags.bits.n = ((acc & 0x80) > 0 ? 1 : 0);
}

void CPU::setStatusADC(byte toAdd, word result) {
    flags.bits.c = result > 0xFF;
    flags.bits.z = (result & 0xFF) == 0;
    flags.bits.n = (result & 0x80) > 0;
    flags.bits.v = (((acc ^ result) & (~(acc ^ toAdd))) & 0x80) > 0;
}

void CPU::setStatusSBC(byte toAdd, word result) {
    // Si le résultat a une retenue
    // Par exemple 200 - 1 : c = 1
    // 123 - 192 : c = 0
    flags.bits.c = (result & 0xFF00) > 0;
    flags.bits.z = (result & 0xFF) == 0;
    flags.bits.n = (result & 0x80) > 0;
    flags.bits.v = (((acc ^ result) & (result ^ toAdd)) & 0x80) > 0;
}

void CPU::printData() const {
    printf(
        "===[ CPU DATA ]===\n"
        "[PC]    %04x\n"
        "[SP]    %02x\n"
        "[ACC]   %02x\n"
        "[REG X] %02x\n"
        "[REG Y] %02x\n"
        "Flags:\n"
        "[N] %d [V] %d [U] %d [B] %d [D] %d [I] %d [Z] %d [C] %d\n",
        pc, sp, acc, x, y,
        flags.bits.n, flags.bits.v, flags.bits.u, flags.bits.b, flags.bits.d, flags.bits.i, flags.bits.z, flags.bits.c
    );
}
