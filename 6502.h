#pragma once
#include <stdint.h>
#include <array>
#include <iostream>
#include <vector>
#include <string>
#include "bus.h"

/*
* 1) Read opcode byte at pc
* 2) Get addressing mode function and cycles of table[byte]
* 3) Read 0, 1, or 2 extra bytes
* 4) Execute opcode
* 5) Wait and count clock cycles until completion
*/

class Bus;

class Nes6502 
{
public:
    Nes6502();
    ~Nes6502();

    // Basic Components
    uint16_t pc = 0x0000;
    uint8_t sp = 0xff;
    uint8_t a = 0x00;
    uint8_t x = 0x00;
    uint8_t y = 0x00;
    int cycles = 0;

    // The address range $0100 and $01ff is designated for the stack
    // the stack pointer is only 1 byte so its automatically offset
    // i.e sp = 0x40 designates the address $0140
    // the stack pointer also starts at 0xff and decreases as items are pushed
    // pop is often reffered to as pull in 6502 documentation
    const uint16_t s_offset = 0x0100;
    void s_push(uint8_t data);
    uint8_t s_pop();

    // Flags related variables
    // From High to low: Negative Overflow Unused Break Decimal Interrupt Zero Carry
    // Decimal is unused 
    uint8_t status = 0b11111111;
    // These functions take in either 1 or 0 
    void set_c(uint8_t num); void set_z(uint8_t num);
    void set_i(uint8_t num); void set_b(uint8_t num); 
    void set_o(uint8_t num); void set_n(uint8_t num);  
    
    uint8_t get_c(); uint8_t get_z();
    uint8_t get_i(); uint8_t get_b(); 
    uint8_t get_o(); uint8_t get_n();  

    // 1 byte = 8 bits = 2 hex digits
    // used to store opcode byte
    uint8_t opcode = 0x00;
    // used to store second byte of instruction
    uint8_t addr_low = 0x00;
    // used to store third byte of instruction
    uint8_t addr_high = 0x00;
    // full 16 bit address used to index memory
    uint16_t addr = (addr_high << 8) | addr_low;
    // used only for indirect addressing
    uint16_t addr_indirect = 0x0000;
    // Used for branch instruction addressing
    int8_t offset = 0x00;

    // Addressing modes can either refer to data in memory via a hex number stored with the instruction
    // or by storing the value itself with the instruction. 
    // For example:
    // LDA $AA sets accum = ram[0x00AA] 
    // LDA $AAAA sets accum = ram[0xAAAA]
    // LDA #AA sets accum = 0xAA
    // The opcode function itself shouldn't worry about addressing,
    // it should be given its value to operate upon and not worry about anything more.
    // Thus the addressing function stores the value retrived in operand, and then the opcode function uses it later.
    // operand is a pointer because it will need to be able to edit values within memory.
    
    // Sometimes you want to edit ram contents so you have a reference to ram values 
    // Sometimes you want to edit registers so you need a reference to registers and edit them
    // Sometimes the value is written within the code so you set operand to that, but because of possible
    // pointer arithmetic mess ups you set the value to the temp variable and then have operand point to that.
    // For example: 
    // operand  = ram.fetch(addr)
    // then later
    // *operand = *operand << 1 
    
    // Temp is used to store values retrieved through immediate addressing without overwriting what operand points to.
    // For example:
    // ASL A shift accum left so operand points to cpu.a and shifts it left,
    // but then the cpu reads LDX #AA and goes to add AA to cpu.x. The addressing mode must store AA 
    // somewhere for the opcode function to later add to cpu.x, but where does it store it?
    // we can't do *operand = 0xAA because that would overwrite cpu.a which is not good. 
    // Thus we have to AA temporarily in temp and then have operand point to temp, to avoid
    // possibly overwiting anything important.
    uint8_t temp = 0x00;
    uint8_t* operand = &temp;
    // fetch is only used under the context of setting operand to a value in memory
    // helper function for addressing functions
    void fetch();
    void fetch_indirect();

    // Struct for instruction information
    struct Instruction {
        std::string opcode_name;
        std::string addrmode_name;
        int (Nes6502::*operation)() = nullptr;
        int (Nes6502::*addrmode)() = nullptr;
        int cycles = 0;
    };
    std::array<Instruction, 256> table;

    // Data bus for accessing ram and other components
    void connect_bus(Bus* bus);
    Bus* bus = nullptr;
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);

    // Addressing Modes:
    // Gets the information at the memory location in the designated fashion.
    // pc is increased as requried in the addressing mode functions
    // Depending on the addressing mode and opcode more cycles may be required from the machine than expected.
    // If they do they return the extra amount needed, 0 otherwise.
    // ABX ABY IDY REL can demand more cycles
    int ACC(); int IMP();
    int IMM(); int REL();
    int ABS(); int IDX();
    int ZPA(); int IDY();
    int ZPX(); int IND();
    int ZPY();
    int ABX();
    int ABY();

    int BAD(); // Placeholder for undefined opcode

    // Opcodes:
    // Returns 1 if more clock cycles can be needed, 0 otherwise.
    // Except for branch instructions which return the amount of extra cycles needed.
    // Returned result is multipled with addressing mode if more cycles are needed
    int ADC(); int AND(); int ASL(); int BCC(); 
    int BCS(); int BEQ(); int BIT(); int BMI(); 
    int BNE(); int BPL(); int BRK(); int BVC(); 
    int BVS(); int CLC(); int CLD(); int CLI(); 
    int CLV(); int CMP(); int CPX(); int CPY(); 
    int DEC(); int DEX(); int DEY(); int EOR(); 
    int INC(); int INX(); int INY(); int JMP();
    int JSR(); int LDA(); int LDX(); int LDY(); 
    int LSR(); int NOP(); int ORA(); int PHA(); 
    int PHP(); int PLA(); int PLP(); int ROL(); 
    int ROR(); int RTI(); int RTS(); int SBC(); 
    int SEC(); int SED(); int SEI(); int STA(); 
    int STX(); int STY(); int TAX(); int TAY(); 
    int TSX(); int TXA(); int TXS(); int TYA();

    int RIP(); // Placeholder for undefined

    void interrupt();
    void reset();
    void breakprg();

    // Cycles is incremented/decremented here
    void emulate_cycle();
    void print_instruction();
};