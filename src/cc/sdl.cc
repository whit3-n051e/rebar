#pragma once
#include "../hh/sdl.hh"
#include <string>
#include <cstddef>

::std::unique_ptr<sdl> sdl::_inst;
::std::mutex sdl::_mtx;


sdl::sdl() { if (!SDL_Init(SDL_INIT_VIDEO)) throw ::std::runtime_error(SDL_GetError()); }

sdl::~sdl() { SDL_Quit(); }

uint64_t sdl::get_delta_ms() {
    sdl& self = get_inst();
    uint32_t current_ticks = SDL_GetTicks();
    uint32_t delta = current_ticks - self.ticks;
    self.ticks = current_ticks;
    return delta;
}

void sdl::cleanup() {
    sdl& self = get_inst();
    if (self.renderer) SDL_DestroyRenderer(self.renderer);
    if (self.window) SDL_DestroyWindow(self.window);
}

sdl& sdl::get_inst() {
    if (!_inst) {
        ::std::lock_guard<::std::mutex> lock{_mtx};
        if (!_inst) _inst.reset(::new sdl{});
    }
    return *_inst;
}

void sdl::create_window(::std::string const& name, uint32_t w, uint32_t h, bool fullscreen) {
    sdl& self = get_inst();
    if (self.window) SDL_DestroyWindow(self.window);
    self.window = SDL_CreateWindow(name.c_str(), static_cast<int>(w), static_cast<int>(h), (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0);
    if (!self.window) throw ::std::runtime_error(SDL_GetError());
}

SDL_Window* sdl::get_window() noexcept {
    if (!_inst) return nullptr;
    return _inst->window;
}

void sdl::create_renderer(const char* name) {
    sdl& self = get_inst();
    if (self.window) self.renderer = SDL_CreateRenderer(self.window, name);
}

