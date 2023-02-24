cmake_minimum_required(VERSION 3.2)

project(caveshoot_server)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(caveshoot_server main.cpp Shell.h)

target_include_directories(caveshoot_server PUBLIC ./include pstreams-1.0.3)

target_link_libraries(caveshoot_server sfml-network)
