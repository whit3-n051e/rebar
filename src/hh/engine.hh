#pragma once
#include "sdl.hh"
#include <vector>


class RebarEngine {
public:
    static void report_error(::std::exception const&) noexcept;
    static void init(::std::vector<::std::string> const&);
    static void handle_event(SDL_Event const&) noexcept;
    static void frame(uint64_t);
};
