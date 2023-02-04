cmake_minimum_required(VERSION 3.2)

project(caveshoot)

set(CMAKE_CXX_STANDARD 20)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

file(GLOB imgui_files ./3rd/imgui/*.cpp)

find_package(OpenGL REQUIRED)

add_executable(caveshoot ${imgui_files} include/Exceptions.h include/Game.h include/GameObject.h include/Player.h include/TextureManager.h src/Game.cpp src/GameObject.cpp src/main.cpp src/Player.cpp src/TextureManager.cpp src/Bullet.cpp include/Bullet.h)

target_include_directories(caveshoot PUBLIC ./include)

target_include_directories(caveshoot PUBLIC ./3rd/imgui)

target_link_libraries(caveshoot sfml-graphics sfml-audio)
target_link_libraries(caveshoot OpenGL::GL)
