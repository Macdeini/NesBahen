#pragma once 
#include <stdint.h>
#include "bus.h"

class Bus;

class PPU
{
public:
    PPU();
    ~PPU();

    Bus* bus = nullptr;
    void connect_bus(Bus* b);
    
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);
};