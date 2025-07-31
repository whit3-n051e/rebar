#include "../hh/engine.hh"

#include <iostream>


// Using an enum class is safer than using an enum.
SDL_AppResult RebarEngine::to_sdl_result(RebarEngine::Result result) noexcept {
    switch (result) {
        case Result::Continue: return SDL_APP_CONTINUE;
        case Result::Success: return SDL_APP_SUCCESS;
        case Result::Failure: return SDL_APP_FAILURE;
    }
}

void RebarEngine::report_error(::std::exception const& e) noexcept { ::std::cout << e.what() << ::std::endl; }


// Init engine
void RebarEngine::init(::std::vector<::std::string> const& args) {
    sdl::create_window("Rebar Test SDL3", 640, 480);
}


// Each event gets sent here
RebarEngine::Result RebarEngine::handle_event(SDL_Event const& event) noexcept {
    return Result::Continue;
}


// And each frame, this should run
void RebarEngine::frame() {

}
