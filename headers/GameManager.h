#ifndef BUN_GAMEMANAGER_H
#define BUN_GAMEMANAGER_H

#include "ObjectManager.h"
#include "UIManager.h"

class GameManager {
public:
    GameManager() = default;

    // manage game states
    enum class GameStates{PLAYING, START, GAME_OVER, GAME_WON};
    inline GameStates currentGameState(){return gameState;};

    // run game
    void startGame();
    void runGameLoop(sf::RenderWindow& window);
    void runContinueLoop(sf::RenderWindow& window);
    void runStartLoop(sf::RenderWindow& window);

    // manage continue choice
    void processChoice();

private:
    GameStates gameState{GameStates::START};
    ObjectManager objectManager{};
    UIManager uiManager{};

    void updateGameStateAndScreen();
};


#endif //BUN_GAMEMANAGER_H