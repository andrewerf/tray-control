//
// Created by andrew on 11/17/22.
//

#include "StatusNotifierItem.h"
#include <sdbus-c++/sdbus-c++.h>

#include "DBusUtils.h"


template <typename T>
static constexpr auto safelyGetSNIProperty = std::bind( safelyGetProperty<T>, std::placeholders::_1, "org.kde.StatusNotifierItem", std::placeholders::_2 );


StatusNotifierItem::StatusNotifierItem( std::string_view destination ):
    destination_( destination )
{}

StatusNotifierItem::~StatusNotifierItem() = default;


std::expected<void, Error> StatusNotifierItem::connect()
{
    return safelyExec( [this] -> std::expected<void, Error> {
        if ( proxy_ = sdbus::createProxy( sdbus::createSessionBusConnection(), std::string( destination_ ), "/StatusNotifierItem" ) )
            return {};
        else
            return makeError( ErrorKind::ConnectionError );
    } );
}

std::expected<std::string, Error> StatusNotifierItem::getCategory()
{
    return safelyGetSNIProperty<std::string>( proxy_, "Category" );
}

std::expected<std::string, Error> StatusNotifierItem::getId()
{
    return safelyGetSNIProperty<std::string>( proxy_, "Id" );
}

std::expected<std::string, Error> StatusNotifierItem::getTitle()
{
    return safelyGetSNIProperty<std::string>( proxy_, "Title" );
}

std::expected<std::string, Error> StatusNotifierItem::getStatus()
{
    return safelyGetSNIProperty<std::string>( proxy_, "Status" );
}

std::expected<uint32_t, Error> StatusNotifierItem::getWindowId()
{
    return safelyGetSNIProperty<uint32_t>( proxy_, "WindowId" );
}

std::expected<std::string, Error> StatusNotifierItem::getIconName()
{
    return safelyGetSNIProperty<std::string>( proxy_, "IconName" );
}

std::expected<std::string, Error> StatusNotifierItem::getOverlayIconName()
{
    return safelyGetSNIProperty<std::string>( proxy_, "OverlayIconName" );
}

std::expected<std::string, Error> StatusNotifierItem::getAttentionIconName()
{
    return safelyGetSNIProperty<std::string>( proxy_, "AttentionIconName" );
}

std::expected<std::string, Error> StatusNotifierItem::getAttentionMovieName()
{
    return safelyGetSNIProperty<std::string>( proxy_, "AttentionMovieName" );
}

std::expected<StatusNotifierItem::ToolTip, Error> StatusNotifierItem::getToolTip()
{
    return makeError( ErrorKind::UnknownError, "ToolTip is not implemented yet" );
}

std::expected<void, Error> StatusNotifierItem::activate( int x, int y )
{
    return safelyCallMethod<void>( proxy_, "org.kde.StatusNotifierItem", "Activate", x, y );
}
