#ifndef BUN_OBJECTMANAGER_H
#define BUN_OBJECTMANAGER_H


#include "GameObject.h"

class ObjectManager {
public :
    // constructor
    ObjectManager();

    // initialization
    void initializeGame();

    // new screen
    void generateNewScreen(sf::Vector2f initialBunnyPosition);
    void clearAndGenerate();

    // loop behavior
    void update();
    void handleCollisions();
    void display(sf::RenderWindow &window);

    // score
    inline int getScore() const{return score;};

    // level state
    bool noMoreCarrots();

private :
    // objects
    std::vector<std::unique_ptr<GameObject>> gameObjects{};
    int score{-1};
    void addObject(std::unique_ptr<GameObject> object);

    // initialization
    void generatePlatforms();
    void generateCarrots();
    void checkPlatformValidity();
    void generateBunny();
    void generateBunny(sf::Vector2f initialPosition);
    int static constexpr NB_COLLISION_TESTS{1000};

    // game loops
    sf::Clock chrono{};

    // clear
    bool toClear{false};
    sf::Vector2f bunnyStartPosition{};
};

#endif //BUN_OBJECTMANAGER_H
