#include <iostream>
#include <SFML/Graphics.hpp>
#include "headers/ColorPalette.h"
#include "headers/Bunny.h"
#include "headers/Platform.h"
#include "headers/Carrot.h"

int main() {

    // score
    int score{0};

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

    // game objects
    auto gameObjects = std::vector<std::unique_ptr<GameObject>>{};

    gameObjects.push_back(std::move(std::make_unique<Platform>(Platform::PlatformLevel::LOW)));
    gameObjects.push_back(std::move(std::make_unique<Platform>(Platform::PlatformLevel::LOW)));
    gameObjects.push_back(std::move(std::make_unique<Platform>(Platform::PlatformLevel::MIDDLE)));
    gameObjects.push_back(std::move(std::make_unique<Platform>(Platform::PlatformLevel::MIDDLE)));
    gameObjects.push_back(std::move(std::make_unique<Platform>(Platform::PlatformLevel::HIGH)));
    gameObjects.push_back(std::move(std::make_unique<Platform>(Platform::PlatformLevel::HIGH)));

    gameObjects.push_back(std::move(std::make_unique<Carrot>(score)));

    gameObjects.push_back(std::move(std::make_unique<Bunny>()));

    // chrono
    sf::Clock chrono{};

    // window
    sf::RenderWindow window{sf::VideoMode(), "bun", sf::Style::Fullscreen};

    while(window.isOpen()){
        auto event = sf::Event();

        while(window.pollEvent(event)){
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
        }

        auto loopTime = chrono.restart().asSeconds();

        window.clear(BEIGE);

        for(auto& gameObject : gameObjects){
            gameObject->update(loopTime);
        }

        for(auto i{0u}; i<gameObjects.size(); ++i){
            for(auto j{0u}; j<gameObjects.size(); ++j){
                if(i != j){
                    gameObjects[i]->testCollision(*gameObjects[j]);
                }
            }
        }

        scoreDisplayVariable.setString(std::to_string(score));

        window.draw(scoreDisplayFixed);
        window.draw(carrotSprite);
        window.draw(scoreDisplayVariable);

        for(auto& gameObjects : gameObjects){
            gameObjects->display(window);
        }

        window.display();
    }
}
