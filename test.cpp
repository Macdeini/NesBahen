#include <iostream>
// #define OLC_PGE_APPLICATION
// #include "olcPixelGameEngine.h"
#include <bitset>
#include <vector>
#include "6502.h"
#include "bus.h"
#include "cartridge.h"


int main(){
    
    Nes6502 cpu;
    Bus bus;
    cpu.connect_bus(&bus);
    bus.set_cpu(&cpu);
    Cartridge test;
    // bus.set_cartridge(&test);
    
    cpu.pc = 0xC000;

    for (int i = 0; i < cpu.table.size(); i++){
        if (cpu.table[i].opcode_name != "RIP")
            std::cout << std::hex << i << " " << cpu.table[i].opcode_name << std::endl;
    }

    do {
        cpu.emulate_cycle();
    } while(cpu.pc != 0xc66e);


    return 0;
}
