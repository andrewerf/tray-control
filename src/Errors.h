//
// Created by andrew on 11/17/22.
//
#pragma once

#include <magic_enum.hpp>

enum class ErrorKind
{
    NoError,
    ConnectionError,
    TypeError,
    DBusError,
    UnknownError,
};


struct Error
{
    ErrorKind kind = ErrorKind::NoError;
    std::string_view msg;

    std::string show() const
    {
        std::string res( magic_enum::enum_name( kind ) );
        res += '\n';
        res += msg;
        return res;
    }
};

constexpr auto makeError( ErrorKind kind ) noexcept
{
    return std::unexpected{ Error{ kind, "" } };
}

constexpr auto makeError( ErrorKind kind, std::string_view msg ) noexcept
{
    return std::unexpected{ Error{ kind, msg } };
}