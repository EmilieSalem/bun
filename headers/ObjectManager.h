#ifndef BUN_OBJECTMANAGER_H
#define BUN_OBJECTMANAGER_H


#include "GameObject.h"

class ObjectManager {
public :
    // constructor
    ObjectManager();

    // initialization
    void initializeGame();

    // screen management
    void changeScreen(sf::Vector2f initialBunnyPosition, sf::Vector2f initialBunnyVelocity);
    inline bool isInLowerScreen() const {return bunnyInLowerScreen;};
    void generateNewScreen(sf::Vector2f initialBunnyPosition, sf::Vector2f initialBunnyVelocity);
    void updateScreen();

    // loop behavior
    void updateCurrentScreen();
    void handleCollisionsInCurrentScreen();
    void displayCurrentScreen(sf::RenderWindow &window);

    // score
    inline int getScore() const{return score;};

    // level state
    bool noMoreCarrotsInCurrentScreen();

    // losing
    void gameOver();
    inline bool gameIsOver(){return hasLost;};

private :
    // objects
    std::vector<std::unique_ptr<GameObject>> gameObjectsLowerScreen{};
    std::vector<std::unique_ptr<GameObject>> gameObjectsUpperScreen{};
    int score{-1};
    static void addObject(std::unique_ptr<GameObject> object, std::vector<std::unique_ptr<GameObject>> &gameObjects);
    bool bunnyInLowerScreen{true};

    // initialization
    static void generatePlatforms(std::vector<std::unique_ptr<GameObject>> &gameObjects);
    void generateCarrots(std::vector<std::unique_ptr<GameObject>> &gameObjects);
    static void checkPlatformValidity(std::vector<std::unique_ptr<GameObject>> &gameObjects);
    void generateBunny(std::vector<std::unique_ptr<GameObject>> &gameObjects);
    void generateBunny(std::vector<std::unique_ptr<GameObject>> &gameObjects, sf::Vector2f initialPosition, sf::Vector2f initialVelocity = sf::Vector2f(0,0));
    int static constexpr NB_COLLISION_TESTS{1000};

    // operations on all objects
    void update(std::vector<std::unique_ptr<GameObject>> &gameObjects);
    static void handleCollisions(std::vector<std::unique_ptr<GameObject>> &gameObjects);
    static void display(sf::RenderWindow &window, std::vector<std::unique_ptr<GameObject>> &gameObjects);
    static bool noMoreCarrots(std::vector<std::unique_ptr<GameObject>> &gameObjects);

    // game loops
    sf::Clock chrono{};

    // clear
    bool toClear{false};
    bool toChange{false};
    sf::Vector2f bunnyStartPosition{};
    sf::Vector2f bunnyStartVelocity{};

    // losing condition
    bool hasLost{false};
};

#endif //BUN_OBJECTMANAGER_H
