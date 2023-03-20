#include <iostream>
#include "../headers/Bunny.h"

Bunny::Bunny() : GameObject(
        IDLE_BUNNY_PATH,
        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height/2),
        sf::Vector2f(2.5, 2.5)){
}

void Bunny::applyBehavior(float loopTime) {
    // initializing velocities
    velocity.x = 0;
    velocity.y += GRAVITY;

    // right | blocked if charging
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        velocity.x += HORIZONTAL_ACCELERATION;
    }

    // left | blocked if charging
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        velocity.x -= HORIZONTAL_ACCELERATION;
    }

    // jump | only works if on the ground
    if(isGrounded){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            // charging
            loadTexture(BunnyStates::CHARGING);
            pressedTime += loopTime;
            jumpForce = pressedTime * MAX_JUMP_FORCE * CHARGE_ACCELERATION_COEFF;
            if(jumpForce > MAX_JUMP_FORCE) jumpForce = MAX_JUMP_FORCE;
            chargeBar.updateProgress(-jumpForce/MAX_JUMP_FORCE);
        } else {
            if(pressedTime != 0){ // means that the space bar was just released
                // jumping
                loadTexture(BunnyStates::IDLE);
                velocity.y = -jumpForce;
                jumpForce = 0;
                isGrounded = false;
                chargeBar.updateProgress(0);
                // horizontal direction of the jump
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) velocity.x = HORIZONTAL_ACCELERATION;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) velocity.x = -HORIZONTAL_ACCELERATION;
            }
            pressedTime = 0;
        }
    }
}

void Bunny::handleCollision() {
    // TODO temporary code, needs to be changed
    if(position.y >= 1000){
        position.y = 1000;
        velocity.y = 0;
        isGrounded = true;
    }
}

void Bunny::loadTexture(Bunny::BunnyStates bunnyState) {
    // loading the right asset depending on the bunny state
    switch(bunnyState){
        case BunnyStates::IDLE : texture.loadFromFile(IDLE_BUNNY_PATH.data()); break;
        case BunnyStates::CHARGING : texture.loadFromFile(CHARGING_BUNNY_PATH.data()); break;
    }
}

void Bunny::updateRelatedObjects() {
    // update the bunny
    GameObject::updateRelatedObjects();
    // update the charge bar
    chargeBar.updatePosition(position.x, position.y);
}

void Bunny::displayRelatedObjects(sf::RenderWindow &window) const {
    // display the bunny
    GameObject::displayRelatedObjects(window);
    // display the charge bar
    chargeBar.display(window);
}