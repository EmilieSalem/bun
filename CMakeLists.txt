cmake_minimum_required(VERSION 3.24)
project(bun)

set(CMAKE_CXX_STANDARD 17)

add_executable(bun main.cpp headers/ColorPalette.h headers/GameObject.h sources/GameObject.cpp headers/Bunny.h sources/Bunny.cpp headers/ChargeBar.h sources/ChargeBar.cpp headers/Platform.h sources/Platform.cpp headers/Utils.h headers/Utils.h headers/Utils.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR D:/saemi/Documents/Perso/cpp-libs/SFML/lib/cmake/SFML)
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

include_directories(D:/saemi/Documents/Perso/cpp-libs/SFML/include)
target_link_libraries(bun sfml-system sfml-window sfml-graphics sfml-audio)
