#include <iostream>
#include "../headers/Bunny.h"

// CONSTRUCTOR --------------------------------------------------------------------

Bunny::Bunny(sf::Vector2f p_initialPosition, ObjectManager &p_objectManager, sf::Vector2f p_initialVelocity) : GameObject(
        IDLE_BUNNY_PATH,
        p_initialPosition,
        sf::Vector2f(2.5, 2.5)),
        objectManager{p_objectManager}{
    type = ObjectType::BUNNY;
    velocity = p_initialVelocity;
}

// CONTROLS | PHYSICS --------------------------------------------------------------------

void Bunny::applyBehavior(float loopTime) {
    // initializing velocities
    velocity.x = 0;
    velocity.y += GRAVITY;

    // right | blocked if charging
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if(isGrounded) {velocity.x += HORIZONTAL_GROUND_ACCELERATION;}
        else {velocity.x += HORIZONTAL_JUMP_ACCELERATION;}
    }

    // left | blocked if charging
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if(isGrounded) {velocity.x -= HORIZONTAL_GROUND_ACCELERATION;}
        else {velocity.x -= HORIZONTAL_JUMP_ACCELERATION;}
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

// COLLISIONS --------------------------------------------------------------------

void Bunny::manageScreenLimits() {
    // walls | movement is stopped
    if(position.x + getWidth()/2 >= Utils::getScreenWidth()){
        position.x = Utils::getScreenWidth() - getWidth()/2;
        velocity.x = 0;
    }
    if(position.x - getWidth()/2 <= 0){
        position.x = getWidth()/2;
        velocity.x = 0;
    }

    // bottom
    if(position.y >= Utils::getScreenHeight() + getHeight()){
        sf::Vector2f newPosition = sf::Vector2f{position.x, position.y-Utils::getScreenHeight() - getHeight()};
        if(objectManager.isInLowerScreen()){ // loses the game
            objectManager.gameOver();
        } else { // goes to lower screen
            objectManager.changeScreen(newPosition, velocity);
        }
    }

    // top
    if(position.y <= 0 - getHeight()){
        sf::Vector2f newPosition = sf::Vector2f{position.x, position.y+Utils::getScreenHeight() + getHeight()};
        if(objectManager.isInLowerScreen()){ // goes to upper screen
            objectManager.changeScreen(newPosition, velocity);
        } else { // // create new screen
            objectManager.generateNewScreen(newPosition, velocity);
        }
    }
}

void Bunny::handleCollision(GameObject &otherObject) {
    switch(otherObject.getType()){

        case ObjectType::BUNNY: // not necessary since we only have one bunny on the screen at the moment
            break;

        case ObjectType::PLATFORM:
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
            break;

        case ObjectType::CARROT:
            // need the bunny to be much closer to the carrot before it disappears, otherwise it looks very jarring
            // TODO write better code for this behavior
            if(static_cast<float>(std::abs(position.x - otherObject.getX())) < getWidth()/5 + otherObject.getWidth()/5
            && static_cast<float>(std::abs(position.y - otherObject.getY())) < getHeight()/5 + otherObject.getHeight()/5){
                otherObject.remove(); // picks up the carrot
            }
            break;

        case ObjectType::OTHER:
            break;

    }
}

// AESTHETIC --------------------------------------------------------------------

void Bunny::loadTexture(Bunny::BunnyStates bunnyState) {
    switch(bunnyState){ // loading the right asset depending on the bunny state
        case BunnyStates::IDLE : texture.loadFromFile(IDLE_BUNNY_PATH.data()); break;
        case BunnyStates::CHARGING : texture.loadFromFile(CHARGING_BUNNY_PATH.data()); break;
    }
}

// RELATED OBJECTS --------------------------------------------------------------------

void Bunny::updateRelatedObjects() {
    chargeBar.updatePosition(position.x, position.y);
}

void Bunny::displayRelatedObjects(sf::RenderWindow &window) const {
    chargeBar.display(window);
}
