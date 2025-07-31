#pragma once
#include "sdl.hh"
#include <vector>


class RebarEngine {
public:
    enum class Result : uint8_t {
        Continue = 0,
        Success = 1,
        Failure = 2
    };
    
    static SDL_AppResult to_sdl_result(Result) noexcept;
    static void report_error(::std::exception const&) noexcept;
    static void init(::std::vector<::std::string> const&);
    static Result handle_event(SDL_Event const&) noexcept;
    static void frame();
};
