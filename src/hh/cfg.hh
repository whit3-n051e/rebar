#pragma once
#include <string>
#include <optional>
#include <variant>
#include <concepts>
#include <vector>
#include <type_traits>
#include <cstddef>
#include <array>
#include <map>


namespace {
    template <class T, class... Ts> struct Index;
    template <class T, class... Ts> struct Index<T, T, Ts...> : std::integral_constant<std::size_t, 0> {};
    template <class T, class U, class... Ts> struct Index<T, U, Ts...> : std::integral_constant<std::size_t, 1 + Index<T, Ts...>::value> {};
    template <class T, class V> struct variant_index;
    template <class T, class... Ts> struct variant_index<T, ::std::variant<Ts...>> {
        static const constexpr ::std::size_t v = Index<T, Ts...>::value;
    };
}


class cfg {
public:
    using StringType = ::std::string;
    using IntType = int32_t;
    using RealType = float;
    enum class BoolType : bool {
        False = false,
        True  = true
    };
    using MapType = ::std::map<StringType, cfg>;

    class Value {
        ::std::variant<StringType, IntType, RealType, BoolType, MapType> value;
        template <class T> struct type_index : variant_index<T, decltype(value)> {};
    public:
        enum class Type : ::std::size_t {
            String  = type_index<StringType>::v,
            Integer = type_index<IntType>::v,
            Real    = type_index<RealType>::v,
            Boolean = type_index<BoolType>::v,
            List    = type_index<MapType>::v
        };

    };

private:

    ::std::map<StringType, Value> data;

    static ::std::optional<::std::string> get_pref_path(::std::string const& org, ::std::string const& app) noexcept;
    static bool write_file(::std::string const& data, ::std::string const& path) noexcept;
    static inline ::std::vector<::std::string> split(::std::string const& str, ::std::string const& deli);
    static inline void trim_edit(::std::string& str);
    static inline ::std::string trim_copy(::std::string const& str);
    static inline ::std::string remove_comments(::std::string const& line) noexcept;
    static inline ::std::optional<::std::array<::std::string, 2>> to_key_value_pair(::std::string const& line) noexcept;

    cfg() = default;

public:
    
    
    ~cfg() = default;
    
};
