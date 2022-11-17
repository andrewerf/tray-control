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
    cxxopts::Options optionsDecl( "tray-activate", "Activate items from the system tray" );
    optionsDecl.add_options()
        ( "h,help", "Print help and exit", cxxopts::value<bool>()->default_value("false") )
        ( "i,id", "Find items by id", cxxopts::value<std::string>() )
        ( "t,title", "Find items by title", cxxopts::value<std::string>() )
        ( "x", "X coord", cxxopts::value<int>()->default_value( "0" ) )
        ( "y", "Y coord", cxxopts::value<int>()->default_value( "0" ) );

    const auto options = optionsDecl.parse( argc, argv );
    if ( options["help"].as<bool>() )
    {
        std::cout << optionsDecl.help();
        return 0;
    }

    std::optional<std::string> id;
    std::optional<std::string> title;
    if ( auto [countId, countTitle] = std::make_tuple( options.count( "id" ), options.count( "title" ) );
         countId != 0 && countTitle != 0 || countId == 0 && countTitle == 0 )
    {
        exitWithMsg( "Please specify either id or title (and not both)", 0 );
    }
    else if ( countId != 0 )
        id = options["id"].as<std::string>();
    else if ( countTitle != 0 )
        title = options["title"].as<std::string>();

    const int x = options["x"].as<int>();
    const int y = options["y"].as<int>();

    StatusNotifierWatcher watcher;
    if ( auto connRes = watcher.connect(); !connRes )
        exitWithMsg( "Could not connect to the StatusNotifierWatcher with error: " + connRes.error().show(), -1 );

    if ( auto maybeAddrs = watcher.getRegisteredStatusNotifierItemAddresses() )
    {
        for ( const auto& addr : maybeAddrs.value() )
        {
            StatusNotifierItem item( addr );
            if ( !item.connect() )
                continue;

            if ( title )
            {
                item.getTitle() >> [&title, x, y, &item] ( auto&& ctitle )
                {
                    if ( ctitle == *title )
                    {
                        item.activate( x, y );
                    }
                };
            }
            else if ( id )
            {
                item.getId() >> [&id, x, y, &item] ( auto&& cid )
                {
                    if ( cid == *id )
                    {
                        item.activate( x, y );
                    }
                };
            }
        }
    }

}