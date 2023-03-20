#include <iostream>
#include <random>
#include <chrono>
#include "../headers/Platform.h"

Platform::Platform(PlatformLevel p_platformLevel) : GameObject(
        PLATFORM_PATH,
        sf::Vector2f(Utils::getScreenWidth()/2, Utils::getScreenHeight()/2),
        sf::Vector2f(2.2, 2.2)),
                                                    platformLevel{p_platformLevel}
        {
    randomizePosition();
    sprite.setPosition(position);
}

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
        case PlatformLevel::LOW :
            vertical_inf = 2 * Utils::getScreenHeight()/3 + getHeight()/2;
            vertical_sup = Utils::getScreenHeight() - getHeight()/2 - VERTICAL_BORDER;
            break;
        case PlatformLevel::MIDDLE:
            vertical_inf = Utils::getScreenHeight()/3 + getHeight()/2;
            vertical_sup = 2 * Utils::getScreenHeight()/3 - getHeight()/2;
            break;
        case PlatformLevel::HIGH :
            vertical_inf = VERTICAL_BORDER;
            vertical_sup = Utils::getScreenHeight()/3 - getHeight()/2;
            break;
    }

    auto verticalDistribution = std::uniform_real_distribution(vertical_inf, vertical_sup);

    // generating and setting the randomized position
    position = sf::Vector2f(horizontalDistribution(generator), verticalDistribution(generator));
}