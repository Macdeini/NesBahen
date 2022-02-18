#pragma once 
#include "array"
#include "cstdint"

class PPU
{
    PPU();
    ~PPU();
    
    std::array<uint8_t, 0x20> palette_table;
    std::array<uint8_t, 0x800> vram;
    std::array<uint8_t, 0x100> oam;
    
};