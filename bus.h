#pragma once
#include <array>

/*
* Bus class for transferring data along the machine
*/
class Nes6502;

class Bus {

public:
    Bus();
    ~Bus();

    // Devices connected to the bus
    std::array<uint8_t, 0xFFFF+1> ram;
    Nes6502* cpu = nullptr;

    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr);
    uint8_t* fetch(uint16_t addr);
};