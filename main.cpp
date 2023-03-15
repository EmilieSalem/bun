#include <iostream>
#include <SFML/Graphics.hpp>

const sf::Color BROWN{sf::Color(100,59,53)};
const sf::Color BEIGE{sf::Color{230, 202, 188}};

void actualiser(sf::RectangleShape& bunny, sf::Text& debugText, float& tempsBoucle, float& pressedTime) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        pressedTime += tempsBoucle;
        debugText.setString("Space pressed for : " + std::to_string(pressedTime) + " s");
    } else{
        pressedTime = 0;
        debugText.setString("Space is not pressed");
    }
}

int main() {
    sf::RenderWindow fenetre{sf::VideoMode{800, 600}, "bun"};

    sf::RectangleShape bunny(sf::Vector2f(50, 50));
    bunny.setFillColor(BROWN);

    sf::Clock chrono{};

    sf::Text debugText{};
    sf::Font police{};
    police.loadFromFile("../assets/debug_font.ttf");
    debugText.setFont(police);
    debugText.setFillColor(BROWN);
    debugText.setString("Hello !");
    debugText.setPosition(15, 15);

    float pressedTime{};

    while (fenetre.isOpen()) {
        auto evenement = sf::Event();

        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == sf::Event::Closed) fenetre.close();
        }

        // bunny position
        bunny.setOrigin(bunny.getLocalBounds().width / 2, bunny.getLocalBounds().height / 2);
        bunny.setPosition(400,550);

        // bunny behavior
        auto tempsBoucle = chrono.restart().asSeconds();
        actualiser(bunny, debugText, tempsBoucle, pressedTime);


        fenetre.clear(BEIGE);
        fenetre.draw(bunny);
        fenetre.draw(debugText);
        fenetre.display();
    }
}




