cmake_minimum_required(VERSION 3.24)
project(bun)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(bun main.cpp headers/ColorPalette.h headers/GameObject.h sources/GameObject.cpp headers/Bunny.h sources/Bunny.cpp headers/ChargeBar.h sources/ChargeBar.cpp headers/Platform.h sources/Platform.cpp headers/Utils.h headers/Utils.h headers/Utils.h headers/Carrot.h sources/Carrot.cpp headers/ObjectManager.h sources/ObjectManager.cpp headers/UIManager.h sources/UIManager.cpp headers/GameManager.h sources/GameManager.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR D:/saemi/Documents/Perso/cpp-libs/SFML/lib/cmake/SFML)
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

include_directories(D:/saemi/Documents/Perso/cpp-libs/SFML/include)
target_link_libraries(bun sfml-system sfml-window sfml-graphics sfml-audio)
