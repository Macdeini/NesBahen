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

/*
* Reads a value along the CPU's memory bus
*/
uint8_t Bus::cpu_read(uint16_t addr)
{
    if (0 <= addr && addr <= 0x1fff) { // reading from cpu internal ram
        return cpu_ram[addr & 0x07ff];
    }
    if (0x2000 <= addr && addr <= 0x3FFF) { // PPU registers
        uint16_t ppu_register = (addr % 0x2000) % 8;
        switch (ppu_register) {
            case 0:
                return ppu->PPU_CTRL;
                break;
            case 1:
                return ppu->PPU_MASK;
                break;
            case 2:
                return ppu->PPU_STATUS; 
                break;
            case 3:
                return ppu->OAM_ADDR; 
                break;
            case 4:
                return ppu->OAM_DATA; 
                break;
            case 5:
                return ppu->PPU_SCROLL; 
                break;
            case 6:
                return ppu->PPU_ADDR; 
                break;
            case 7:
                return ppu->PPU_DATA;
                break;
        }
    }
    if (0x8000 <= addr && addr <= 0xffff) { // reading from cartridge rom
        return cartridge->read_prg(addr - 0x8000);
    }
    return 0;
}

/*
* Writes a value along the CPU's memory bus
*/
void Bus::cpu_write(uint16_t addr, uint8_t data)
{
    if (0 <= addr && addr <= 0x1fff) { // internal ram
        cpu_ram[addr & 0x07ff] = data;
    }   
    if (0x2000 <= addr && addr <= 0x3FFF) { // PPU registers
        uint16_t ppu_register = (addr % 0x2000) % 8;
        switch (ppu_register) {
            case 0:
                ppu->PPU_CTRL = data; 
                break;
            case 1:
                ppu->PPU_MASK = data;
                break;
            case 2:
                ppu->PPU_STATUS = data; 
                break;
            case 3:
                ppu->OAM_ADDR = data; 
                break;
            case 4:
                ppu->OAM_DATA = data; 
                break;
            case 5:
                ppu->PPU_SCROLL = data; 
                break;
            case 6:
                ppu->PPU_ADDR = data; 
                break;
            case 7:
                ppu->PPU_DATA = data;
                break;
        }
    }
    if (addr == 0x4014) { // OAMDMA PPU register
        ppu->OAM_DMA = data;
    }
    if (0x8000 <= addr && addr <= 0xffff) { // cartridge rom
        cartridge->write_prg(addr - 0x8000, data);
    }
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