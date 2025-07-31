#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL_main.h"
#include "SDL3/SDL_init.h"
#include "hh/engine.hh"


extern "C" {
    SDL_AppResult SDLCALL SDL_AppInit(void **appstate, int argc, char **argv) {
        try { RebarEngine::init(::std::vector<::std::string>(argv, argv + argc)); }
        catch (::std::exception const& e) {
            RebarEngine::report_error(e);
            return SDL_APP_FAILURE;
        }
        return SDL_APP_CONTINUE;
    }

    SDL_AppResult SDLCALL SDL_AppIterate(void *appstate) {
        try { RebarEngine::frame(sdl::get_delta_ms()); }
        catch (::std::exception const& e) {
            RebarEngine::report_error(e);
            return SDL_APP_FAILURE;
        }
        return SDL_APP_CONTINUE;
    }

    SDL_AppResult SDLCALL SDL_AppEvent(void *appstate, SDL_Event* event) {
        if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;
        RebarEngine::handle_event(*event);
        return SDL_APP_CONTINUE;
    }

    void SDLCALL SDL_AppQuit(void *appstate, SDL_AppResult result) { sdl::cleanup(); }
}
