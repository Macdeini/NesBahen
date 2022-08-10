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

/*
* Gets the Tile starting at addr
*/
PPU::Tile PPU::construct_tile(uint16_t addr)
{
    Tile tile;
    // get least sig. bitmap
    for (int i = addr; i < addr + bitmap_size; i++){
        tile.lsbm[i - addr] = read(i);
    }
    // get most sig. bitmap
    for (int i = addr + bitmap_size; i < addr + bitmap_size * 2; i++){
        tile.msbm[i - (addr + bitmap_size)] = read(i);
    }
    //construct tile from msbm and lsbm
    uint8_t low_bit;
    uint8_t high_bit;
    // goes from top to bottom, right to left
    for (int i = 0; i < bitmap_size; i++){
        for (int j = 0; j < bitmap_size; j++){
            low_bit = (tile.lsbm[i] & (1 << j)) >> j;
            high_bit = (tile.msbm[i] & (1 << j)) >> j;
            tile.pixel_pattern[bitmap_size - j - 1][i] = low_bit + (high_bit * 2);
        }
    }
    return tile;
}

/**
 * @brief Gets all the tile memory and saves it 
 * 
 */
void PPU::construct_pattern_memory()
{
    int tile_count = 0; 
    for (int addr = 0; addr < 0x2000; addr += 0x10){
        tiles[tile_count] = construct_tile(addr);
        tile_count++;
    }
}