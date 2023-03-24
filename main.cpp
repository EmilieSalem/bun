#include <iostream>
#include <SFML/Graphics.hpp>
#include "headers/ColorPalette.h"
#include "headers/Bunny.h"
#include "headers/Platform.h"
#include "headers/Carrot.h"
#include "headers/ObjectManager.h"

int main() {
    // score display
    sf::Text scoreDisplayFixed{};
    sf::Text scoreDisplayVariable{};
    sf::Sprite carrotSprite{};
    sf::Texture carrotTexture{};
    sf::Font police{};
    police.loadFromFile("../assets/Early_GameBoy.ttf");

    // fixed part
    scoreDisplayFixed.setFont(police);
    scoreDisplayFixed.setCharacterSize(70);
    scoreDisplayFixed.setFillColor(BROWN);
    scoreDisplayFixed.setPosition(25, 25);
    scoreDisplayFixed.setString("SCORE : ");

    // carrot display
    carrotTexture.loadFromFile("../assets/carrot.png");
    carrotSprite.setTexture(carrotTexture);
    carrotSprite.setScale(sf::Vector2f(2.5,2.5));
    carrotSprite.setOrigin(carrotSprite.getLocalBounds().width / 2, 0);
    carrotSprite.setPosition(25 + scoreDisplayFixed.getLocalBounds().width,15);

    // variable part
    scoreDisplayVariable.setFont(police);
    scoreDisplayVariable.setCharacterSize(70);
    scoreDisplayVariable.setFillColor(BROWN);
    scoreDisplayVariable.setPosition(75 + carrotSprite.getLocalBounds().width + scoreDisplayFixed.getLocalBounds().width, 25);

    // window
    sf::RenderWindow window{sf::VideoMode(), "bun", sf::Style::Fullscreen};

    ObjectManager objectManager{};
    objectManager.initializeGame();

    while(window.isOpen()){
        auto event = sf::Event();

        while(window.pollEvent(event)){
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
        }

        window.clear(BEIGE);

        objectManager.update();
        objectManager.handleCollisions();

        scoreDisplayVariable.setString(std::to_string(objectManager.getScore()));

        window.draw(scoreDisplayFixed);
        window.draw(carrotSprite);
        window.draw(scoreDisplayVariable);

        objectManager.display(window);

        window.display();
    }
}
