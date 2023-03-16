#include <iostream>
#include "../headers/Bunny.h"

Bunny::Bunny() : GameObject(
        IDLE_BUNNY_PATH,
        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height/2),
        sf::Vector2f(2.5, 2.5)){
}

void Bunny::applyBehavior(float loopTime) {
    // initializing the velocity
    velocity.x = 0;

    // right movement (blocked if charging)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        velocity.x += HORIZONTAL_ACCELERATION;
    }

    // left movement (blocked if charging)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        velocity.x -= HORIZONTAL_ACCELERATION;
    }

    // jump
    if(isGrounded){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            texture.loadFromFile(CHARGING_BUNNY_PATH.data());
            sprite.setTexture(texture);
            pressedTime += loopTime;
            jumpForce = pressedTime * MAX_JUMP_FORCE * CHARGE_ACCELERATION_COEFF;
            if(jumpForce > MAX_JUMP_FORCE) jumpForce = MAX_JUMP_FORCE;
        } else {
            if(pressedTime != 0){
                texture.loadFromFile(IDLE_BUNNY_PATH.data());
                sprite.setTexture(texture);
                velocity.y = -jumpForce;
                jumpForce = 0;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) velocity.x = HORIZONTAL_ACCELERATION;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) velocity.x = -HORIZONTAL_ACCELERATION;
                isGrounded = false;
            }
            pressedTime = 0;
        }
    }

    // Gravity
    velocity.y += GRAVITY;
}

void Bunny::handleCollision() {
    if(position.y >= 600){
        position.y = 600;
        velocity.y = 0;
        isGrounded = true;
    }
}
