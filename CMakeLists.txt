cmake_minimum_required (VERSION 2.8.11)

project(caveshoot)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

file(GLOB src_files ./src/*.cpp)

add_executable(caveshoot ${src_files} src/Game.cpp include/Game.h)

target_include_directories(caveshoot PUBLIC ./include)

target_link_libraries(caveshoot sfml-graphics sfml-audio)
