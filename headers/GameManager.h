#ifndef BUN_GAMEMANAGER_H
#define BUN_GAMEMANAGER_H


#include "ObjectManager.h"
#include "UIManager.h"

class GameManager {
public:
    GameManager() = default;

    // manage game states
    enum class GameStates{PLAYING, START_MENU, GAME_OVER_MENU};
    inline GameStates currentGameState(){return gameState;};

    // run game
    void startGame();
    void runGameLoop(sf::RenderWindow& window);

private:
    GameStates gameState{GameStates::START_MENU};
    ObjectManager objectManager{};
    UIManager uiManager{};
};


#endif //BUN_GAMEMANAGER_H
