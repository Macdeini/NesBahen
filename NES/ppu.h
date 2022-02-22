#pragma once 
#include <stdint.h>
#include <unordered_map>
#include "bus.h"

class Bus;

class PPU
{
public:
    PPU();
    ~PPU();

    // Pattern Memory is image data
    // Nametable Memory is layout information
    // OAM is sprite specific informartion 
    // Palette memory dictates colour

    Bus* bus = nullptr;
    void connect_bus(Bus* b);

    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);

    // PPU registers
    // From left to right:
    // PPUCTRL PPUMASK PPUSTATUS OAMADDR OAMDATA PPUSCROLL PPUADDR PPUDATA
    std::array<uint8_t, 8> ppuRegisters = {0, 0, 0b10100000, 0, 0, 0, 0, 0};
    uint8_t direct_memory_access = 0; 
    
    struct Tile {
        // values are between 0 and 3
        std::array<std::array<uint8_t, 8>, 8> pixels;
    };
    Tile construct_tile(uint16_t addr);
    std::array<Tile, 256> left_tiles; 
    std::array<Tile, 256> right_tiles; 
    void construct_left_tiles();
    void construct_right_tiles();

    std::array<uint8_t, 0x1000> nametables;
    std::array<uint8_t, 0x20> palettes; 
    std::array<uint8_t, 0x100> oam;  
};