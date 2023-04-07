#include <random>
#include <chrono>
#include "../headers/Platform.h"

// CONSTRUCTOR  --------------------------------------------------------------------

Platform::Platform(PlatformLevel p_platformLevel) : GameObject(
        PLATFORM_PATH,
        sf::Vector2f(Utils::getScreenWidth()/2, Utils::getScreenHeight()/2),
        sf::Vector2f(2.2, 2.2)),
        platformLevel{p_platformLevel} {
    type = ObjectType::PLATFORM;
    randomizePosition(); // generates the random position
    sprite.setPosition(position);
}

// POSITION  --------------------------------------------------------------------

void Platform::randomizePosition() {
    // generating a seed with the current time for true randomness
    std::default_random_engine random_engine;
    unsigned long int current_time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    random_engine.seed(current_time);

    // creating the generator with the seed
    std::mt19937 generator{random_engine()};

    // horizontal distribution
    auto horizontalDistribution = std::uniform_real_distribution(getWidth()/2, Utils::getScreenWidth() - getWidth()/2);

    // vertical distribution
    auto vertical_inf = 0.f;
    auto vertical_sup = 0.f;

    switch(platformLevel){ // different bounds depending on the part of the screen
        case PlatformLevel::LOW: // bottom third of the screen
            vertical_inf = 2 * Utils::getScreenHeight()/3 + getHeight()/2;
            vertical_sup = Utils::getScreenHeight() - getHeight()/2 - VERTICAL_BORDER;
            break;
        case PlatformLevel::MIDDLE: // middle third of the screen
            vertical_inf = Utils::getScreenHeight()/3 + getHeight()/2;
            vertical_sup = 2 * Utils::getScreenHeight()/3 - getHeight()/2;
            break;
        case PlatformLevel::HIGH : // top third of the screen
            vertical_inf = VERTICAL_BORDER;
            vertical_sup = Utils::getScreenHeight()/3 - getHeight()/2;
            break;
    }

    auto verticalDistribution = std::uniform_real_distribution(vertical_inf, vertical_sup);

    // generating and setting the randomized position
    position = sf::Vector2f(horizontalDistribution(generator), verticalDistribution(generator));
}

// COLLISION  --------------------------------------------------------------------

void Platform::handleCollision(GameObject &otherObject) {
    if(otherObject.getType() == ObjectType::PLATFORM){ // if there is overlap with another platform
        randomizePosition(); // generate a new position
        sprite.setPosition(position);
    }
}
