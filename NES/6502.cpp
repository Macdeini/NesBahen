#include "6502.h"

Nes6502::Nes6502()
{   
    for (auto &i : table) {
        i = {"RIP", "BAD", &RIP, &BAD, 5};
    }
    table[0x00] = {"BRK", "IMM", &BRK, &IMM, 7};
    table[0x01] = {"ORA", "IDX", &ORA, &IDX, 6};
    table[0x05] = {"ORA", "ZPA", &ORA, &ZPA, 3};
    table[0x06] = {"ASL", "ZPA", &ASL, &ZPA, 5};
    table[0x08] = {"PHP", "IMP", &PHP, &IMP, 3};
    table[0x09] = {"ORA", "IMM", &ORA, &IMM, 2};
    table[0x0A] = {"ASL", "ACC", &ASL, &ACC, 2};
    table[0x0D] = {"ORA", "ABS", &ORA, &ABS, 4};
    table[0x0E] = {"ASL", "ABS", &ASL, &ABS, 6};

    table[0x10] = {"BPL", "REL", &BPL, &REL, 2};
    table[0x11] = {"ORA", "IDY", &ORA, &IDY, 5};
    table[0x15] = {"ORA", "ZPX", &ORA, &ZPX, 4};
    table[0x16] = {"ASL", "ZPX", &ASL, &ZPX, 6};
    table[0x18] = {"CLC", "IMP", &CLC, &IMP, 2};
    table[0x19] = {"ORA", "ABY", &ORA, &ABY, 4};
    table[0x1D] = {"ORA", "ABX", &ORA, &ABX, 4};
    table[0x1E] = {"ASL", "ABX", &ASL, &ABX, 7};

    table[0x20] = {"JSR", "ABS", &JSR, &ABS, 6};
    table[0x21] = {"AND", "IDX", &AND, &IDX, 6};
    table[0x24] = {"BIT", "ZPA", &BIT, &ZPA, 3};
    table[0x25] = {"AND", "ZPA", &AND, &ZPA, 3};
    table[0x26] = {"ROL", "ZPA", &ROL, &ZPA, 5};
    table[0x28] = {"PLP", "IMP", &PLP, &IMP, 4};
    table[0x29] = {"AND", "IMM", &AND, &IMM, 2};
    table[0x2A] = {"ROL", "ACC", &ROL, &ACC, 2};
    table[0x2C] = {"BIT", "ABS", &BIT, &ABS, 4};
    table[0x2D] = {"AND", "ABS", &AND, &ABS, 4};
    table[0x2E] = {"ROL", "ABS", &ROL, &ABS, 6};

    table[0x30] = {"BMI", "REL", &BMI, &REL, 2};
    table[0x31] = {"AND", "IDY", &AND, &IDY, 5};
    table[0x35] = {"AND", "ZPX", &AND, &ZPX, 4};
    table[0x36] = {"ROL", "ZPX", &ROL, &ZPX, 6};
    table[0x38] = {"SEC", "IMP", &SEC, &IMP, 2};
    table[0x39] = {"AND", "ABY", &AND, &ABY, 4};
    table[0x3D] = {"AND", "ABX", &AND, &ABX, 4};
    table[0x3E] = {"ROL", "ABX", &ROL, &ABX, 7};

    table[0x40] = {"RTI", "IMP", &RTI, &IMP, 6};
    table[0x41] = {"EOR", "IDX", &EOR, &IDX, 6};
    table[0x45] = {"EOR", "ZPA", &EOR, &ZPA, 3};
    table[0x46] = {"LSR", "ZPA", &LSR, &ZPA, 5};
    table[0x48] = {"PHA", "IMP", &PHA, &IMP, 3};
    table[0x49] = {"EOR", "IMM", &EOR, &IMM, 2};
    table[0x4A] = {"LSR", "ACC", &LSR, &ACC, 2};
    table[0x4C] = {"JMP", "ABS", &JMP, &ABS, 3};
    table[0x4D] = {"EOR", "ABS", &EOR, &ABS, 4};
    table[0x4E] = {"LSR", "ABS", &LSR, &ABS, 6};
    
    table[0x50] = {"BVC", "REL", &BVC, &REL, 2};
    table[0x51] = {"EOR", "IDY", &EOR, &IDY, 5};
    table[0x55] = {"EOR", "ZPX", &EOR, &ZPX, 4};
    table[0x56] = {"LSR", "ZPX", &LSR, &ZPX, 6};
    table[0x58] = {"CLI", "IMP", &CLI, &IMP, 2};
    table[0x59] = {"EOR", "ABY", &EOR, &ABY, 4};
    table[0x5D] = {"EOR", "ABX", &EOR, &ABX, 4};
    table[0x5E] = {"LSR", "ABX", &LSR, &ABX, 7};

    table[0x60] = {"RTS", "IMP", &RTS, &IMP, 6};
    table[0x61] = {"ADC", "IDX", &ADC, &IDX, 6};
    table[0x65] = {"ADC", "ZPA", &ADC, &ZPA, 3};
    table[0x66] = {"ROR", "ZPA", &ROR, &ZPA, 5};
    table[0x68] = {"PLA", "IMP", &PLA, &IMP, 4};
    table[0x69] = {"ADC", "IMM", &ADC, &IMM, 2};
    table[0x6A] = {"ROR", "ACC", &ROR, &ACC, 2};
    table[0x6C] = {"JMP", "IND", &JMP, &IND, 5};
    table[0x6D] = {"ADC", "ABS", &ADC, &ABS, 4};
    table[0x6E] = {"ROR", "ABS", &ROR, &ABS, 6};
    
    table[0x70] = {"BVS", "REL", &BVS, &REL, 2};
    table[0x71] = {"ADC", "IDY", &ADC, &IDY, 5};
    table[0x75] = {"ADC", "ZPX", &ADC, &ZPX, 4};
    table[0x76] = {"ROR", "ZPX", &ROR, &ZPX, 6};
    table[0x78] = {"SEI", "IMP", &SEI, &IMP, 2};
    table[0x79] = {"ADC", "ABY", &ADC, &ABY, 4};
    table[0x7D] = {"ADC", "ABX", &ADC, &ABX, 4};
    table[0x7E] = {"ROR", "ABX", &ROR, &ABX, 7};

    table[0x81] = {"STA", "IDX", &STA, &IDX, 6};
    table[0x84] = {"STY", "ZPA", &STY, &ZPA, 3};
    table[0x85] = {"STA", "ZPA", &STA, &ZPA, 3};
    table[0x86] = {"STX", "ZPA", &STX, &ZPA, 3};
    table[0x88] = {"DEY", "IMP", &DEY, &IMP, 2};
    table[0x8A] = {"TXA", "IMP", &TXA, &IMP, 2};
    table[0x8C] = {"STY", "ABS", &STY, &ABS, 4};
    table[0x8D] = {"STA", "ABS", &STA, &ABS, 4};
    table[0x8E] = {"STX", "ABS", &STX, &ABS, 4};

    table[0x90] = {"BCC", "REL", &BCC, &REL, 2};
    table[0x91] = {"STA", "IDY", &STA, &IDY, 6};
    table[0x94] = {"STY", "ZPX", &STY, &ZPX, 4};
    table[0x95] = {"STA", "ZPX", &STA, &ZPX, 4};
    table[0x96] = {"STX", "ZPY", &STX, &ZPY, 4};
    table[0x98] = {"TYA", "IMP", &TYA, &IMP, 2};
    table[0x99] = {"STA", "ABY", &STA, &ABY, 5};
    table[0x9A] = {"TXS", "IMP", &TXS, &IMP, 2};
    table[0x9D] = {"STA", "ABX", &STA, &ABX, 5};

    table[0xA0] = {"LDY", "IMM", &LDY, &IMM, 2};
    table[0xA1] = {"LDA", "IDX", &LDA, &IDX, 6};
    table[0xA2] = {"LDX", "IMM", &LDX, &IMM, 2};
    table[0xA4] = {"LDY", "ZPA", &LDY, &ZPA, 3};
    table[0xA5] = {"LDA", "ZPA", &LDA, &ZPA, 3};
    table[0xA6] = {"LDX", "ZPA", &LDX, &ZPA, 3};
    table[0xA8] = {"TAY", "IMP", &TAY, &IMP, 2};
    table[0xA9] = {"LDA", "IMM", &LDA, &IMM, 2};
    table[0xAA] = {"TAX", "IMP", &TAX, &IMP, 2};
    table[0xAC] = {"LDY", "ABS", &LDY, &ABS, 4};
    table[0xAD] = {"LDA", "ABS", &LDA, &ABS, 4};
    table[0xAE] = {"LDX", "ABS", &LDX, &ABS, 4};

    table[0xB0] = {"BCS", "REL", &BCS, &REL, 2};
    table[0xB1] = {"LDA", "IDY", &LDA, &IDY, 5};
    table[0xB4] = {"LDY", "ZPX", &LDY, &ZPX, 4};
    table[0xB5] = {"LDA", "ZPX", &LDA, &ZPX, 4};
    table[0xB6] = {"LDX", "ZPY", &LDX, &ZPY, 4};
    table[0xB8] = {"CLV", "IMP", &CLV, &IMP, 2};
    table[0xB9] = {"LDA", "ABY", &LDA, &ABY, 4};
    table[0xBA] = {"TSX", "IMP", &TSX, &IMP, 2};
    table[0xBC] = {"LDY", "ABX", &LDY, &ABX, 4};
    table[0xBD] = {"LDA", "ABX", &LDA, &ABX, 4};
    table[0xBE] = {"LDX", "ABY", &LDX, &ABY, 4};

    table[0xC0] = {"CPY", "IMM", &CPY, &IMM, 2};
    table[0xC1] = {"CMP", "IDX", &CMP, &IDX, 6};
    table[0xC4] = {"CPY", "ZPA", &CPY, &ZPA, 3};
    table[0xC5] = {"CMP", "ZPA", &CMP, &ZPA, 3};
    table[0xC6] = {"DEC", "ZPA", &DEC, &ZPA, 5};
    table[0xC8] = {"INY", "IMP", &INY, &IMP, 2};
    table[0xC9] = {"CMP", "IMM", &CMP, &IMM, 2};
    table[0xCA] = {"DEX", "IMP", &DEX, &IMP, 2};
    table[0xCC] = {"CPY", "ABS", &CPY, &ABS, 4};
    table[0xCD] = {"CMP", "ABS", &CMP, &ABS, 4};
    table[0xCE] = {"DEC", "ABS", &DEC, &ABS, 6};

    table[0xD0] = {"BNE", "REL", &BNE, &REL, 2};
    table[0xD1] = {"CMP", "IDY", &CMP, &IDY, 5};
    table[0xD5] = {"CMP", "ZPX", &CMP, &ZPX, 4};
    table[0xD6] = {"DEC", "ZPX", &DEC, &ZPX, 6};
    table[0xD8] = {"CLD", "IMP", &CLD, &IMP, 2};
    table[0xD9] = {"CMP", "ABY", &CMP, &ABY, 4};
    table[0xDD] = {"CMP", "ABX", &CMP, &ABX, 4};
    table[0xDE] = {"DEC", "ABX", &DEC, &ABX, 7};

    table[0xE0] = {"CPX", "IMM", &CPX, &IMM, 2};
    table[0xE1] = {"SBC", "IDX", &SBC, &IDX, 6};
    table[0xE4] = {"CPX", "ZPA", &CPX, &ZPA, 3};
    table[0xE5] = {"SBC", "ZPA", &SBC, &ZPA, 3};
    table[0xE6] = {"INC", "ZPA", &INC, &ZPA, 5};
    table[0xE8] = {"INX", "IMP", &INX, &IMP, 2};
    table[0xE9] = {"SBC", "IMM", &SBC, &IMM, 2};
    table[0xEA] = {"NOP", "IMP", &NOP, &IMP, 2};
    table[0xEC] = {"CPX", "ABS", &CPX, &ABS, 4};
    table[0xED] = {"SBC", "ABS", &SBC, &ABS, 4};
    table[0xEE] = {"INC", "ABS", &INC, &ABS, 6};

    table[0xF0] = {"BEQ", "REL", &BEQ, &REL, 2};
    table[0xF1] = {"SBC", "IDY", &SBC, &IDY, 5};
    table[0xF5] = {"SBC", "ZPX", &SBC, &ZPX, 4};
    table[0xF6] = {"INC", "ZPX", &INC, &ZPX, 6};
    table[0xF8] = {"SED", "IMP", &SED, &IMP, 2};
    table[0xF9] = {"SBC", "ABY", &SBC, &ABY, 4};
    table[0xFD] = {"SBC", "ABX", &SBC, &ABX, 4};
    table[0xFE] = {"INC", "ABX", &INC, &ABX, 7};
}

Nes6502::~Nes6502()
{   
}

void Nes6502::emulate_cycle() 
{
    if (cycles == 0){
        opcode = read(pc);
        // print_status();

        pc++;
        cycles += table[opcode].cycles;
        int extra_cycles = (this->*table[opcode].addrmode)();
        int need_extra = (this->*table[opcode].operation)();
    
        cycles += need_extra & extra_cycles;
        total_cycles += cycles;
    }
    cycles--;
}

void Nes6502::print_status()
{
    std::cout << std::hex << std::setfill('0') << std::setw(4) << int(pc) << "  ";
    std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)read(pc) << " ";
    std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)read(pc+1) << " ";
    std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)read(pc+2) << "  "; 
    std::cout << "  " << table[opcode].opcode_name << " " << table[opcode].addrmode_name;
    std::cout << "                ";
    std::cout << "A:" << std::hex << std::setfill('0') << std::setw(2) << int(a) << " ";
    std::cout << "X:" << std::hex << std::setfill('0') << std::setw(2) << int(x) << " ";
    std::cout << "Y:" << std::hex << std::setfill('0') << std::setw(2) << int(y) << " ";
    std::cout << "P:" << std::hex << std::setfill('0') << std::setw(2) << int(status) << " ";
    std::cout << "SP:" << std::hex << std::setfill('0') << std::setw(2) << int(sp) << " ";
    std::cout << "CYC:" << std::dec << int(total_cycles) << " " << std::endl;
}

/*
* Helper functions
*/
// Interactions with bus
void Nes6502::connect_bus(Bus* b)
{
    bus = b;
}

void Nes6502::write(uint16_t addr, uint8_t data)
{
    bus->cpu_write(addr, data);
}

uint8_t Nes6502::read(uint16_t addr)
{
    return bus->cpu_read(addr);
}

void Nes6502::fetch()
{
    operand = bus->fetch(this->addr);
}
void Nes6502::fetch_indirect()
{
    operand = bus->fetch(this->addr_indirect);
}

// Flag setters: n is 0 or 1 
void Nes6502::set_c(uint8_t n)
{
    status = (status & 0b11111110) | (n << 0);
}
void Nes6502::set_z(uint8_t n)
{
    status = (status & 0b11111101) | (n << 1);
}
void Nes6502::set_i(uint8_t n)
{
    status = (status & 0b11111011) | (n << 2);
}
void Nes6502::set_b(uint8_t n)
{
    status = (status & 0b11101111) | (n << 4);
}
void Nes6502::set_v(uint8_t n)
{
    status = (status & 0b10111111) | (n << 6);
}
void Nes6502::set_n(uint8_t n)
{
    status = (status & 0b01111111) | (n << 7);
}
void Nes6502::set_d(uint8_t n)
{
    status = (status & 0b11110111) | (n << 3);
}
void Nes6502::set_u(uint8_t n)
{
    status = (status & 0b11011111) | (n << 5);
}

// Flag getters
uint8_t Nes6502::get_c()
{
    return (status & 0b00000001) >> 0;
}
uint8_t Nes6502::get_z()
{
    return (status & 0b00000010) >> 1;
}
uint8_t Nes6502::get_i()
{
    return (status & 0b00000100) >> 2;
}
uint8_t Nes6502::get_b()
{
    return (status & 0b00010000) >> 4;
}
uint8_t Nes6502::get_v()
{
    return (status & 0b01000000) >> 6;
}
uint8_t Nes6502::get_n()
{
    return (status & 0b10000000) >> 7;
}

// stack helpers
void Nes6502::s_push(uint8_t data)
{
    write(s_offset + sp, data);
    sp--;
}
uint8_t Nes6502::s_pop()
{
    sp++;
    uint8_t data = read(s_offset + sp);
    return data;
}

/*
* Addressing modes 
*/
int Nes6502::ACC() 
{
    operand = &a;
    return 0;
}

int Nes6502::IMM()
{
    temp = read(pc);
    pc++;
    operand = &temp;
    return 0;
}

int Nes6502::ABS()
{
    addr_low = read(pc);
    pc++;
    addr_high = read(pc);
    pc++;
    addr = (addr_high << 8) | addr_low;
    jumpaddr = addr;
    fetch();
    return 0;
}

int Nes6502::ZPA()
{
    addr = read(pc);
    pc++;
    fetch();
    return 0;
}

int Nes6502::ZPX()
{
    addr = (read(pc) + x) & 0xff;
    pc++ ;
    fetch();
    return 0;
}

int Nes6502::ZPY()
{    
    addr = (read(pc) + y) & 0xff;
    pc++ ;
    fetch();
    return 0;
}

int Nes6502::ABX()
{
    addr_low = read(pc);
    pc++;
    addr_high = read(pc);
    pc++;
    uint16_t addr_before = ((addr_high << 8) | addr_low);
    addr = ((addr_high << 8) | addr_low) + x;
    fetch();
    if ((addr & 0xff00) - (addr_before & 0xff00) != 0)
        return 1;
    return 0;
}

int Nes6502::ABY()
{    
    addr_low = read(pc);
    pc++;
    addr_high = read(pc);
    pc++;
    uint16_t addr_before = ((addr_high << 8) | addr_low);
    addr = ((addr_high << 8) | addr_low) + y;
    fetch();
    if ((addr & 0xff00) - (addr_before & 0xff00) != 0)
        return 1;
    return 0;
}

// opcodes that use IMP only use IMP 
// can handle data retrieval in those opcodes
int Nes6502::IMP()
{
    return 0;
}

// Because we need to check the condition of the branch
// to determine whether or not to edit pc and 
// add extra clock cycles, we'll leave all that to the 
// opcode functions themselves. All REL does is get the 
// offset and saves it internally.
int Nes6502::REL()
{
    offset = read(pc);
    pc++;
    return 1;
}

int Nes6502::IND()
{
    addr_low = read(pc);
    pc++;
    addr_high = read(pc);
    pc++;
    addr = (addr_high << 8) | addr_low;
    addr_indirect = (read(addr + 1) << 8) | read(addr);
    fetch_indirect();
    return 0;
}

int Nes6502::IDX() 
{
    addr = (read(pc) + x) & 0xff;
    pc++;
    addr_indirect = (read(addr + 1) << 8) | read(addr);
    fetch_indirect();
    return 0;
}

int Nes6502::IDY() 
{
    addr = read(pc);
    pc++;
    addr_indirect = (read(addr + 1) << 8) | read(addr);
    uint16_t addr_indirect_before = addr_indirect;
    addr_indirect += y;
    fetch_indirect();
    if ((addr_indirect & 0xff00) - (addr_indirect_before & 0xff00) != 0)
        return 1;
    return 0;
}

/*
* Opcodes
*/
int Nes6502::ADC()
{
    uint16_t ans = a + *operand + get_c(); 
    uint8_t msba = a >> 7;
    uint8_t msbr = (ans & 0xff) >> 7;
    uint8_t msbm = *operand >> 7;
    set_v((msba ^ msbr) & (~(msba ^ msbm)));
    a = ans & 0xff;
    set_c(ans > 0xff);
    set_z(a == 0);
    set_n((a >> 7 == 1));
    return 1;
}
int Nes6502::AND()
{   
    a &= *operand;
    set_z(a == 0);
    set_n((a >> 7 == 1));
    return 1;
}
int Nes6502::ASL()
{
    set_c((*operand >> 7)== 1);
    *operand = *operand << 1;
    set_n((*operand >> 7)== 1);
    set_z(*operand == 0);
    return 0;
}
int Nes6502::BCC()
{
    if (get_c() == 0){
        uint16_t old_pc = pc;
        pc += offset;
        if ((pc & 0xff00) - (old_pc & 0xff00) != 0) {
            return 2;
        }
        return 1;
    } else {
        return 0;
    }
}
int Nes6502::BCS()
{
    if (get_c() == 1){
        uint16_t old_pc = pc;
        pc += offset;
        if ((pc & 0xff00) - (old_pc & 0xff00) != 0) {
            return 2;
        }
        return 1;
    } else {
        return 0;
    }
}
int Nes6502::BEQ()
{
    if (get_z() == 1){
        uint16_t old_pc = pc;
        pc += offset;
        if ((pc & 0xff00) - (old_pc & 0xff00) != 0) {
            return 2;
        }
        return 1;
    } else {
        return 0;
    }
}
int Nes6502::BIT()
{   
    set_z((a & *operand) == 0);
    set_v((*operand >> 6) & 0b01);
    set_n(*operand >> 7);
    return 0;
}
int Nes6502::BMI()
{
    if (get_n() == 1){
        uint16_t old_pc = pc;
        pc += offset;
        if ((pc & 0xff00) - (old_pc & 0xff00) != 0) {
            return 2;
        }
        return 1;
    } else {
        return 0;
    }
}
int Nes6502::BNE()
{
    if (get_z() == 0){
        uint16_t old_pc = pc;
        pc += offset;
        if ((pc & 0xff00) - (old_pc & 0xff00) != 0) {
            return 2;
        }
        return 1;
    } else {
        return 0;
    }
}
int Nes6502::BPL()
{
    if (get_n() == 0){
        uint16_t old_pc = pc;
        pc += offset;
        if ((pc & 0xff00) - (old_pc & 0xff00) != 0) {
            return 2;
        }
        return 1;
    } else {
        return 0;
    }
}
int Nes6502::BRK()
{
    pc++;
    s_push(pc >> 8);
    s_push(pc & 0x00ff);
    uint8_t temp = status;
    set_b(1);
    // set_u(1);
    s_push(status);
    status = temp;
    pc = (read(0xffff) << 8) | read(0xfffe);
    return 0;
}
int Nes6502::BVC()
{
    if (get_v() == 0){
        uint16_t old_pc = pc;
        pc += offset;
        if ((pc & 0xff00) - (old_pc & 0xff00) != 0) {
            return 2;
        }
        return 1;
    } else {
        return 0;
    }
}
int Nes6502::BVS()
{
    if (get_v() == 1){
        uint16_t old_pc = pc;
        pc += offset;
        if ((pc & 0xff00) - (old_pc & 0xff00) != 0) {
            return 2;
        }
        return 1;
    } else {
        return 0;
    }
}
int Nes6502::CLC()
{
    set_c(0);
    return 0;
}
int Nes6502::CLD()
{
    set_d(0);
    return 0;
}
int Nes6502::CLI()
{
    set_i(0);
    return 0;
}
int Nes6502::CLV()
{
    set_v(0);
    return 0;
}
int Nes6502::CMP()
{
    set_c(a >= *operand);
    set_z(a == *operand);
    set_n(((a - *operand) >> 7) != 0);
    return 1;
}
int Nes6502::CPX()
{
    set_c(x >= *operand);
    set_z(x == *operand);
    set_n(((x - *operand) >> 7) != 0);
    return 0;
}
int Nes6502::CPY()
{
    set_c(y >= *operand);
    set_z(y == *operand);
    set_n(((y - *operand) >> 7) != 0);
    return 0;
}
int Nes6502::DEC()
{
    *operand -= 1;
    set_z(*operand == 0);
    set_n((*operand >> 7) == 1);
    return 0;
}
int Nes6502::DEX()
{
    x -= 1;
    set_z(x == 0);
    set_n((x >> 7) == 1);
    return 0;
}
int Nes6502::DEY()
{
    y -= 1;
    set_z(y == 0);
    set_n((y >> 7) == 1);
    return 0;
}
int Nes6502::EOR()
{
    a = a ^ *operand;
    set_z(a == 0);
    set_n((a >> 7) == 1);
    return 1;
}
int Nes6502::INC()
{
    *operand += 1;
    set_z(*operand == 0);
    set_n((*operand >> 7) == 1);
    return 0;
}
int Nes6502::INX()
{
    x += 1;
    set_z(x == 0);
    set_n((x >> 7) == 1);
    return 0;
}
int Nes6502::INY()
{
    y += 1;
    set_z(y == 0);
    set_n((y >> 7) == 1);
    return 0;
}
int Nes6502::JMP()
{   
    pc = addr;
    return 0;
}
// Might be finicky with how im pushing pc
// Online sources say push pc - 1 but that doesnt make sense to me 
// With how I'm doing it pc is going to point to the next instruction byte after jmp addrlow addrhigh
// by the time we reach here. We save pc, jmp and go do something else,
// and then return to the byte of the next instruction
int Nes6502::JSR()
{
    s_push(pc >> 8); // high
    s_push(pc & 0xff); // low 
    pc = jumpaddr;
    return 0;
}
int Nes6502::LDA()
{
    a = *operand;
    set_z(a == 0);
    set_n((a >> 7) == 1);
    return 1;
}
int Nes6502::LDX()
{
    x = *operand;
    set_z(x == 0);
    set_n((x >> 7) == 1);
    return 1;
}
int Nes6502::LDY()
{
    y = *operand;
    set_z(y == 0);
    set_n((y >> 7) == 1);
    return 1;
}
int Nes6502::LSR()
{
    set_c((*operand >> 7)== 1);
    *operand = *operand >> 1;
    set_n((*operand >> 7)== 1);
    set_z(*operand == 0);
    return 0;
}
int Nes6502::NOP()
{
    return 0;
}
int Nes6502::ORA()
{
    a = a | *operand;
    set_z(a == 0);
    set_n((a >> 7) == 1);
    return 1;
}
int Nes6502::PHA()
{
    s_push(a);
    return 0;
}
int Nes6502::PHP()
{
    uint8_t temp = status;
    set_b(1);
    // set_u(1);
    s_push(status);
    status = temp;
    return 0;
}
int Nes6502::PLA()
{
    a = s_pop();
    set_z(a == 0);
    set_n((a >> 7) == 1);
    return 0;
}
int Nes6502::PLP()
{
    status = s_pop();
    set_b(0);
    set_u(1);
    return 0;
}
int Nes6502::ROL()
{
    int temp = get_c();
    set_c(*operand >> 7);
    *operand = *operand << 1;
    *operand = *operand & 0b11111110;
    *operand = *operand | temp;
    return 0;
}
int Nes6502::ROR()
{
    int temp = get_c();
    set_c(*operand & 0b00000001);
    *operand = *operand >> 1;
    *operand = *operand & 0b01111111;
    *operand = *operand | (temp << 7);
    return 0;
}
int Nes6502::RTI()
{
    status = s_pop();
    set_b(0);
    set_u(1);
    int low = s_pop();
    int high = s_pop();
    pc = (high << 8) | low;
    return 0;
}
int Nes6502::RTS()
{
    int lo = s_pop();
    int hi = s_pop();
    pc = (hi << 8) | lo;
    return 0;
}
int Nes6502::SBC()
{
    //uint16_t negative_m = *operand ^ 0x00ff;   // getting two's complement (the +1 is implicit)
    uint16_t new_a = a - *operand - (1 - get_c());
    uint8_t msba = a >> 7;
    uint8_t msbr = (new_a & 0xff) >> 7;
    uint8_t msbm = (*operand ^ 0xff) >> 7;
    set_v((msba ^ msbr) & (~(msba ^ msbm)));
    a = new_a;
    set_c(!(new_a > 0xff));
    set_z(a == 0);
    set_n((a >> 7) != 0);
    return 1;
}
int Nes6502::SEC()
{
    set_c(1);
    return 0; 
}
int Nes6502::SED()
{
    set_d(1);
    return 0;
}
int Nes6502::SEI()
{
    set_i(1);
    return 0;
}
int Nes6502::STA()
{
    *operand = a;
    return 0;
}
int Nes6502::STX()
{
    *operand = x;
    return 0;
}
int Nes6502::STY()
{
    *operand = y;
    return 0;
}
int Nes6502::TAX()
{
    x = a;
    set_z(x == 0);
    set_n((x >> 7) == 1);
    return 0;
}
int Nes6502::TAY()
{
    y = a;
    set_z(y == 0);
    set_n((y >> 7) == 1);
    return 0;
}
int Nes6502::TSX()
{
    x = sp;
    set_z(x == 0);
    set_n((x >> 7) == 1);
    return 0;
}
int Nes6502::TXA()
{
    a = x;
    set_z(a == 0);
    set_n(a >> 7);
    return 0;
}
int Nes6502::TXS()
{
    sp = x;
    return 0;
}
int Nes6502::TYA()
{
    a = y;
    set_z(a == 0);
    set_n(a >> 7);
    return 0;
}





// Functions for unused operations
int Nes6502::BAD()
{
    return 0;
}
int Nes6502::RIP()
{
    return 0;
}