cmake_minimum_required (VERSION 3.2)

project(caveshoot)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)


file(GLOB src_files ./src/*.cpp)

file(GLOB imgui_files ./3rd/imgui/*.cpp)

find_package(OpenGL REQUIRED)

add_executable(caveshoot ${src_files} ${imgui_files})

target_include_directories(caveshoot PUBLIC ./include)

target_include_directories(caveshoot PUBLIC ./3rd/imgui)

target_link_libraries(caveshoot sfml-graphics sfml-audio )
