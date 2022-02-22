#include <iostream>
#include <bitset>
#include <vector>
#include <fstream>
#include <string>
#include "NES/6502.h"
#include "NES/bus.h"
#include "NES/cartridge.h"

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
    std::string file_location = "testing/nestest.log.txt";
    std::ifstream nestest(file_location);
    std::string line;
    while(std::getline(nestest, line)) {
        Log log = Log();
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
        log.cyc = std::stoi(line.substr(90), nullptr, 10);  // clock
        logs.push_back(log);
    }
    nestest.close();
    return logs;
}

std::vector<Log> get_cpu_log(Nes6502 cpu, int upperbound){
    std::vector<Log> logs;
    do {
        if (cpu.cycles == 0) { // check if cpu has finished execution of instruction
            Log log = Log();
            log.pc_addr = cpu.pc;
            log.byte1 = cpu.read(cpu.pc);
            log.byte2 = cpu.read(cpu.pc + 1);
            log.byte3 = cpu.read(cpu.pc + 2);
            log.instruction = cpu.table[cpu.read(cpu.pc)].opcode_name;
            log.a = cpu.a;
            log.x = cpu.x;
            log.y = cpu.y;
            log.p = cpu.status;
            log.sp = cpu.sp;
            log.cyc = cpu.total_cycles;
            logs.push_back(log);
        }
        cpu.emulate_cycle();
    } while (cpu.total_cycles <= upperbound);
    return logs;
}

void print_log(Log log){
    std::cout << std::hex << std::setfill('0') << std::setw(4) << int(log.pc_addr) << "  ";
    std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)(log.byte1) << " ";
    std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)(log.byte2) << " ";
    std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)(log.byte3) << "  "; 
    std::cout << "  " << log.instruction << "    ";
    std::cout << "                ";
    std::cout << "A:" << std::hex << std::setfill('0') << std::setw(2) << int(log.a) << " ";
    std::cout << "X:" << std::hex << std::setfill('0') << std::setw(2) << int(log.x) << " ";
    std::cout << "Y:" << std::hex << std::setfill('0') << std::setw(2) << int(log.y) << " ";
    std::cout << "P:" << std::hex << std::setfill('0') << std::setw(2) << int(log.p) << " ";
    std::cout << "SP:" << std::hex << std::setfill('0') << std::setw(2) << int(log.sp) << " ";
    std::cout << "CYC:" << std::dec << log.cyc << " " << std::endl;
}

bool compare_log(Log log1, Log log2){
    bool pctest = log1.pc_addr == log2.pc_addr;
    bool byte1test = log1.byte1 == log2.byte1;
    bool nametest = log1.instruction == log2.instruction;
    bool atest = log1.a == log2.a;
    bool xtest = log1.x == log2.x;
    bool ytest = log1.y == log2.y;
    bool ptest = log1.p == log2.p;
    bool sptest = log1.sp == log2.sp;
    bool clocktest = log1.cyc == log2.cyc;
    std::array<bool, 9> test = {pctest, byte1test, nametest, atest, xtest, ytest, ptest, sptest, clocktest};
    for (auto b : test){
        if (b == false)
            return false;
    }
    return true;
}

int run_nestest(){
    std::vector<Log> nestest_logs = load_testlog();
    Nes6502 cpu;
    cpu.pc = 0xC000;
    Bus bus;
    cpu.connect_bus(&bus);
    bus.set_cpu(&cpu);
    Cartridge test;
    bus.set_cartridge(&test);
    const int end_of_test = 14575; // at pc = 0xC6BC
    int upper = end_of_test;
    std::vector<Log> cpu_logs = get_cpu_log(cpu, upper);
    int back = 2;
    int front = 0; 

    bool success = true;
    for (int i = 0; i < cpu_logs.size(); ++i){
        bool compare = compare_log(cpu_logs[i], nestest_logs[i]);
        if (compare == false){
            std::cout << "Mine" << std::endl;
            for (int j = back; j >= -1 * front; j--){   
                std::cout << "  ";
                print_log(cpu_logs[i - j]);   
            }
            std::cout << "Them" << std::endl;
            for (int j = back; j >= -1 * front; j--){   
                std::cout << "  ";
                print_log(nestest_logs[i - j]);   
            }
            success = false;
            return 1;
        }
    }

    if (success)
        std::cout << "All tests pass" << std::endl;

    return 0;
}

// int main(){
//     run_nestest();
//     return 0;
// }
