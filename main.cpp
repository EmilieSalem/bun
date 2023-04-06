 #include <SFML/Graphics.hpp>
#include "headers/ColorPalette.h"
#include "headers/GameManager.h"

 int main() {
    // window
    sf::RenderWindow window{sf::VideoMode(), "bun", sf::Style::Fullscreen};

    GameManager gameManager{};

    while(window.isOpen()){
        auto event = sf::Event();

        while(window.pollEvent(event)){
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::Enter && gameManager.currentGameState() == GameManager::GameStates::START) gameManager.startGame();
        }

        window.clear(BEIGE);
        switch(gameManager.currentGameState()) {

            case GameManager::GameStates::PLAYING:
                gameManager.runGameLoop(window);
                break;

            case GameManager::GameStates::START:
                window.display();
                break;

            case GameManager::GameStates::GAME_OVER:
                gameManager.runDisplayLoop(window);
                gameManager.processChoice();
                break;

            case GameManager::GameStates::GAME_WON:
                gameManager.runDisplayLoop(window);
                gameManager.processChoice();
                break;
        }
    }
}