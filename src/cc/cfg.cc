#include "SDL3/SDL_filesystem.h"
#include "../hh/cfg.hh"
#include <fstream>
#include <type_traits>
#include <cstddef>


CfgValue::CfgValue(::std::string const& _n, StringType _v) noexcept : name{_n}, value{_v} {}
CfgValue::CfgValue(::std::string const& _n, ::std::integral auto _v) noexcept : name{_n}, value{static_cast<IntType>(_v)} {}
CfgValue::CfgValue(::std::string const& _n, ::std::floating_point auto _v) noexcept : name{_n}, value{static_cast<RealType>(_v)} {}
CfgValue::CfgValue(::std::string const& _n, BoolType _v) noexcept : name{_n}, value{_v} {}
CfgValue::CfgValue(::std::string const& _n, CfgList _v) noexcept : name{_n}, value{_v} {}
constexpr CfgValue::Type CfgValue::get_type() const noexcept { return static_cast<Type>(value.index()); }


::std::optional<::std::string> cfg::get_pref_path(::std::string const& org, ::std::string const& app) noexcept {
    char* path = SDL_GetPrefPath(org.c_str(), app.c_str());
    if (path) {
        ::std::string result = path;
        SDL_free(path);
        return result;
    }
    return {};
}

bool cfg::write_file(::std::string const& data, ::std::string const& path) noexcept {
    try {
        ::std::ofstream fout(path);
        if (!fout) return false;
        fout << data << ::std::endl;
    } catch (...) { return false; }
}
