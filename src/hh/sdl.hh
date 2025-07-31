#pragma once
#define SDL_MAIN_HANDLED    // DO NOT FORGET!!!
#include "SDL2\SDL.h"
#include <memory>
#include <mutex>

class sdl {
    friend class ::std::unique_ptr<sdl>;
    friend class ::std::default_delete<sdl>;

    static ::std::unique_ptr<sdl> _inst;
    static ::std::mutex _mtx;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    sdl();
    ~sdl();
    static sdl& get_inst();

public:

    static void do_nothing_loop();
    static void create_window(::std::string const& name, uint32_t w, uint32_t h, bool fullscreen = false);
    static void create_renderer();
};
