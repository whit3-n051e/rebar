#pragma once
#include "SDL3/SDL.h"
#include <memory>
#include <mutex>
#include <string>
#include <stdexcept>

class sdl {
    friend class ::std::unique_ptr<sdl>;
    friend class ::std::default_delete<sdl>;

    static ::std::unique_ptr<sdl> _inst;
    static ::std::mutex _mtx;

    uint64_t ticks = SDL_GetTicks();
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    sdl();
    ~sdl();
    static sdl& get_inst();

public:

    static uint64_t get_delta_ms();
    static void cleanup();
    static void create_window(::std::string const&, uint32_t, uint32_t, bool = false);
    static SDL_Window* get_window() noexcept;
    static void create_renderer(const char* = nullptr);
};
