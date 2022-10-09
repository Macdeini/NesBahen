#pragma once
#include <array>
#include "6502.h"
#include "cartridge.h"
#include "ppu.h"

/*
* Bus class for transferring data along the machine
*/
class Nes6502;
class PPU;

class Bus {

public:
    Bus();
    ~Bus();

    // Devices connected to the bus
    std::array<uint8_t, 0x0800> cpu_ram;
    Nes6502* cpu = nullptr;
    Cartridge* cartridge = nullptr;
    PPU* ppu = nullptr;

    void set_cpu(Nes6502* c);
    void set_cartridge(Cartridge* c);
    void set_ppu(PPU* p);

    void cpu_write(uint16_t addr, uint8_t data);
    uint8_t cpu_read(uint16_t addr);
    uint8_t* cpu_fetch(uint16_t addr);

    // These should only be used when accessing pattern memory on the cartridge
    void ppu_write(uint16_t addr, uint8_t data);
    uint8_t ppu_read(uint16_t addr);

    Mirroring get_nametable_mirroring();
};