#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL_main.h"
#include "SDL3/SDL_init.h"
#include "hh\sdl.hh"
#include <iostream>


extern "C" {
    SDL_AppResult SDLCALL SDL_AppInit(void **appstate, int argc, char **argv) {
        try {
            sdl::AppState::create(appstate);
            sdl::create_window("Rebar Test SDL3", 640, 480);
        } catch (::std::exception const& e) {
            ::std::cerr << "Exception: " << e.what() << ::std::endl;
            return SDL_APP_FAILURE;
        }
        return SDL_APP_CONTINUE;
    }

    SDL_AppResult SDLCALL SDL_AppIterate(void *appstate) {
        sdl::AppState::from_ptr(appstate).iterations++;
        return SDL_APP_CONTINUE;
    }

    SDL_AppResult SDLCALL SDL_AppEvent(void *appstate, SDL_Event* event) {
        if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;
        return SDL_APP_CONTINUE;
    }

    void SDLCALL SDL_AppQuit(void *appstate, SDL_AppResult result) {
        sdl::AppState last_state = sdl::AppState::copy(appstate);
        sdl::AppState::destroy(appstate);
        ::std::cout << "Quitted after " << last_state.iterations << " iterations." << ::std::endl;
    }
}
