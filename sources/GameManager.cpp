#include "../headers/GameManager.h"

// LOOPS --------------------------------------------------------------------

void GameManager::startGame() {
    gameState = GameStates::PLAYING;
    objectManager.initializeGame();
}

void GameManager::runGameLoop(sf::RenderWindow &window) {
    // Updates and collisions
    objectManager.updateCurrentScreen();
    objectManager.handleCollisionsInCurrentScreen();

    // UI
    uiManager.updateScoreDisplay(objectManager.getScore());
    uiManager.displayPLaying(window, objectManager.noMoreCarrotsInCurrentScreen());

    // Display
    objectManager.displayCurrentScreen(window);
    window.display();

    // Screen management
    updateGameStateAndScreen();
}

void GameManager::runStartLoop(sf::RenderWindow &window) {
    uiManager.displayTitleScreen(window);
    window.display();
}

void GameManager::runContinueLoop(sf::RenderWindow& window) {
    // displays the continue option with the right message
    if(gameState == GameStates::GAME_OVER) uiManager.displayContinueMenu(window, true);
    if(gameState == GameStates::GAME_WON) uiManager.displayContinueMenu(window, false);
    window.display();

}
void GameManager::processChoice() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
        if(uiManager.getChoice()){ // yes option | new game starts
            startGame();
        } else{ // no option | back to title screen
            gameState = GameStates::START;
        }
    }
}

// GAME STATES --------------------------------------------------------------------

void GameManager::updateGameStateAndScreen() {
    objectManager.manageScreens(); // screen management
    if(objectManager.gameIsOver()) {
        gameState = GameStates::GAME_OVER;
    }
    if(objectManager.gameIsWon()) {
        gameState = GameStates::GAME_WON;
    }
}
