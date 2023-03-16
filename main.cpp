#include <iostream>
#include <SFML/Graphics.hpp>
#include "ColorPalette.h"
#include "GameObject.h"

int main() {
    // test code to display a bunny in the middle of the screen
    auto bunny = GameObject(
            "../assets/bunny_idle.png",
            sf::Vector2f(sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height/2),
            sf::Vector2f(2.5, 2.5));

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
        bunny.display(window);

        window.display();
    }
}
