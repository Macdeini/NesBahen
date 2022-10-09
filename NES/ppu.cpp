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
    if (0 <= addr && addr <= 0x1fff) { // read to chr rom on cartridge
        return bus->ppu_read(addr);
    }
    if (0x2000 <= addr && addr <= 0x2fff) { // read from nametable
        Mirroring mirroring = bus->get_nametable_mirroring();
        if (mirroring == VERTICAL) {  // $2000 equals $2800 and $2400 equals $2C00
            if (0x2000 <= addr && addr <= 0x23ff) { // map to first nametable [0-1023]
                int nametable_index = addr - 0x2000;
                return nametables[nametable_index];
            }
            else if (0x2400 <= addr && addr <= 0x27ff) { // map to second nametable [1024-2047]
                int nametable_index = addr - 0x2400 + 1024;
                return nametables[nametable_index];
            }
            else if (0x2800 <= addr && addr <= 0x2bff) { // map to first nametable [0-1023]
                int nametable_index = addr - 0x2800;
                return nametables[nametable_index];
            }
            else if (0x2c00 <= addr && addr <= 0x2fff) { // map to second nametable [1024-2047]
                int nametable_index = addr - 0x2c00 + 1024;
                return nametables[nametable_index];
            }
        } 
        else if (mirroring == HORIZONTAL) { // $2000 equals $2400 and $2800 equals $2C00 
            if (0x2000 <= addr && addr <= 0x23ff) { // map to first nametable [0-1023]
                int nametable_index = addr - 0x2000;
                return nametables[nametable_index];
            }
            else if (0x2400 <= addr && addr <= 0x27ff) { // map to first nametable [0-1023]
                int nametable_index = addr - 0x2400;
                return nametables[nametable_index];
            }
            else if (0x2800 <= addr && addr <= 0x2bff) { // map to second nametable [1024-2047]
                int nametable_index = addr - 0x2800 + 1024;
                return nametables[nametable_index];
            }
            else if (0x2c00 <= addr && addr <= 0x2fff) { // map to second nametable [1024-2047]
                int nametable_index = addr - 0x2c00 + 1024;
                return nametables[nametable_index];
            }
        }
    }
    return 0;
}
void PPU::write(uint16_t addr, uint8_t data)
{
    if (0 <= addr && addr <= 0x1fff) { // write to chr rom on cartridge
        bus->ppu_write(addr, data);
    }
    if (0x2000 <= addr && addr <= 0x2fff) { // write to nametable
        Mirroring mirroring = bus->get_nametable_mirroring();
        if (mirroring == VERTICAL) {  // $2000 equals $2800 and $2400 equals $2C00
            if (0x2000 <= addr && addr <= 0x23ff) { // map to first nametable [0-1023]
                int nametable_index = addr - 0x2000;
                nametables[nametable_index] = data;
            }
            else if (0x2400 <= addr && addr <= 0x27ff) { // map to second nametable [1024-2047]
                int nametable_index = addr - 0x2400 + 1024;
                nametables[nametable_index] = data;
            }
            else if (0x2800 <= addr && addr <= 0x2bff) { // map to first nametable [0-1023]
                int nametable_index = addr - 0x2800;
                nametables[nametable_index] = data;
            }
            else if (0x2c00 <= addr && addr <= 0x2fff) { // map to second nametable [1024-2047]
                int nametable_index = addr - 0x2c00 + 1024;
                nametables[nametable_index] = data;
            }
        } 
        else if (mirroring == HORIZONTAL) { // $2000 equals $2400 and $2800 equals $2C00 
            if (0x2000 <= addr && addr <= 0x23ff) { // map to first nametable [0-1023]
                int nametable_index = addr - 0x2000;
                nametables[nametable_index] = data;
            }
            else if (0x2400 <= addr && addr <= 0x27ff) { // map to first nametable [0-1023]
                int nametable_index = addr - 0x2400;
                nametables[nametable_index] = data;
            }
            else if (0x2800 <= addr && addr <= 0x2bff) { // map to second nametable [1024-2047]
                int nametable_index = addr - 0x2800 + 1024;
                nametables[nametable_index] = data;
            }
            else if (0x2c00 <= addr && addr <= 0x2fff) { // map to second nametable [1024-2047]
                int nametable_index = addr - 0x2c00 + 1024;
                nametables[nametable_index] = data;
            }
        }
    }
}

// read registers 
uint8_t PPU::read_PPU_STATUS() {
    return PPU_STATUS;
}

uint8_t PPU::read_OAM_DATA() {}

uint8_t PPU::read_PPU_DATA() {
    uint8_t result = read(PPU_ADDR);
    if ((PPU_CTRL >> 2) & 1 == 0) {
        PPU_ADDR += 1;
    } else {
        PPU_ADDR += 32;
    }
    return result;
}

// write registers
void PPU::write_PPU_CTRL(uint8_t data) {
    PPU_CTRL = data;
}

void PPU::write_PPU_MASK(uint8_t data) {
    PPU_MASK = data;
}

void PPU::write_OAM_ADDR(uint8_t data) {}

void PPU::write_OAM_DATA(uint8_t data) {}

void PPU::write_PPU_SCROLL(uint8_t data) {}

void PPU::write_PPU_ADDR(uint8_t data) {
    PPU_ADDR &= 0x3fff;
    if (ppu_addr_latch) { // write to high byte 
        PPU_ADDR = (PPU_ADDR & 0b0000000011111111) | (data << 8);
    } else { // write to low byte
        PPU_ADDR = (PPU_ADDR & 0b1111111100000000) | data;
    }
    ppu_addr_latch = !ppu_addr_latch;
}

void PPU::write_PPU_DATA(uint8_t data) {
    write(PPU_ADDR, data);
    if ((PPU_CTRL >> 2) & 1 == 0) {
        PPU_ADDR += 1;
    } else {
        PPU_ADDR += 32;
    }
}

void PPU::write_OAM_DMA(uint8_t data) {}

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
        pattern_tiles[tile_count] = construct_tile(addr);
        tile_count++;
    }
}