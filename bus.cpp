#include "bus.h"

Bus::Bus()
{
    for (auto &i : ram)
        i = 0x00;
}

Bus::~Bus()
{
}

uint8_t Bus::read(uint16_t addr)
{
    return ram[addr];
}

void Bus::write(uint16_t addr, uint8_t data)
{
    ram[addr] = data;
}

uint8_t* Bus::fetch(uint16_t addr) 
{
    return &ram[addr];
}