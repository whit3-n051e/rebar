#include "SDL3/SDL_filesystem.h"
#include "../hh/cfg.hh"
#include <fstream>
#include <algorithm> 
#include <cctype>
#include <locale>


CfgValue::CfgValue(::std::string const& _n, StringType _v) noexcept : name{_n}, value{_v} {}
CfgValue::CfgValue(::std::string const& _n, ::std::integral auto _v) noexcept : name{_n}, value{static_cast<IntType>(_v)} {}
CfgValue::CfgValue(::std::string const& _n, ::std::floating_point auto _v) noexcept : name{_n}, value{static_cast<RealType>(_v)} {}
CfgValue::CfgValue(::std::string const& _n, BoolType _v) noexcept : name{_n}, value{_v} {}
CfgValue::CfgValue(::std::string const& _n, CfgList _v) noexcept : name{_n}, value{_v} {}
constexpr CfgValue::Type CfgValue::get_type() const noexcept { return static_cast<Type>(value.index()); }

inline ::std::vector<::std::string> CfgValue::split(::std::string const& str, ::std::string const& deli) {
    ::std::vector<::std::string> result;
    ::std::size_t next = 0, last = 0;
    while ((next = str.find(deli, last)) != ::std::string::npos) {
        result.push_back(str.substr(last, next - last));
        last = next + deli.length();
    }
    result.push_back(str.substr(last));
    return result;
}

inline void CfgValue::trim_edit(::std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), str.end());
}

inline ::std::string CfgValue::trim_copy(::std::string const& str) {
    ::std::string copy = str;
    trim_edit(copy);
    return copy;
}


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
