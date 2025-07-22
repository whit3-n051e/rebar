#define SDL_MAIN_HANDLED    // DO NOT FORGET!!!
#include "SDL2\SDL.h"
#include <iostream>



int main() {
    SDL_Window* window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to init SDL!" << std::endl << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("Rebar Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);

    if (!window) {
        std::cerr << "Failed to init window!" << std::endl << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Event e;
    bool keep_running = true;

    while (keep_running)
        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT) keep_running = false;

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
