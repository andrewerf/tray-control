//
// Created by andrew on 11/17/22.
//
#include <cxxopts.hpp>
#include <iostream>
#include <fmt/printf.h>

#include "StatusNotifierWatcher.h"
#include "StatusNotifierItem.h"
#include "Utils.h"


void exitWithMsg( std::string_view msg, int code = -1 )
{
    std::cerr << msg << std::endl;
    exit( code );
}


int main( int argc, char** argv )
{
    cxxopts::Options optionsDecl( "tray-show", "Show items in the system tray" );
    optionsDecl.add_options()
        ( "h,help", "Print help and exit", cxxopts::value<bool>()->default_value("false") )
        ( "v,verbose", "Show full info about each item", cxxopts::value<bool>()->default_value("false") );

    const auto options = optionsDecl.parse( argc, argv );
    if ( options["help"].as<bool>() )
    {
        std::cout << optionsDecl.help();
        return 0;
    }
    const bool verboseOutput = options["verbose"].as<bool>();

    StatusNotifierWatcher watcher;
    if ( auto connRes = watcher.connect(); !connRes )
        exitWithMsg( "Could not connect to the StatusNotifierWatcher with error: " + connRes.error().show(), -1 );

    if ( auto maybeAddrs = watcher.getRegisteredStatusNotifierItemAddresses() )
    {
        for ( const auto& addr : maybeAddrs.value() )
        {
            StatusNotifierItem item( addr );
            if ( auto connRes = item.connect() )
            {
                item.getCategory() >> std::bind_front( fmt::printf<std::string_view, std::string>, "Category: %s\n" );
                item.getTitle() >> std::bind_front( fmt::printf<std::string_view, std::string>, "Title: %s\n" );

                if ( verboseOutput )
                {
                    item.getId() >> std::bind_front( fmt::printf<std::string_view, std::string>, "Id: %s\n" );
                    item.getStatus() >> std::bind_front( fmt::printf<std::string_view, std::string>, "Status: %s\n" );
                    item.getWindowId() >> std::bind_front( fmt::printf<std::string_view, uint32_t>, "WindowId: %d\n" );
                    item.getIconName() >> std::bind_front( fmt::printf<std::string_view, std::string>, "IconName: %s\n" );
                }
            }
            else
            {
                std::cerr << "Could not connect to the StatusNotifierItem on address: " << addr << " with error: " << connRes.error().show() << '\n';
            }

            std::cout << '\n';
        }
    }
}