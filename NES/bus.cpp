#include "bus.h"

Bus::Bus()
{
    for (auto &i : cpu_ram)
        i = 0x00;
}

void Bus::set_cartridge(Cartridge* c)
{
    cartridge = c;
}
void Bus::set_cpu(Nes6502* c)
{
    cpu = c;
}
void Bus::set_ppu(PPU* p)
{
    ppu = p;
}

Bus::~Bus()
{
}

uint8_t Bus::cpu_read(uint16_t addr)
{
    if (0 <= addr && addr <= 0x1fff) // reading from cpu internal ram
        return cpu_ram[addr & 0x07ff];
    if (0x8000 <= addr && addr <= 0xffff) // reading from cartridge rom
        return cartridge->read_prg(addr - 0x8000);
    return 0;
}

void Bus::cpu_write(uint16_t addr, uint8_t data)
{
    if (0 <= addr && addr <= 0x1fff)
        cpu_ram[addr & 0x07ff] = data;   
    if (0x8000 <= addr && addr <= 0xffff) // reading from cartridge rom
        return cartridge->write_prg(addr - 0x8000, data);
}

uint8_t* Bus::cpu_fetch(uint16_t addr) 
{
    if (0 <= addr && addr <= 0x1fff)
        return &cpu_ram[addr & 0x07ff];
    if (0x8000 <= addr && addr <= 0xffff) // reading from cartridge rom
        return cartridge->fetch(addr - 0x8000);
    return nullptr;
}

// $0000-1fff addressing range for PPU indicate CHR memory on cartridge
uint8_t Bus::ppu_read(uint16_t addr)
{
    if (0 <= addr && addr <= 0x1fff) {
        return cartridge->read_chr(addr);
    }
    return 0;
}

void Bus::ppu_write(uint16_t addr, uint8_t data)
{
    if (0 <= addr && addr <= 0x1fff)
        return cartridge->write_chr(addr, data);
    return;
    
}