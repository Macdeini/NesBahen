#include <iostream>
#include "NES/6502.h"
#include "NES/bus.h"
#include "NES/cartridge.h"
#include "NES/ppu.h"

#define SCREEN_WIDTH 256 
#define SCREEN_HEIGHT 240

int main(int argc, char** argv){
    Nes6502 cpu;
    Bus bus;
    Cartridge cartridge;
    PPU ppu;
    ppu.connect_bus(&bus);
    ppu.construct_pattern_memory(); // error
    cpu.connect_bus(&bus);
    bus.set_cpu(&cpu);
    bus.set_ppu(&ppu);
    bus.set_cartridge(&cartridge);


    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SLD test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!window){
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    int x = 0;
    int y = 0;

    for (int i = 0; i < 256; i++){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawPoint(renderer, x, y);
        x++;
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

    return 0;
}