#include "../headers/Bunny.h"

Bunny::Bunny() : GameObject(
        IDLE_BUNNY_PATH,
        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height/2),
        sf::Vector2f(2.5, 2.5)){
}

void Bunny::applyBehavior(float loopTime) {
    // initializing the velocity
    velocity =  sf::Vector2f(0,0);

    // right movement (blocked if charging)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        velocity.x += HORIZONTAL_ACCELERATION;
    }

    // left movement (blocked if charging)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        velocity.x -= HORIZONTAL_ACCELERATION;
    }
}
