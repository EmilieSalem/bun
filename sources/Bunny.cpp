#include <iostream>
#include "../headers/Bunny.h"

Bunny::Bunny() : GameObject(
        IDLE_BUNNY_PATH,
        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height/2),
        sf::Vector2f(2.5, 2.5)){
    type = ObjectType::BUNNY;
}

void Bunny::applyBehavior(float loopTime) {
    // initializing velocities
    velocity.x = 0;
    velocity.y += GRAVITY;

    // right | blocked if charging
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if(isGrounded) {velocity.x += HORIZONTAL_GROUND_ACCELERATION;}
        else {velocity.x += HORIZONTAL_JUMP_ACCELERATION;};
    }

    // left | blocked if charging
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if(isGrounded) {velocity.x -= HORIZONTAL_GROUND_ACCELERATION;}
        else {velocity.x -= HORIZONTAL_JUMP_ACCELERATION;};
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
            }
            pressedTime = 0;
        }
    }
}

void Bunny::handleFloorTemp() {
    // TODO temporary code, needs to be changed
    if(position.y >= 1000){
        position.y = 1000;
        velocity.y = 0;
        isGrounded = true;
    }
    if(position.x + getWidth()/2 >= Utils::getScreenWidth()){
        position.x = Utils::getScreenWidth() - getWidth()/2;
        velocity.x = 0;
    }
    if(position.x - getWidth()/2 <= 0){
        position.x = getWidth()/2;
        velocity.x = 0;
    }
}

void Bunny::handleCollision(GameObject &otherObject) {
    if(otherObject.getType() == ObjectType::PLATFORM){
        /* The 3 conditions correspond to:
         * The bunny must be going downwards ( velocity.y >= 0.f )
         * The bunny must be above the platform ( position.y < otherObject.getY() )
         * The bunny must be low enough so that the collision doesn't create a rough "teleportation" ( position.y >= otherObject.getY() - otherObject.getHeight()/3 )
         */
        if(velocity.y >= 0.f && position.y < otherObject.getY() && position.y >= otherObject.getY() - otherObject.getHeight()/3){
            velocity.y = 0.f;
            position.y = otherObject.getY() - otherObject.getHeight()/3; // bunny placed a bit lower for aesthetic purposes
            isGrounded = true;
        }
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