#include <iostream>
// #define OLC_PGE_APPLICATION
// #include "olcPixelGameEngine.h"
#include <bitset>
#include "6502.h"
#include "bus.h"
#include <vector>

// class SnakeWindow : public olc::PixelGameEngine
// {
// public:
// 	SnakeWindow()
// 	{
// 		sAppName = "6502 Assembly Snake";
// 	}

// public:
// 	bool OnUserCreate() override
// 	{
// 		// Called once at the start, so create things here
// 		return true;
// 	}

// 	bool OnUserUpdate(float fElapsedTime) override
// 	{
// 		// called once per frame
// 		for (int x = 0; x < ScreenWidth(); x++)
// 			for (int y = 0; y < ScreenHeight(); y++)
// 				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));	
// 		return true;
// 	}
// };

int main(){
    // Machine code for a snake game

    Nes6502 cpu;
    Bus bus;
    cpu.connect_bus(&bus);
    bus.cpu = &cpu;

    std::vector<uint8_t> prog ={0xA2, 0x0A, 0x8E, 0x00, 0x00, 0xA2, 0x03, 0x8E, 0x01, 0x00, 0xAC, 0x00, 0x00, 0xA9, 0x00, 0x18, 
                                0x6D, 0x01, 0x00, 0x88, 0xD0, 0xFA, 0x8D, 0x02, 0x00, 0xEA ,0xEA, 0xEA};


    bus.write(0xfffc, 0x00);
    bus.write(0xfffd, 0x80);
    for (int i = 0; i < prog.size(); i++){
        bus.write(i+0x8000, prog[i]);
    }
    cpu.pc = 0x8000;

    while(true){
        cpu.emulate_cycle();
        if (cpu.pc <= 0x8000){
            break;
        }
    }

    std::cout << std::hex << (int)bus.read(0) << std::endl;
    std::cout << std::hex << (int)bus.read(1) << std::endl;
    std::cout << std::hex << (int)bus.read(2) << std::endl;

    return 0;
}
