#include <iostream>
#include "NES/6502.h"
#include "NES/bus.h"
#include "NES/cartridge.h"
#include "NES/ppu.h"

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 256

int main(int argc, char** argv){
    Nes6502 cpu;
    Bus bus;
    Cartridge cartridge;
    PPU ppu;
    ppu.connect_bus(&bus);
    cpu.connect_bus(&bus);
    bus.set_cpu(&cpu);
    bus.set_ppu(&ppu);
    bus.set_cartridge(&cartridge);
    ppu.construct_pattern_memory(); 

    std::array<int, 4> test_palettes = {{0x21, 0x06, 0x27, 0x0d}};


    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("PPU Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!window){
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, ppu.palettes[test_palettes[0]][0], ppu.palettes[test_palettes[0]][1], ppu.palettes[test_palettes[0]][2], 255);
    SDL_RenderClear(renderer); 

    for (int x = 0; x < 16; x++){
        for (int y = 0; y < 16; y++) {
            PPU::Tile tile = ppu.pattern_tiles[x + y * 16];
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) { 
                        SDL_SetRenderDrawColor(renderer, 
                        ppu.palettes[test_palettes[tile.pixel_pattern[i][j]]][0], 
                        ppu.palettes[test_palettes[tile.pixel_pattern[i][j]]][1], 
                        ppu.palettes[test_palettes[tile.pixel_pattern[i][j]]][2], 
                        255);
                        SDL_RenderDrawPoint(renderer, (i + x * 8) * 2, (j + y * 8) * 2);
                        SDL_RenderDrawPoint(renderer, (i + x * 8) * 2 + 1, (j + y * 8) * 2);
                        SDL_RenderDrawPoint(renderer, (i + x * 8) * 2, (j + y * 8) * 2 + 1);
                        SDL_RenderDrawPoint(renderer, (i + x * 8) * 2 + 1, (j + y * 8) * 2 + 1);
                    }
                }
        }
    }

    for (int x = 0; x < 16; x++){
        for (int y = 0; y < 16; y++) {
            PPU::Tile tile = ppu.pattern_tiles[x + y * 16 + 256];
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) { 
                        SDL_SetRenderDrawColor(renderer, 
                        ppu.palettes[test_palettes[tile.pixel_pattern[i][j]]][0], 
                        ppu.palettes[test_palettes[tile.pixel_pattern[i][j]]][1], 
                        ppu.palettes[test_palettes[tile.pixel_pattern[i][j]]][2], 
                        255);
                        SDL_RenderDrawPoint(renderer, (i + x * 8) * 2 + 256, (j + y * 8) * 2);
                        SDL_RenderDrawPoint(renderer, (i + x * 8) * 2 + 1 + 256, (j + y * 8) * 2);
                        SDL_RenderDrawPoint(renderer, (i + x * 8) * 2 + 256, (j + y * 8) * 2 + 1);
                        SDL_RenderDrawPoint(renderer, (i + x * 8) * 2 + 1 + 256, (j + y * 8) * 2 + 1);
                    }
                }
        }
    }

    bool running = true;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }

        SDL_RenderPresent(renderer);
    }

    std::cout << "No Error" << std::endl;
    return 0;
}