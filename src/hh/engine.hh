#pragma once
#include "sdl.hh"
#include <vector>


class RebarEngine {
public:
    static void report_error(::std::exception const& e) noexcept;
    static void init(::std::vector<::std::string> const& args);
    static void handle_event(SDL_Event const& event) noexcept;
    static void frame(uint64_t delta_ms);
};
