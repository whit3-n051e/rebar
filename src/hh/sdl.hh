#pragma once
#include "SDL3\SDL.h"
#include <memory>
#include <mutex>
#include <string>

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
    struct AppState {
        SDL_Window *window = nullptr;
        uint64_t iterations = 0;

        static AppState& from_ptr(void* appstate);
        static void create(void** appstate);
        static void destroy(void* appstate);
        static AppState copy(void* appstate);
    };

    static void do_nothing_loop();
    static void create_window(::std::string const& name, uint32_t w, uint32_t h, bool fullscreen = false);
    static void create_renderer();
    static void create_renderer(::std::string const& name);
};
