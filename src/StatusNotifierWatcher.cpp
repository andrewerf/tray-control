//
// Created by andrew on 11/16/22.
//

#include "StatusNotifierWatcher.h"
#include <sdbus-c++/sdbus-c++.h>

#include "Utils.h"
#include "DBusUtils.h"


StatusNotifierWatcher::StatusNotifierWatcher() = default;

StatusNotifierWatcher::~StatusNotifierWatcher() = default;

std::expected<void, Error> StatusNotifierWatcher::connect()
{
    return safelyExec( [this] -> std::expected<void, Error> {
        if ( proxy_ = sdbus::createProxy( sdbus::createSessionBusConnection(), "org.kde.StatusNotifierWatcher", "/StatusNotifierWatcher" ) )
            return {};
        else
            return makeError( ErrorKind::ConnectionError );
    } );
}

std::expected<std::vector<std::string>, Error> StatusNotifierWatcher::getRegisteredStatusNotifierItemAddresses()
{
    return
        safelyGetProperty<std::vector<std::string>>( proxy_, "org.kde.StatusNotifierWatcher", "RegisteredStatusNotifierItems" ) >>
            [] ( std::vector<std::string>&& addrs ) {
                for ( auto& addr : addrs )
                {
                    addr = addr.substr( 0, addr.find( '/' ) );
                }

                return addrs;
            };
}



