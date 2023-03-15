#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow fenetre{sf::VideoMode{800, 600}, "bun"};
    sf::RectangleShape bunny(sf::Vector2f(50, 50));
    bunny.setFillColor(sf::Color(100,59,53));

    while (fenetre.isOpen()) {
        auto evenement = sf::Event();

        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == sf::Event::Closed) fenetre.close();
        }

        fenetre.clear(sf::Color{230, 202, 188});
        fenetre.draw(bunny);
        fenetre.display();
    }
}