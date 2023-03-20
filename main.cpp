#include <iostream>
#include <SFML/Graphics.hpp>
#include "headers/ColorPalette.h"
#include "headers/Bunny.h"
#include "headers/Platform.h"

int main() {
    auto bunny = Bunny();
    auto platform1 = Platform(Platform::PlatformLevel::LOW);
    auto platform2 = Platform(Platform::PlatformLevel::MIDDLE);
    auto platform3 = Platform(Platform::PlatformLevel::HIGH);


    sf::Clock chrono{};

    sf::RenderWindow window{sf::VideoMode(), "bun", sf::Style::Fullscreen};
    while(window.isOpen()){
        auto event = sf::Event();

        while(window.pollEvent(event)){
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
        }

        auto loopTime = chrono.restart().asSeconds();

        window.clear(BEIGE);

        bunny.update(loopTime);

        platform1.display(window);
        platform2.display(window);
        platform3.display(window);

        bunny.display(window);

        window.display();
    }
}
