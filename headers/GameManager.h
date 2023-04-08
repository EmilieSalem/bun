#ifndef BUN_GAMEMANAGER_H
#define BUN_GAMEMANAGER_H

#include "ObjectManager.h"
#include "UIManager.h"

/// The GameManager is responsible for switching between the different menus of the game and triggering the appropriate game loops.
///  It uses both an ObjectManager and a UIManager.
class GameManager {
public:
    // CONSTRUCTOR --------------------------------------------------------------------
    /// Initializes a GameManager. Default constructor, no additional behavior.
    GameManager() = default;

    // GAME STATES --------------------------------------------------------------------
    /// Defines the different game states, aka the types of screens/menus accessible to the player.
    enum class GameStates{PLAYING, START, GAME_OVER, GAME_WON};
    /// Gets the current game state.
    /// \return Current game state. Can be PLAYING, START, GAME_OVER or GAME_WON.
    inline GameStates currentGameState(){return gameState;};

    // LOOPS --------------------------------------------------------------------
    /// Initializes a new game and changes the game state to PLAYING.
    void startGame();
    /// Runs a game loop, aka updates, handles collisions and displays the GameObjects in the current screen.
    /// Also updates and displays the UI.
    /// \param window SFML window in which the game runs.
    void runGameLoop(sf::RenderWindow& window);
    /// Runs a UI loop that displays the title screen.
    /// \param window SFML window in which the game runs.
    void runStartLoop(sf::RenderWindow& window);
    /// Runs a UI loop that displays either a game over or a winning message,
    /// with the option to continue playing or not.
    /// \param window SFML window in which the game runs.
    void runContinueLoop(sf::RenderWindow& window);
    /// Checks for user input in the continue loop, to either restart a game or go back to the title screen.
    void processChoice();

private:
    // GAME STATES --------------------------------------------------------------------
    /// Current state of the game. Initialized at START, aka on the title screen.
    GameStates gameState{GameStates::START};
    /// Manages screens and changes the game state accordingly if the player has won (GAME_WON) or lost (GAME_LOST).
    void updateGameStateAndScreen();

    // MANAGERS --------------------------------------------------------------------
    /// GameManager used to run game loops.
    ObjectManager objectManager{};
    /// UIManager used to display the UI.
    UIManager uiManager{};
};


#endif //BUN_GAMEMANAGER_H
