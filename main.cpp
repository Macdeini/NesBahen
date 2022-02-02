#include <iostream>
#include <bitset>
#include "6502.h"
#include "bus.h"


int main() {
    Nes6502 cpu;
    // Bus bus;
    // cpu.connect_bus(&bus);
    // bus.cpu = &cpu; 
    // int addr = 0xAAAA;
    // bus.ram[addr] = 0xAA;
    // cpu.addr = addr;
    // cpu.fetch();
    std::cout << std::hex << (int)cpu.sp;
}
