#pragma once
#include <cstdint>
#include <vector>
#include <array>

enum Mirroring {VERTICAL, HORIZONTAL, Four_Screen};

class Cartridge
{
public:
    Cartridge();
    ~Cartridge();

    // for now we'll only worry about mapper 0 
    uint8_t mapper = 0;
    
    void dump_rom();
    std::vector<uint8_t> dump;
    void print_rom();

    // For mapper 0 the only thing that varies in bank_num
    int bank_num = 0;
    int vrom_num = 0;
    int ram_num = 0;
    uint8_t control_byte_1 = 0x00;
    uint8_t control_byte_2 = 0x00;
    
    std::array<uint8_t, 0x8000> prg_rom;
    std::array<uint8_t, 0x2000> chr_rom;
    std::array<uint8_t, 0x0800> prg_ram;

    Mirroring mirroring;

    uint8_t read_prg(uint16_t addr);
    void write_prg(uint16_t addr, uint8_t data);
    uint8_t* fetch(uint16_t addr);

    uint8_t read_chr(uint16_t addr);
    void write_chr(uint16_t addr, uint8_t data);
};