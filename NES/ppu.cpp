#include "ppu.h"

PPU::PPU()
{
}
PPU::~PPU()
{
}

void PPU::connect_bus(Bus* b)
{
    bus = b;
}

uint8_t PPU::read(uint16_t addr)
{
    if (0 <= addr && addr <= 0x1fff)
        return bus->ppu_read(addr);
    return 0;
}
void PPU::write(uint16_t addr, uint8_t data)
{
    if (0 <= addr && addr <= 0x1fff)
        bus->ppu_write(addr, data);
}