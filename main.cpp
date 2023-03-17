#include <iostream>
#include <SFML/Graphics.hpp>
#include "headers/ColorPalette.h"
#include "headers/Bunny.h"
#include "headers/Platform.h"

int main() {
    auto bunny = Bunny();
    auto platform = Platform();

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
        platform.display(window);
        bunny.display(window);

        window.display();
    }
}
