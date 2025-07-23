#include "hh/sdl.hh"
#include <iostream>



int main() {
    sdl::create_window("Rebar Test: The Sequel", 640, 480);
    sdl::do_nothing_loop();

    return 0;
}
