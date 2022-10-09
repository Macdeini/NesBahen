#include "cartridge.h"
#include <fstream>
#include <iostream>

void Cartridge::dump_rom()
{
    std::ifstream file("roms/donkeykong.nes", std::ios::binary);
    dump = std::vector<uint8_t>((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
    file.close();
}

void Cartridge::print_rom()
{
    for (int i = 0; i < dump.size(); i++) {
        if (i % 16 == 0)
            std::cout << std::endl;
        std::cout << std::hex << (int)dump[i] << " ";
    }
}

Cartridge::Cartridge()
{
    
    for(auto &i : prg_rom)
        i = 0x00;
    for(auto &i : chr_rom)
        i = 0x00;
    for(auto &i : prg_ram)
        i = 0x00;

    dump_rom();

    bank_num = dump[4];
    vrom_num = dump[5];
    control_byte_1 = dump[6];
    control_byte_2 = dump[7];
    ram_num = dump[8];

    if (control_byte_1 >> 7) {
        mirroring = VERTICAL;
    } else {
        mirroring = HORIZONTAL;
    }
    if ((control_byte_1 >> 3) & 0b00000001){
        mirroring = Four_Screen;
    }
    // add code for determining mapper
    // and for detecting TRAINER

    // For now we're only going to worry about supporting 40 KiB games and 20 KiB games
    int offset = 16;

    if (bank_num == 2) {
        for (offset; offset < 0x8000 + 16; offset++) {
            prg_rom[offset - 16] = dump[offset];
        }
        for (offset; offset < 0x8000 + 16 + 0x2000; offset++) {
            chr_rom[offset - 0x8000 - 16] = dump[offset];
        }
    } else {
        for (offset; offset < 0x4000 + 16; offset++) {
            prg_rom[offset - 16] = dump[offset];
            prg_rom[offset - 16 + 0x4000] = dump[offset];
        }
        for (offset; offset < 0x4000 + 16 + 0x2000; offset++) { // me when
            chr_rom[offset - 0x4000 - 16] = dump[offset]; 
        }
    }
}

uint8_t Cartridge::read_prg(uint16_t addr)
{
    if (addr < 0 || addr >= 0x8000)
        return 0;
    if (bank_num == 2)
        return prg_rom[addr];
    if (bank_num == 1)
        return prg_rom[addr & 0x3fff]; // mirroring for smaller bank size
    return 0;
}
void Cartridge::write_prg(uint16_t addr, uint8_t data)
{
    if (addr < 0 || addr >= 0x8000)
        return;       
    if (bank_num == 2)
        prg_rom[addr] = data;
    if (bank_num == 1)
        prg_rom[addr & 0x3fff] = data;  // mirroring for smaller bank size
}
uint8_t* Cartridge::fetch(uint16_t addr)
{
    if (addr < 0 || addr >= 0x8000)
        return nullptr;
    if (bank_num == 2)
        return &prg_rom[addr];
    if (bank_num == 1)
        return &prg_rom[addr & 0x3fff]; // mirroring for smaller bank size
    return nullptr;
}

uint8_t Cartridge::read_chr(uint16_t addr)
{
    if (0 <= addr && addr <= 0x1fff){
        return chr_rom[addr];
    }
    return 0;
}
void Cartridge::write_chr(uint16_t addr, uint8_t data)
{
    if (0 <= addr && addr <= 0x1fff)
        chr_rom[addr] = data;
    return;
}

Cartridge::~Cartridge()
{
}