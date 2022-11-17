//
// Created by andrew on 11/17/22.
//
#pragma once

#include <string>
#include <memory>
#include <expected>

#include "Errors.h"

namespace sdbus
{
    class IProxy;
}


class StatusNotifierItem
{
public:

    struct ToolTip
    {
        std::string iconName;
        // icon data
        std::string title;
        std::string description;
    };

    StatusNotifierItem( std::string_view destination );
    ~StatusNotifierItem();

    std::expected<void, Error> connect();


    /**
     * @name Properties
     * @brief Properties interface for StatusNotifierItem: https://www.freedesktop.org/wiki/Specifications/StatusNotifierItem/StatusNotifierItem/
     * @return
     */
    ///@{
    std::expected<std::string, Error> getCategory();

    std::expected<std::string, Error> getId();

    std::expected<std::string, Error> getTitle();

    std::expected<std::string, Error> getStatus();

    std::expected<uint32_t, Error> getWindowId();

    std::expected<std::string, Error> getIconName();

    // getIconPixmap()

    std::expected<std::string, Error> getOverlayIconName();

    // getOverlayIconPixmap()

    std::expected<std::string, Error> getAttentionIconName();

    // getAttentionIconPixmap()

    std::expected<std::string, Error> getAttentionMovieName();

    std::expected<ToolTip, Error> getToolTip();

    // menu
    ///@}

    /**
     * @name Methods
     * @brief Methods interface for StatusNotifierItem: https://www.freedesktop.org/wiki/Specifications/StatusNotifierItem/StatusNotifierItem/
     * @return
     */
    ///@{
    std::expected<void, Error> contextMenu( int x, int y );

    std::expected<void, Error> activate( int x, int y );

    std::expected<void, Error> secondaryActivate( int x, int y );

    std::expected<void, Error> scroll( int delta, const std::string& orientation );
    ///@}

private:
    std::unique_ptr<sdbus::IProxy> proxy_;
    std::string_view destination_;
};