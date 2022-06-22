#include <CPU.h>
#include <stdio.h>

CPU::CPU(unsigned int maxMemoryCapacity, Instruction _instructions[256]) :
    mem(maxMemoryCapacity), instructions(_instructions) {}

void CPU::reset() {
    pc = 0xFFFC;

    flags.all = 0;

    sp = 0xFF;
    acc = x = y = 0;
    mem.init();
    cycles = 1;
}

bool CPU::execute() {
    byte value;

    instruction = fetchByte();
    cycles = instructions[instruction].cycles - 1;
    switch(instruction) {
        default: return false;
        case Instruction::LDA_IMM:{
            value = fetchByte();
            acc = value;
            setStatusLDA();
        } return true;
        case Instruction::LDA_ZP:{
            value = fetchByte();
            acc = readByte(value);
            setStatusLDA();
        } return true;
        case Instruction::LDA_ZP_X:{
            value = fetchByte();
            value += x;
            cycles--;
            acc = readByte(value);
            setStatusLDA();
        } return true;
        case Instruction::LDA_ZP_X_IND:{
            value = fetchByte();
            value += x;
            cycles--;
            word address = readWord(x);
            acc = readByte(address);
            setStatusLDA();
        } return true;
        case Instruction::LDA_ZP_IND_Y_IDX:{
            value = fetchByte();
            word address = y;
            address += readWord(value);
            acc = readByte(address);
            cycles = 0;
            setStatusLDA();
        } return true;
        case Instruction::LDA_ABS:{
            word address = fetchWord();
            acc = readByte(address);
            setStatusLDA();
        } return true;
        case Instruction::LDA_ABS_X:{
            word address = fetchWord() + x;
            acc = readByte(address);
            // Le nombre de cycles dépend de si la page est croisée
            cycles = 0;
            setStatusLDA();
        } return true;
        case Instruction::LDA_ABS_Y:{
            word address = fetchWord() + y;
            acc = readByte(address);
            // Le nombre de cycles dépend de si la page est croisée
            cycles = 0;
            setStatusLDA();
        } return true;
        case Instruction::LDX_IMM:{
            x = fetchByte();
            setStatusLDX();
        } return true;
        case Instruction::LDX_ZP:{
            value = fetchByte();
            x = readByte(value);
            setStatusLDX();
        } return true;
        case Instruction::LDX_ZP_Y:{
            value = fetchByte();
            value += y;
            cycles--;
            x = readByte(value);
            setStatusLDX();
        } return true;
        case Instruction::LDX_ABS:{
            word address = fetchWord();
            x = readByte(address);
            setStatusLDX();
        } return true;
        case Instruction::LDX_ABS_Y:{
            word address = fetchWord() + y;
            x = readByte(address);
            // Le nombre de cycles dépend de si la page est croisée
            cycles = 0;
            setStatusLDX();
        } return true;
        case Instruction::LDY_IMM:{
            y = fetchByte();
            setStatusLDY();
        } return true;
        case Instruction::LDY_ZP:{
            value = fetchByte();
            y = readByte(value);
            setStatusLDY();
        } return true;
        case Instruction::LDY_ZP_X:{
            value = fetchByte();
            value += x;
            cycles--;
            y = readByte(value);
            setStatusLDY();
        } return true;
        case Instruction::LDY_ABS:{
            word address = fetchWord();
            y = readByte(address);
            setStatusLDY();
        } return true;
        case Instruction::LDY_ABS_X:{
            word address = fetchWord() + x;
            y = readByte(address);
            // Le nombre de cycles dépend de si la page est croisée
            cycles = 0;
            setStatusLDY();
        } return true;
        case Instruction::STA_ZP:{
            value = fetchByte();
            writeByte(value, acc);
        } return true;
        case Instruction::STA_ZP_X:{
            value = fetchByte();
            value += x;
            cycles--;
            writeByte(value, acc);
        } return true;
        case Instruction::STA_ABS:{
            word address = fetchWord();
            writeByte(address, acc);
        } return true;
        case Instruction::STA_ABS_X:{
            word address = fetchWord();
            address += x;
            cycles--;
            writeByte(address, acc);
        } return true;
        case Instruction::STA_ABS_Y:{
            word address = fetchWord();
            address += y;
            cycles--;
            writeByte(address, acc);
        } return true;
        case Instruction::STA_ZP_X_IND:{
            value = fetchByte();
            value += x;
            cycles--;
            word address = readWord(value);
            writeByte(address, acc);
        } return true;
        case Instruction::STA_ZP_IND_Y_IDX:{
            value = fetchByte();
            word address = readWord(value);
            address += y;
            cycles--;
            writeByte(address, acc);
        } return true;
        case Instruction::STX_ZP:{
            value = fetchByte();
            writeByte(value, x);
        } return true;
        case Instruction::STX_ZP_Y:{
            value = fetchByte();
            value += y;
            cycles--;
            writeByte(value, x);
        } return true;
        case Instruction::STX_ABS:{
            word address = fetchWord();
            writeByte(address, x);
        } return true;
        case Instruction::STY_ZP:{
            value = fetchByte();
            writeByte(value, y);
        } return true;
        case Instruction::STY_ZP_X:{
            value = fetchByte();
            value += x;
            cycles--;
            writeByte(value, y);
        } return true;
        case Instruction::STY_ABS:{
            word address = fetchWord();
            writeByte(address, y);
        } return true;
        case Instruction::JMP_ABS:{
            pc = fetchWord();
        } return true;
        case Instruction::JMP_ABS_IND:{
            word address = fetchWord();
            pc = readWord(address);
        } return true;
        case Instruction::JSR:{
            word address = fetchWord();
            writeStackWord(pc - 1);
            pc = address;
            cycles--;
        } return true;
        case Instruction::ADC_IM:{
            value = fetchByte();
            word result = acc + value + flags.bits.c;
            setStatusADC(value, result);
            acc = result & 0x00FF;
        } return true;
        case Instruction::SBC_IM:{
            value = ~fetchByte();
            word result = acc + value + flags.bits.c;
            setStatusSBC(value, result);
            acc = result & 0x00FF;
        } return true;
        case Instruction::CLD:{
            flags.bits.d = 0;
            cycles--;
        } return true;
        case Instruction::SED:{
            flags.bits.d = 1;
            cycles--;
        } return true;
        case Instruction::CLI:{
            flags.bits.i = 0;
            cycles--;
        } return true;
        case Instruction::SEI:{
            flags.bits.i = 1;
            cycles--;
        } return true;
        case Instruction::CLC:{
            flags.bits.c = 0;
            cycles--;
        } return true;
        case Instruction::SEC:{
            flags.bits.c = 1;
            cycles--;
        } return true;
        case Instruction::CLV:{
            flags.bits.v = 0;
            cycles--;
        } return true;
        case Instruction::RTS:{
            pc = readStackWord() + 1;
            cycles = 0;
        } return true;
    }
}

byte CPU::fetchByte() {
    byte data = mem.data[pc];
    pc++;
    cycles--;
    return data;
}

word CPU::fetchWord() {
    word data = mem.data[pc];
    pc++;
    data |= (word) (mem.data[pc] << 8);
    pc++;
    cycles -= 2;
    return data;
}

byte CPU::readByte(word address) {
    byte data = mem.data[address];
    cycles--;
    return data;
}

word CPU::readWord(word address) {
    word data = mem.data[address];
    data |= (word) (mem.data[address + 1] << 8);
    cycles -= 2;
    return data;
}

void CPU::writeByte(word address, byte value) {
    mem.data[address] = value;
    cycles--;
}

void CPU::writeWord(word address, word value) {
    mem.data[address]     = value & 0xFF;
    mem.data[address + 1] = (value >> 8) & 0xFF;
    cycles -= 2;
}

byte CPU::readStackByte() {
    byte data = mem.data[sp];
    sp++;
    cycles--;
    return data;
}

word CPU::readStackWord() {
    word data = mem.data[sp];
    sp++;
    data |= (word) (mem.data[sp] << 8);
    sp++;
    cycles -= 2;
    return data;
}

void CPU::writeStackByte(byte value) {
    sp--;
    mem.data[sp] = value;
    cycles--;
}

void CPU::writeStackWord(word value) {
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

void CPU::setStatusLDX() {
    flags.bits.z = (x == 0);
    flags.bits.n = ((x & 0x80) > 0);
}

void CPU::setStatusLDY() {
    flags.bits.z = (y == 0);
    flags.bits.n = ((y & 0x80) > 0);
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
        "[INS]   %s\n"
        "Flags:\n"
        "[N] %d [V] %d [U] %d [B] %d [D] %d [I] %d [Z] %d [C] %d\n",
        pc, sp, acc, x, y, instructions[instruction].name,
        flags.bits.n, flags.bits.v, flags.bits.u, flags.bits.b, flags.bits.d, flags.bits.i, flags.bits.z, flags.bits.c
    );
}
