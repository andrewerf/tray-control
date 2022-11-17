//
// Created by andrew on 11/17/22.
//
#pragma once

#include <variant>
#include <expected>
#include <ranges>
#include <functional>

template <typename T, typename E>
constexpr std::variant<T, E> toVariant( std::expected<T, E>&& expected )
{
    if ( expected )
        return std::variant<T, E>{ std::in_place_index<0>, std::move( expected.value() ) };
    else
        return std::variant<T, E>{ std::in_place_index<1>, std::move( expected.error() ) };
}

template <typename T>
struct is_expected
{
    static constexpr bool value = false;
};

template <typename T, typename E>
struct is_expected<std::expected<T, E>>
{
    static constexpr bool value = true;
};

template <typename T>
constexpr bool is_expected_v = is_expected<T>::value;



template <typename T1, typename E, std::invocable<T1> F>
    requires is_expected_v<std::invoke_result_t<F, T1>>
constexpr std::invoke_result_t<F, T1> operator >>( std::expected<T1, E>&& exp, F&& f )
{
    if ( exp )
        return std::invoke( std::forward<F>( f ), std::move( exp.value() ) );
    else
        return std::unexpected{ exp.error() };
}

template <typename T1, typename E, std::invocable<T1> F>
    requires ( !is_expected_v<std::invoke_result_t<F, T1>> && ( !std::same_as<std::invoke_result_t<F, T1>, void> ) )
constexpr std::expected<std::invoke_result_t<F, T1>, E> operator >>( std::expected<T1, E>&& exp, F&& f )
{
    if ( exp )
        return std::invoke( std::forward<F>( f ), std::move( exp.value() ) );
    else
        return std::unexpected{ exp.error() };
}

template <typename T1, typename E, std::invocable<T1> F>
    requires std::same_as<std::invoke_result_t<F, T1>, void>
constexpr std::expected<void, E> operator >>( std::expected<T1, E>&& exp, F&& f )
{
    if ( exp )
    {
        std::invoke( std::forward<F>( f ), std::move( exp.value() ) );
        return {};
    }
    else
        return std::unexpected{ exp.error() };
}
