#include "../headers/GameObject.h"
#include <cmath>
#include <iostream>

// CONSTRUCTOR --------------------------------------------------------------------

GameObject::GameObject(const std::string_view &assetPath,
                       const sf::Vector2f &initialPosition,
                       const sf::Vector2f &p_scale)
                       : position{initialPosition}, scale{p_scale}{
    texture.loadFromFile(assetPath.data());
    sprite.setTexture(texture);
    sprite.setScale(scale);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(position.x, position.y);
}

// UPDATE | DISPLAY --------------------------------------------------------------------

void GameObject::update(const float loopTime) {
    applyBehavior(loopTime); // applying object-specific behavior (gravity, user input...)
    position += velocity * loopTime;
    manageScreenLimits(); // enforcing screen limits may change the position
    sprite.setPosition(position.x, position.y);
    updateRelatedObjects();
}

void GameObject::display(sf::RenderWindow &window) const {
    // TODO Reimplement duplication
    window.draw(sprite);
    displayRelatedObjects(window);
}

void GameObject::remove() {
    scale = sf::Vector2f(0,0);
    sprite.setScale(scale);
    removed = true;
    onRemoval();
}

// COLLISIONS --------------------------------------------------------------------

void GameObject::testCollision(GameObject &otherObject) {
    if(!otherObject.isRemoved()){ // e.g. to avoid colliding with removed carrots
        auto x_distance = static_cast<float>(std::abs(position.x - otherObject.getX()));
        auto y_distance = static_cast<float>(std::abs(position.y - otherObject.getY()));

        // box collision with a bit of tolerance (dividing by 2.4 instead of 2)
        if(x_distance < getWidth()/2.4 + otherObject.getWidth()/2.4 && y_distance < getHeight()/2.4 + otherObject.getHeight()/2.4){
            handleCollision(otherObject);
        }
    }
}

// VIRTUAL METHODS --------------------------------------------------------------------

void GameObject::applyBehavior(const float loopTime) {}

void GameObject::manageScreenLimits() {}

void GameObject::updateRelatedObjects() {}

void GameObject::displayRelatedObjects(sf::RenderWindow &window) const {}

void GameObject::handleCollision(GameObject &otherObject) {}

void GameObject::onRemoval() {}
