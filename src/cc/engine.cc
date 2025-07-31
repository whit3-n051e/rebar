#include "../hh/engine.hh"

#include <iostream>

void RebarEngine::report_error(::std::exception const& e) noexcept { ::std::cout << e.what() << ::std::endl; }


// Init engine
void RebarEngine::init(::std::vector<::std::string> const& args) {
    sdl::create_window("Rebar Test SDL3", 640, 480);
}


// Each event gets sent here
void RebarEngine::handle_event(SDL_Event const& event) noexcept {
    
}


// And each frame, this should run
void RebarEngine::frame() {

}
