#pragma once
#include "..\hh\sdl.hh"
#include <stdexcept>
#include <string>
#include <cstddef>

::std::unique_ptr<sdl> sdl::_inst;
::std::mutex sdl::_mtx;


sdl::AppState& sdl::AppState::from_ptr(void* appstate) { return *static_cast<AppState*>(appstate); }
void sdl::AppState::create(void** appstate) { *appstate = new AppState; }
void sdl::AppState::destroy(void* appstate) { delete &AppState::from_ptr(appstate); }
sdl::AppState sdl::AppState::copy(void* appstate) { return AppState{AppState::from_ptr(appstate)}; }


sdl::sdl() { if (!SDL_Init(SDL_INIT_VIDEO)) throw ::std::runtime_error("Failed to init SDL."); }

sdl::~sdl() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

sdl& sdl::get_inst() {
    if (!_inst) {
        ::std::lock_guard<::std::mutex> lock{_mtx};
        if (!_inst) _inst.reset(::new sdl{});
    }
    return *_inst;
}


void sdl::do_nothing_loop() {
    SDL_Event e;
    bool keep_running = true;
    while (keep_running)
        while (SDL_PollEvent(&e))
            if (e.type == SDL_EVENT_QUIT) keep_running = false;
}

void sdl::create_window(::std::string const& name, uint32_t w, uint32_t h, bool fullscreen) {
    sdl& self = get_inst();
    self.window = SDL_CreateWindow(name.c_str(), static_cast<int>(w), static_cast<int>(h), (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0);
    if (!self.window) throw ::std::runtime_error(SDL_GetError());
}

void sdl::create_renderer() {
    sdl& self = get_inst();
    if (self.window) SDL_CreateRenderer(self.window, nullptr);
}

void sdl::create_renderer(::std::string const& name) {
    sdl& self = get_inst();
    if (self.window) SDL_CreateRenderer(self.window, name.c_str());
}


