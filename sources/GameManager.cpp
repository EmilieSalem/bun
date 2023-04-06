#include "../headers/GameManager.h"

void GameManager::startGame() {
    gameState = GameStates::PLAYING;
    objectManager.initializeGame();
}

void GameManager::runGameLoop(sf::RenderWindow &window) {
    objectManager.updateCurrentScreen();
    objectManager.handleCollisionsInCurrentScreen();
    uiManager.updateScoreDisplay(objectManager.getScore());

    uiManager.displayPLaying(window, objectManager.noMoreCarrotsInCurrentScreen());
    objectManager.displayCurrentScreen(window);

    window.display();

    updateGameStateAndScreen();
}

void GameManager::runDisplayLoop(sf::RenderWindow& window) {
    if(gameState == GameStates::GAME_OVER) uiManager.displayContinueMenu(window, true);
    if(gameState == GameStates::GAME_WON) uiManager.displayContinueMenu(window, false);
    window.display();
}

void GameManager::updateGameStateAndScreen() {
    objectManager.updateScreen();
    if(objectManager.gameIsOver()) {
        gameState = GameStates::GAME_OVER;
    }
    if(objectManager.gameIsWon()) {
        gameState = GameStates::GAME_WON;
    }
}

void GameManager::processChoice() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
        if(uiManager.getChoice()){
            startGame();
        } else{
            gameState = GameStates::START;
        }
    }
}
