//
// Created by andrew on 11/17/22.
//
#pragma once

#include <sdbus-c++/sdbus-c++.h>
#include "Errors.h"
#include <functional>

template <std::invocable F>
std::invoke_result_t<F> safelyExec( F&& f )
{
    try
    {
        return std::invoke( std::forward<F>( f ) );
    }
    catch( sdbus::Error& err )
    {
        return makeError( ErrorKind::DBusError, err.what() );
    }
    catch( std::exception& err )
    {
        return makeError( ErrorKind::UnknownError, err.what() );
    }
}

template <typename T>
std::expected<T, Error> safelyGetProperty( const std::unique_ptr<sdbus::IProxy>& proxy, const std::string& interface, const std::string& property )
{
    return safelyExec( [&] -> std::expected<T, Error> {
        if ( !proxy )
            return makeError( ErrorKind::ConnectionError );

        const auto variantResult = proxy->getProperty( property ).onInterface( interface );
        if ( variantResult.containsValueOfType<T>() )
            return variantResult.get<T>();
        else
            return makeError( ErrorKind::TypeError );
    } );
}

template <typename Dest, typename ...Args>
std::expected<Dest, Error> safelyCallMethod( const std::unique_ptr<sdbus::IProxy>& proxy, const std::string& interface, const std::string& method, Args&& ...args )
{
    return safelyExec( [&] -> std::expected<Dest, Error> {
        if ( !proxy )
            return makeError( ErrorKind::ConnectionError );

        std::expected<Dest, Error> res;
        proxy->callMethod( method ).onInterface( interface ).withArguments( std::forward<Args>( args )... ).storeResultsTo( res.value() );
        return res;
    } );
}

template <typename Dest, typename ...Args>
    requires std::same_as<Dest, void>
std::expected<void, Error> safelyCallMethod( const std::unique_ptr<sdbus::IProxy>& proxy, const std::string& interface, const std::string& method, Args&& ...args )
{
    return safelyExec( [&] -> std::expected<void, Error> {
        if ( !proxy )
            return makeError( ErrorKind::ConnectionError );

        proxy->callMethod( method ).onInterface( interface ).withArguments( std::forward<Args>( args )... ).dontExpectReply();
        return {};
    } );
}
