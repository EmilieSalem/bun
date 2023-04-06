#include "../headers/GameManager.h"

void GameManager::startGame() {
    gameState = GameStates::PLAYING;
    objectManager.initializeGame();
}

void GameManager::runGameLoop(sf::RenderWindow &window) {
    objectManager.updateCurrentScreen();
    objectManager.handleCollisionsInCurrentScreen();
    uiManager.updateScoreDisplay(objectManager.getScore());

    uiManager.display(window, objectManager.noMoreCarrotsInCurrentScreen(), objectManager.gameIsOver(), objectManager.gameIsWon());
    objectManager.displayCurrentScreen(window);

    window.display();

    objectManager.updateScreen();
}
