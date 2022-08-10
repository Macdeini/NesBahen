#pragma once 
#include <stdint.h>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "bus.h"
#include <bitset>

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
        // pixel_pattern is a 8x8 array where each entry represents the palette color at that pixel (0-3)
        std::array<std::array<uint8_t, 8>, 8> pixel_pattern;
    };
    std::array<Tile, 512> tiles;  
    PPU::Tile construct_tile(uint16_t addr);
    void construct_pattern_memory();

    // array of possible colors to be used in the palette (rbg)
    std::array<std::array<int, 3>, 64> palettes = 
        {{ 
            {84, 84, 84},    {0, 30, 116},    {8, 16, 144},    {48, 0, 136},    {68, 0, 100},    {92, 0, 48},     {84, 4, 0},      {60, 24, 0},
            {32, 42, 0},     {8, 58, 0},      {0, 64, 0},      {0, 60, 0},      {0, 50, 60},     {0, 0, 0},       {0, 0, 0},       {0, 0, 0}, 
            {152, 150, 152}, {8, 76, 196},    {48, 50, 236},   {92, 30, 228},   {136, 20, 176},  {160, 20, 100},  {152, 34, 32},   {120, 60, 0},
            {84, 90, 0},     {40, 114, 0},    {8, 124, 0},     {0, 118, 40},    {0, 102, 120},   {0, 0, 0},       {0, 0, 0},       {0, 0, 0}, 
            {236, 238, 236}, {76, 154, 236},  {120, 124, 236}, {176, 98, 236},  {228, 84, 236},  {236, 88, 180},  {236, 106, 100}, {212, 136, 32},  
            {160, 170, 0},   {116, 196, 0},   {76, 208, 32},   {56, 204, 108},  {56, 180, 204},  {60, 60, 60},    {0, 0, 0},       {0, 0, 0}, 
            {236, 238, 236}, {168, 204, 236}, {188, 188, 236}, {212, 178, 236}, {236, 174, 236}, {236, 174, 212}, {236, 180, 176}, {228, 196, 144}, 
            {204, 210, 120}, {180, 222, 120}, {168, 226, 144}, {152, 226, 180}, {160, 214, 228}, {160, 162, 160}, {0, 0, 0},       {0, 0, 0} 
        }}; 

    std::array<uint8_t, 0x1000> nametables;
    std::array<uint8_t, 0x100> oam;  
};