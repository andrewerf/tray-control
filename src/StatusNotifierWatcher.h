//
// Created by andrew on 11/16/22.
//
#pragma once

#include <vector>
#include <string>
#include <memory>
#include <expected>

#include "Errors.h"

namespace sdbus
{
    class IProxy;
}

class StatusNotifierWatcher
{
public:
    StatusNotifierWatcher();
    ~StatusNotifierWatcher();

    std::expected<void, Error> connect();
    std::expected<std::vector<std::string>, Error> getRegisteredStatusNotifierItemAddresses();

private:
    std::unique_ptr<sdbus::IProxy> proxy_;
};