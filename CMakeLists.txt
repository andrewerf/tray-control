cmake_minimum_required(VERSION 3.23)
project(tray_control)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts-diagnostics-depth=10")

add_subdirectory(3rdparty/cxxopts)
include_directories(3rdparty/magic_enum/include)

find_package(sdbus-c++ REQUIRED)
find_package(fmt REQUIRED)

add_library(core STATIC src/StatusNotifierWatcher.cpp src/StatusNotifierItem.cpp)
target_link_libraries(core SDBusCpp::sdbus-c++)

add_executable(tray-show src/tray-show.cpp)
target_link_libraries(tray-show core cxxopts fmt)

add_executable(tray-activate src/tray-activate.cpp)
target_link_libraries(tray-activate core cxxopts fmt)
