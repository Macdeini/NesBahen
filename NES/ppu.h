#pragma once 
#include <stdint.h>
#include <unordered_map>
#include <SDL2/SDL.h>
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
    // Palette memory is colour

    Bus* bus = nullptr;
    void connect_bus(Bus* b);

    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);

    // PPU registers
    // From left to right:
    // PPUCTRL PPUMASK PPUSTATUS OAMADDR OAMDATA PPUSCROLL PPUADDR PPUDATA
    std::array<uint8_t, 8> ppu_registers = {0, 0, 0b10100000, 0, 0, 0, 0, 0};
    uint8_t direct_memory_access = 0; 
    
    const int bitmap_size = 0x8;
    struct Tile {
        // lsbm = least significant bitmap
        // msbm = most significant bitmap
        // each entry in lsbm and msbm represent the row of bytes that form each individual bitplane
        std::array<uint8_t, 8> lsbm;
        std::array<uint8_t, 8> msbm;
        // pixel_pattern is a 8x8 array where each entry represents the color at that pixel 
        std::array<std::array<uint8_t, 8>, 8> pixel_pattern;
    };
    PPU::Tile construct_tile(uint16_t addr);
    
    std::array<Tile, 256> left_tiles; 
    std::array<Tile, 256> right_tiles; 
    void construct_left_tiles();
    void construct_right_tiles();
    void construct_pattern_memory();

    std::array<uint8_t, 0x1000> nametables;
    std::array<uint8_t, 0x20> palettes; 
    std::array<uint8_t, 0x100> oam;  
};