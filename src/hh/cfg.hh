#pragma once
#include <string>
#include <optional>
#include <variant>
#include <concepts>
#include <vector>

class CfgList;


class CfgValue {
    using StringType = ::std::string;
    using IntType = int32_t;
    using RealType = float;
    using BoolType = bool;

    ::std::string name;
    ::std::variant<StringType, IntType, RealType, BoolType, CfgList> value;
public:
    enum class Type : uint8_t {
        String = 0,
        Integer = 1,
        Real = 2,
        Boolean = 3,
        List = 4
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
