#include <stdio.h>

#include <CPU.h>

int main() {
    CPU cpu(65536);
    cpu.reset();
    cpu.mem.data[0xFFFC] = CPU::JMP_ABS;
    cpu.mem.data[0xFFFD] = 0x0000;
    cpu.mem.data[0xFFFE] = 0x0000;

    cpu.mem.data[0x0000] = CPU::JMP_ABS_IND;
    cpu.mem.data[0x0001] = 0x26;
    cpu.mem.data[0x0002] = 0x62;

    cpu.mem.data[0x6226] = 0x00;
    cpu.mem.data[0x6227] = 0x51;

    cpu.mem.data[0x5100] = CPU::LDA_ABS;
    cpu.mem.data[0x5101] = 0x02;
    cpu.mem.data[0x5102] = 0x00;

    cpu.mem.data[0x5103] = CPU::JSR;
    cpu.mem.data[0x5104] = 0x00;
    cpu.mem.data[0x5105] = 0x60;

    cpu.x = 0x05;
    cpu.mem.data[0x6000] = CPU::LDA_ZP_X_IND;
    cpu.mem.data[0x6001] = 0x0A;
    cpu.mem.data[0x000F] = 0xCD;
    cpu.mem.data[0x0010] = 0xDC;
    cpu.mem.data[0xDCCD] = 127;

    cpu.mem.data[0x6002] = CPU::ADC_IM;
    cpu.mem.data[0x6003] = 1;
    cpu.mem.data[0x6004] = CPU::ADC_IM;
    cpu.mem.data[0x6005] = 128;
    cpu.mem.data[0x6006] = CPU::ADC_IM;
    cpu.mem.data[0x6007] = 0;
    cpu.mem.data[0x6008] = CPU::SEC;
    cpu.mem.data[0x6009] = CPU::SBC_IM;
    cpu.mem.data[0x600A] = 2;

    // JMP_ABS
    cpu.execute(3);
    //cpu.printData();

    // JMP_ABS_IND
    cpu.execute(5);
    //cpu.printData();

    // LDA_ABS
    cpu.execute(4);
    //cpu.printData();

    // JSR
    cpu.execute(6);
    //cpu.printData();
    
    // LDA_ZP_X_IND
    cpu.execute(6);
    cpu.printData();

    // ADC_IM
    cpu.execute(2);
    cpu.printData();

    // ADC_IM
    cpu.execute(2);
    cpu.printData();

    // ADC_IM
    cpu.execute(2);
    cpu.printData();

    // SEC
    cpu.execute(2);

    // SBC_IM
    cpu.execute(2);
    cpu.printData();

    /* cpu.mem.printStack();
    cpu.mem.printPage(0xFF); */

    printf("Au revoir !\n");
    return 0;
}
