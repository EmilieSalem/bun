#ifndef BUN_OBJECTMANAGER_H
#define BUN_OBJECTMANAGER_H


#include "GameObject.h"

/// Two screens are kept in memory while playing, an upper one and a lower one.
/// The ObjectManager is responsible for the management of both these screens and the GameObjects they contain.
class ObjectManager {
public :
    // CONSTRUCTOR | INITIALIZATION --------------------------------------------------------------------
    /// Initializes an ObjectManager. Default constructor, no additional behavior.
    ObjectManager() = default;
    /// Initializes a game.
    /// Parameters are reset, and valid Platforms and Carrots are generated for both screens.
    /// The Bunny is generated in the lower screen.
    void initializeGame();

    // GAME LOOP --------------------------------------------------------------------
    /// Updates the state of all GameObjects in the current screen.
    void updateCurrentScreen();
    /// Checks for collisions and applies the collision behavior for all GameObjects in the current screen.
    void handleCollisionsInCurrentScreen();
    /// Displays all GameObjects in the current screen in the given window.
    /// \param window SFML window in which the game runs.
    void displayCurrentScreen(sf::RenderWindow &window);

    // SCREEN MANAGEMENT  --------------------------------------------------------------------
    /// Informs the ObjectManager that the screen needs to be changed,
    /// and saves the Bunny's position and velocity to correctly place it in the new screen.
    /// \param initialBunnyPosition Position at which the Bunny must be placed in the new screen.
    /// \param initialBunnyVelocity Velocity that the Bunny must take in the new screen.
    void changeScreen(sf::Vector2f initialBunnyPosition, sf::Vector2f initialBunnyVelocity);
    /// Indicates if the Bunny is currently in the lower screen.
    /// \return Boolean indicating of the Bunny is in the lower screen.
    [[nodiscard]] inline bool isInLowerScreen() const {return bunnyInLowerScreen;};
    /// Informs the ObjectManager that a new screen needs to be generated,
    /// and saves the Bunny's position and velocity to correctly place it in the new screen.
    /// \param initialBunnyPosition Position at which the Bunny must be placed in the new screen.
    /// \param initialBunnyVelocity Velocity that the Bunny must take in the new screen.
    void generateNewScreen(sf::Vector2f initialBunnyPosition, sf::Vector2f initialBunnyVelocity);
    /// Called at the end of the game loop for screen management.
    /// Can either generate a new screen, switch between upper/lower screen or clear both screens
    /// depending on the state of the game.
    void manageScreens();
    /// Indicates whether there are still carrots that can be picked up in the current screen.
    /// \return Boolean indicating if there are still carrots in the current screen.
    bool noMoreCarrotsInCurrentScreen();

    // LOSE | WIN CONDITION --------------------------------------------------------------------
    /// Gets the current score of the player, aka the number of carrots picked up.
    /// \return Score of the player.
    [[nodiscard]] inline int getScore() const{return score;};
    /// Informs the GameObject that player has lost.
    void gameOver();
    /// Indicates whether the player has lost the game.
    /// \return Boolean indicating if the game is over.
    [[nodiscard]] inline bool gameIsOver() const{return hasLost;};
    /// Indicates whether the player has won the game, aka picked up the required number of carrots.
    /// \return Boolean indicating if the player has won.
    [[nodiscard]] inline bool gameIsWon() const{return score == Utils::SCORE_TO_WIN;};

private :
    // GAME OBJECTS --------------------------------------------------------------------
    /// Array containing unique pointers to all the GameObjects in the lower screen.
    std::vector<std::unique_ptr<GameObject>> gameObjectsLowerScreen{};
    /// Array containing unique pointers to all the GameObjects in the upper screen.
    std::vector<std::unique_ptr<GameObject>> gameObjectsUpperScreen{};
    /// Current score of the player.
    /// Initialized at -1 to compensate the Bunny being initialized on a Carrot at the beginning of the game.
    int score{-1};
    /// Adds a new GameObject to the given screen.
    /// \param object Unique pointer to the GameObject to add.
    /// \param gameObjects Lower screen or upper screen array.
    static void addObject(std::unique_ptr<GameObject> object, std::vector<std::unique_ptr<GameObject>> &gameObjects);
    /// Indicates whether the Bunny is currently in the lower screen.
    bool bunnyInLowerScreen{true};

    // SCREEN GENERATION --------------------------------------------------------------------
    /// Randomly generates 7 Platforms (2 LOW, 3 MIDDLE and 2 HIGH) and adds them to the given screen.
    /// \param gameObjects Lower screen or upper screen array.
    static void generatePlatforms(std::vector<std::unique_ptr<GameObject>> &gameObjects);
    /// Generates a Carrot above each platform in the given screen.
    /// \param gameObjects Lower screen or upper screen array.
    void generateCarrots(std::vector<std::unique_ptr<GameObject>> &gameObjects);
    /// Checks if there is platform overlap in the given screen, and regenerates the invalid platforms.
    /// The validity check loop is repeated an arbitrarily high number of times to make sure all collisions are handled.
    /// \param gameObjects Lower screen or upper screen array.
    static void checkPlatformValidity(std::vector<std::unique_ptr<GameObject>> &gameObjects);
    /// Number of times the Platform validity loop should be repeated.
    int static constexpr NB_COLLISION_TESTS{1000};
    /// Generates a still Bunny in the given screen, on the first Platform of the array.
    /// \param gameObjects Lower screen or upper screen array.
    void generateBunny(std::vector<std::unique_ptr<GameObject>> &gameObjects);
    /// Generates a Bunny in the given screen, with the specified position and velocity.
    /// \param gameObjects Lower screen or upper screen array.
    /// \param initialPosition Position at which the bunny should be generated.
    /// \param initialVelocity Velocity the Bunny should have when generated.
    void generateBunny(std::vector<std::unique_ptr<GameObject>> &gameObjects, sf::Vector2f initialPosition, sf::Vector2f initialVelocity = sf::Vector2f(0,0));

    // GAME LOOP --------------------------------------------------------------------
    /// Updates the state of all the GameObjects in the given screen.
    /// \param gameObjects Lower screen or upper screen array.
    void update(std::vector<std::unique_ptr<GameObject>> &gameObjects);
    /// Checks for collisions and applies the collision behavior for all GameObjects in the given screen.
    /// \param gameObjects Lower screen or upper screen array.
    static void handleCollisions(std::vector<std::unique_ptr<GameObject>> &gameObjects);
    /// Displays all GameObjects in the given screen in the specified window.
    /// \param window SFML window in which the game runs.
    /// \param gameObjects Lower screen or upper screen array.
    static void display(sf::RenderWindow &window, std::vector<std::unique_ptr<GameObject>> &gameObjects);
    /// Indicates whether there are still carrots that can be picked up in the given screen.
    /// \param gameObjects Lower screen or upper screen array.
    /// \return Boolean indicating if there are still carrots in the given screen.
    static bool noMoreCarrots(std::vector<std::unique_ptr<GameObject>> &gameObjects);
    /// Chronometer used to measure the game loop time (necessary to update the Bunny).
    sf::Clock chrono{};

    // SCREEN MANAGEMENT --------------------------------------------------------------------
    /// Indicates whether the lower screen needs to be cleared and replaced by the upper screen, as a new screen is generated.
    bool toClear{false};
    /// Indicates whether the Bunny needs to switch between the lower and upper screen.
    bool toChange{false};
    /// Position at which the Bunny should be generated when changing screens.
    sf::Vector2f bunnyStartPosition{};
    /// Velocity the Bunny should have when generated in a new screen.
    sf::Vector2f bunnyStartVelocity{};

    // LOSE | WIN CONDITION --------------------------------------------------------------------
    /// Indicates whether the player has lost the game.
    bool hasLost{false};
};

#endif //BUN_OBJECTMANAGER_H
