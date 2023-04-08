 #include <SFML/Graphics.hpp>
#include "headers/ColorPalette.h"
#include "headers/GameManager.h"

 int main() {

    // SFML window in which the game runs
    sf::RenderWindow window{sf::VideoMode(), "bun", sf::Style::Fullscreen};

    // for management of menus, objects and UI
    GameManager gameManager{};

    while(window.isOpen()){
        auto event = sf::Event();

        while(window.pollEvent(event)){
            // to exit the game
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();

            // to start the game when on the title screen
            if(event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::Enter && gameManager.currentGameState() == GameManager::GameStates::START) gameManager.startGame();
        }

        // clearing the window of the previous loop's display + setting the color
        window.clear(BEIGE);

        switch(gameManager.currentGameState()) {

            case GameManager::GameStates::PLAYING:
                gameManager.runGameLoop(window); // runs the game
                break;

            case GameManager::GameStates::START:
                gameManager.runStartLoop(window); // title screen
                break;

            case GameManager::GameStates::GAME_OVER:
            case GameManager::GameStates::GAME_WON:
                gameManager.runContinueLoop(window); // displays the same continue menu but with a different message
                gameManager.processChoice();
                break;
        }
    }

}