#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window{sf::VideoMode(), "bun", sf::Style::Fullscreen};
    while(window.isOpen()){
        auto event = sf::Event();

        while(window.pollEvent(event)){
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
        }

        window.clear();
        window.display();
    }
}
