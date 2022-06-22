#include <stdio.h>

#include <CPU.h>
#include <instruction.h>

int main() {
    const char *unkwn = "???";
    Instruction instructions[256] = {
        { "BRK", 7 }, { "ORA", 6 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "ORA", 3 }, { "ASL", 5 }, { unkwn, 1 }, { "PHP", 3 }, { "ORA", 2 }, { "ASL", 2 }, { unkwn, 1 }, { unkwn, 1 }, { "ORA", 4 }, { "ASL", 6 }, { unkwn, 1 },
        { "BPL", 4 }, { "ORA", 6 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "ORA", 4 }, { "ASL", 6 }, { unkwn, 1 }, { "CLC", 2 }, { "ORA", 5 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "ORA", 5 }, { "ASL", 7 }, { unkwn, 1 },
        { "JSR", 6 }, { "AND", 6 }, { unkwn, 1 }, { unkwn, 1 }, { "BIT", 3 }, { "AND", 3 }, { "ROL", 5 }, { unkwn, 1 }, { "PLP", 4 }, { "AND", 2 }, { "ROL", 2 }, { unkwn, 1 }, { "BIT", 4 }, { "AND", 4 }, { "ROL", 6 }, { unkwn, 1 },
        { "BMI", 4 }, { "AND", 6 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "AND", 4 }, { "ROL", 6 }, { unkwn, 1 }, { "SEC", 2 }, { "AND", 5 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "AND", 5 }, { "ROL", 7 }, { unkwn, 1 },
        { "RTI", 6 }, { "EOR", 6 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "EOR", 3 }, { "LSR", 5 }, { unkwn, 1 }, { "PHA", 3 }, { "EOR", 2 }, { "LSR", 2 }, { unkwn, 1 }, { "JMP", 3 }, { "EOR", 4 }, { "LSR", 6 }, { unkwn, 1 },
        { "BVC", 4 }, { "EOR", 6 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "EOR", 4 }, { "LSR", 6 }, { unkwn, 1 }, { "CLI", 2 }, { "EOR", 5 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "EOR", 5 }, { "LSR", 7 }, { unkwn, 1 },
        { "RTS", 6 }, { "ADC", 6 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "ADC", 3 }, { "ROR", 5 }, { unkwn, 1 }, { "PLA", 4 }, { "ADC", 2 }, { "ROR", 2 }, { unkwn, 1 }, { "JMP", 5 }, { "ADC", 4 }, { "ROR", 6 }, { unkwn, 1 },
        { "BVS", 4 }, { "ADC", 6 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "ADC", 4 }, { "ROR", 6 }, { unkwn, 1 }, { "SEI", 2 }, { "ADC", 5 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "ADC", 5 }, { "ROR", 7 }, { unkwn, 1 },
        { unkwn, 1 }, { "STA", 6 }, { unkwn, 1 }, { unkwn, 1 }, { "STY", 3 }, { "STA", 3 }, { "STX", 3 }, { unkwn, 1 }, { "DEY", 2 }, { unkwn, 1 }, { "TXA", 2 }, { unkwn, 1 }, { "STY", 4 }, { "STA", 4 }, { "STX", 4 }, { unkwn, 1 },
        { "BCC", 4 }, { "STA", 6 }, { unkwn, 1 }, { unkwn, 1 }, { "STY", 4 }, { "STA", 4 }, { "STX", 4 }, { unkwn, 1 }, { "TYA", 2 }, { "STA", 5 }, { "TXS", 2 }, { unkwn, 1 }, { unkwn, 1 }, { "STA", 5 }, { unkwn, 1 }, { unkwn, 1 },
        { "LDY", 2 }, { "LDA", 6 }, { "LDX", 2 }, { unkwn, 1 }, { "LDY", 3 }, { "LDA", 3 }, { "LDX", 3 }, { unkwn, 1 }, { "TAY", 2 }, { "LDA", 2 }, { "TAX", 2 }, { unkwn, 1 }, { "LDY", 4 }, { "LDA", 4 }, { "LDX", 4 }, { unkwn, 1 },
        { "BCS", 4 }, { "LDA", 6 }, { unkwn, 1 }, { unkwn, 1 }, { "LDY", 4 }, { "LDA", 4 }, { "LDX", 4 }, { unkwn, 1 }, { "CLV", 2 }, { "LDA", 5 }, { "TSX", 2 }, { unkwn, 1 }, { "LDY", 5 }, { "LDA", 5 }, { "LDX", 5 }, { unkwn, 1 },
        { "CPY", 2 }, { "CMP", 6 }, { unkwn, 1 }, { unkwn, 1 }, { "CPY", 3 }, { "CMP", 3 }, { "DEC", 5 }, { unkwn, 1 }, { "INY", 2 }, { "CMP", 2 }, { "DEX", 2 }, { unkwn, 1 }, { "CPY", 4 }, { "CMP", 4 }, { "DEC", 6 }, { unkwn, 1 },
        { "BNE", 4 }, { "CMP", 6 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "CMP", 4 }, { "DEC", 6 }, { unkwn, 1 }, { "CLD", 2 }, { "CMP", 5 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "CMP", 5 }, { "DEC", 7 }, { unkwn, 1 },
        { "CPX", 2 }, { "SBC", 6 }, { unkwn, 1 }, { unkwn, 1 }, { "CPX", 3 }, { "SBC", 3 }, { "INC", 5 }, { unkwn, 1 }, { "INX", 2 }, { "SBC", 2 }, { "NOP", 2 }, { unkwn, 1 }, { "CPX", 4 }, { "SBC", 4 }, { "INC", 6 }, { unkwn, 1 },
        { "BEQ", 4 }, { "SBC", 6 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "SBC", 4 }, { "INC", 6 }, { unkwn, 1 }, { "SED", 2 }, { "SBC", 5 }, { unkwn, 1 }, { unkwn, 1 }, { unkwn, 1 }, { "SBC", 5 }, { "INC", 7 }, { unkwn, 1 }
    };

    CPU cpu(65536, instructions);
    cpu.reset();
    cpu.mem.data[0xFFFC] = Instruction::JMP_ABS;
    cpu.mem.data[0xFFFD] = 0x00;
    cpu.mem.data[0xFFFE] = 0xFF;

    cpu.mem.data[0x0005] = 0x02;
    cpu.mem.data[0x0006] = 0x66;
    cpu.mem.data[0x6602] = 0x24;
    cpu.mem.data[0x6603] = 0x25;
    cpu.mem.data[0x6604] = 0x26;

    cpu.y = 2;
    cpu.mem.data[0xFF00] = Instruction::LDA_ZP_IND_Y_IDX;
    cpu.mem.data[0xFF01] = 0x05;

    while(cpu.execute()) {
        cpu.printData();
    }

    printf("Au revoir !\n");
    return 0;
}
