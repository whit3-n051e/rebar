#include "SDL3/SDL_filesystem.h"
#include "../hh/cfg.hh"
#include <fstream>
#include <type_traits>
#include <cstddef>


namespace {
    template <class T, class... Ts> struct Index;
    template <class T, class... Ts> struct Index<T, T, Ts...> : std::integral_constant<std::size_t, 0> {};
    template <class T, class U, class... Ts> struct Index<T, U, Ts...> : std::integral_constant<std::size_t, 1 + Index<T, Ts...>::value> {};
    template <class T, class V> struct variant_index;
    template <class T, class... Ts> struct variant_index<T, ::std::variant<Ts...>> {
        static const constexpr ::std::size_t v = Index<T, Ts...>::value;
    };
}


CfgValue::CfgValue(::std::string const& _n, StringType _v) noexcept : name{_n}, value{_v} {}
CfgValue::CfgValue(::std::string const& _n, ::std::integral auto _v) noexcept : name{_n}, value{static_cast<IntType>(_v)} {}
CfgValue::CfgValue(::std::string const& _n, ::std::floating_point auto _v) noexcept : name{_n}, value{static_cast<RealType>(_v)} {}
CfgValue::CfgValue(::std::string const& _n, BoolType _v) noexcept : name{_n}, value{_v} {}
CfgValue::CfgValue(::std::string const& _n, CfgList _v) noexcept : name{_n}, value{_v} {}

constexpr CfgValue::Type CfgValue::get_type() const noexcept {
    switch (value.index()) {
        case variant_index<StringType, decltype(value)>::v: return Type::String;
        case variant_index<IntType,    decltype(value)>::v: return Type::Integer;
        case variant_index<RealType,   decltype(value)>::v: return Type::Real;
        case variant_index<BoolType,   decltype(value)>::v: return Type::Boolean;
        case variant_index<CfgList,    decltype(value)>::v: return Type::List;
        default: return Type::String;
    }
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
