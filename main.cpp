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
    sf::Text scoreDisplay{};
    sf::Font police{};
    police.loadFromFile("../assets/Early_GameBoy.ttf");
    scoreDisplay.setFont(police);
    scoreDisplay.setCharacterSize(70);
    scoreDisplay.setFillColor(BROWN);
    scoreDisplay.setPosition(15, 15);

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

        for(auto& gameObjects : gameObjects){
            gameObjects->display(window);
        }

        scoreDisplay.setString("SCORE : " + std::to_string(score));
        window.draw(scoreDisplay);

        window.display();
    }
}
