#include "SDL3/SDL_filesystem.h"
#include "../hh/cfg.hh"
#include <fstream>
#include <algorithm> 
#include <cctype>
#include <locale>


// File Management

::std::optional<::std::string> cfg::get_pref_path(::std::string const& org, ::std::string const& app) noexcept try {
    char* path = SDL_GetPrefPath(org.c_str(), app.c_str());
    if (path) {
        ::std::string result = path;
        SDL_free(path);
        return result;
    } else return {};
} catch (...) { return {}; }


bool cfg::write_file(::std::string const& data, ::std::string const& path) noexcept try {
    ::std::ofstream fout(path);
    if (!fout) return false;
    fout << data << ::std::endl;
    return true;
} catch (...) { return false; }


// String Formatting

inline ::std::vector<::std::string> cfg::split(::std::string const& str, ::std::string const& deli) {
    ::std::vector<::std::string> result;
    ::std::size_t next = 0, last = 0;
    while ((next = str.find(deli, last)) != ::std::string::npos) {
        result.push_back(str.substr(last, next - last));
        last = next + deli.length();
    }
    result.push_back(str.substr(last));
    return result;
}

inline void cfg::trim_edit(::std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), str.end());
}

inline ::std::string cfg::trim_copy(::std::string const& str) {
    ::std::string copy = str;
    trim_edit(copy);
    return copy;
}

inline ::std::string cfg::remove_comments(::std::string const& line) noexcept try {
    ::std::vector<::std::string> splitted_0 = split(line, ";");
    if (splitted_0.size() == 0) return line;
    ::std::vector<::std::string> splitted_1 = split(splitted_0[0], "#");
    if (splitted_1.size() == 0) return splitted_0[0];
    return splitted_1[0];
} catch (...) { return line; }

inline ::std::optional<::std::array<::std::string, 2>> cfg::to_key_value_pair(::std::string const& line) noexcept try {
    ::std::string uncommented = remove_comments(line);
    ::std::vector<::std::string> splitted = split(uncommented, "=");
    if (splitted.size() != 2) return {};
    for (auto& part : splitted) trim_edit(part);
    return ::std::array{splitted[0], splitted[1]};
} catch (...) { return {}; }


// Add value






