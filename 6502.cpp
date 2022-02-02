#include "6502.h"

Nes6502::Nes6502()
{   
    for (int i = 0; i < (int)table.size(); i++) {
        table[i] = {"RIP", "BAD", &RIP, &BAD, 5};
    }
}

Nes6502::~Nes6502()
{   
}

void Nes6502::emulate_cycle() 
{
    // Cycles = 0 indicates a new opcode is to be called
    // That function is called and the cycles is set accordingly
    // emulate_cycle is called the appropriate amount of times 
    // until cycles is 0 again, indicating the current opcode is done 
    // and the new opcode is to be executed
    // Termination of the program depends on what opcode is called
    if (cycles == 0){
        opcode = read(pc);
        pc++;
        
        cycles += table[opcode].cycles;
        
        int extra_cycles = (this->*table[opcode].addrmode)();
        int need_extra = (this->*table[opcode].operation)();
        
        cycles += need_extra & extra_cycles;
    }
    cycles--;
}

void Nes6502::connect_bus(Bus* b)
{
    bus = b;
}

void Nes6502::write(uint16_t addr, uint8_t data)
{
    bus->write(addr, data);
}

uint8_t Nes6502::read(uint16_t addr)
{
    return bus->read(addr);
}

void Nes6502::fetch()
{
    operand = bus->fetch(this->addr);
}
void Nes6502::fetch_indirect()
{
    operand = bus->fetch(this->addr_indirect);
}

void Nes6502::set_c(uint8_t n)
{
    flags = (flags & 0b11111110) | (n << 0);
}
void Nes6502::set_z(uint8_t n)
{
    flags = (flags & 0b11111101) | (n << 1);
}
void Nes6502::set_i(uint8_t n)
{
    flags = (flags & 0b11111011) | (n << 2);
}
void Nes6502::set_b(uint8_t n)
{
    flags = (flags & 0b11101111) | (n << 4);
}
void Nes6502::set_o(uint8_t n)
{
    flags = (flags & 0b10111111) | (n << 6);
}
void Nes6502::set_n(uint8_t n)
{
    flags = (flags & 0b01111111) | (n << 7);
}

uint8_t Nes6502::get_c()
{
    return (flags & 0b00000001) >> 0;
}
uint8_t Nes6502::get_z()
{
    return (flags & 0b00000010) >> 1;
}
uint8_t Nes6502::get_i()
{
    return (flags & 0b00000100) >> 2;
}
uint8_t Nes6502::get_b()
{
    return (flags & 0b00010000) >> 4;
}
uint8_t Nes6502::get_o()
{
    return (flags & 0b01000000) >> 6;
}
uint8_t Nes6502::get_n()
{
    return (flags & 0b10000000) >> 7;
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
    uint8_t temp_a = a;
    uint16_t temp_ans = a + *operand + get_c();
    a += *operand + get_c();
    set_c(temp_ans > 0xff);
    set_z(a == 0);
    set_o(((temp_a ^ a) & (temp_a ^ *operand)) == 1);
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


// Functions for unused operations
int Nes6502::BAD()
{
    return 0;
}
int Nes6502::RIP()
{
    return 0;
}