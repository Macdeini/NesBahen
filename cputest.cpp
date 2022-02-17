#include <iostream>
#include <bitset>
#include <vector>
#include <fstream>
#include <string>
#include "6502.h"
#include "bus.h"
#include "cartridge.h"

// one line of data in the log file
struct Log {
    uint16_t pc_addr = 0;
    uint8_t byte1 = 0;
    uint8_t byte2 = 0;
    uint8_t byte3 = 0;
    std::string instruction = "";
    uint8_t a = 0;
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t p = 0;
    uint8_t sp = 0;
    int cyc = 0;
};

std::vector<Log> load_testlog(){
    std::vector<Log> logs;
    std::string file_location = "testlogs/nestest.log.txt";
    std::ifstream nestest(file_location);
    std::string line;
    while(std::getline(nestest, line)) {
        Log log;
        log.pc_addr = std::stoi(line.substr(0, 4), nullptr, 16); // pc address
        log.byte1 = std::stoi(line.substr(6, 2), nullptr, 16);   // byte 1
        std::string byte_temp = line.substr(9, 2);
        if (byte_temp != "  ")
            log.byte2 = std::stoi(byte_temp, nullptr, 16);       // byte2   
        byte_temp = line.substr(12, 2);
        if (byte_temp != "  ")
            log.byte3 = std::stoi(byte_temp, nullptr, 16);       // byte2   
        log.instruction = line.substr(16 ,3);                    // instruction name 
        log.a = std::stoi(line.substr(50, 2), nullptr, 16);      // accumulator
        log.x = std::stoi(line.substr(55, 2), nullptr, 16);      // x
        log.y = std::stoi(line.substr(60, 2), nullptr, 16);      // y
        log.p = std::stoi(line.substr(65, 2), nullptr, 16);      // status
        log.sp = std::stoi(line.substr(71, 2), nullptr, 16);     // sp
        log.cyc = sstd::stoi(line.substr(90, ), nullptr, 16);  // clock
        
        fix clock reading

        logs.push_back(log);
    }
    nestest.close();
    return logs;
}

int main(){
    load_testlog();

    Nes6502 cpu;
    Bus bus;
    cpu.connect_bus(&bus);
    bus.set_cpu(&cpu);
    Cartridge test;
    bus.set_cartridge(&test);
    
    cpu.pc = 0xC000;

    int count = 0xce5b;
    do {
        cpu.emulate_cycle();
    } while(cpu.total_cycles <= 600);

    // Full test

    // do {
    //     cpu.emulate_cycle();
    // } while(cpu.pc != 0xC6BC);


    return 0;
}
