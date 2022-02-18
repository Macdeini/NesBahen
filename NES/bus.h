#pragma once
#include <array>
#include "6502.h"
#include "cartridge.h"
#include "ppu.h"

/*
* Bus class for transferring data along the machine
*/
class Nes6502;

class Bus {

public:
    Bus();
    ~Bus();

    // Devices connected to the bus
    std::array<uint8_t, 0x0800> cpu_ram;
    Nes6502* cpu = nullptr;
    Cartridge* cartridge = nullptr;
    PPU* ppu = nullptr;

    void set_cpu(Nes6502* cpu);
    void set_cartridge(Cartridge* c);
    void set_ppu(PPU* c);

    void cpu_write(uint16_t addr, uint8_t data);
    uint8_t cpu_read(uint16_t addr);

    // Only used by cpu
    uint8_t* fetch(uint16_t addr);
};