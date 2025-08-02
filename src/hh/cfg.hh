#pragma once
#include <string>
#include <optional>
#include <variant>
#include <concepts>
#include <vector>
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


class CfgList;


class CfgValue {
    using StringType = ::std::string;
    using IntType = int32_t;
    using RealType = float;
    using BoolType = bool;

    ::std::string name;
    ::std::variant<StringType, IntType, RealType, BoolType, CfgList> value;

    template <class T> struct type_index : variant_index<T, decltype(value)> {};

    static inline ::std::vector<::std::string> split(::std::string const& str, ::std::string const& deli);
    static inline void trim_edit(::std::string& str);
    static inline ::std::string trim_copy(::std::string const& str);
public:
    enum class Type : ::std::size_t {
        String  = type_index<StringType>::v,
        Integer = type_index<IntType>::v,
        Real    = type_index<RealType>::v,
        Boolean = type_index<BoolType>::v,
        List    = type_index<CfgList>::v
    };

    CfgValue(::std::string const& _n, StringType _v) noexcept;
    CfgValue(::std::string const& _n, ::std::integral auto _v) noexcept;
    CfgValue(::std::string const& _n, ::std::floating_point auto _v) noexcept;
    CfgValue(::std::string const& _n, BoolType _v) noexcept;
    CfgValue(::std::string const& _n, CfgList _v) noexcept;
    constexpr Type get_type() const noexcept;
    
};


class CfgList {
    ::std::vector<CfgValue> data;
public:
    
};


class cfg {
    static ::std::optional<::std::string> get_pref_path(::std::string const& org, ::std::string const& app) noexcept;
    static bool write_file(::std::string const& data, ::std::string const& path) noexcept;
public:

};
