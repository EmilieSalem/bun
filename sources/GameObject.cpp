#include "../headers/GameObject.h"
#include <cmath>
#include <iostream>

GameObject::GameObject(
        const std::string_view &assetPath,
        const sf::Vector2f &initialPosition,
        const sf::Vector2f &p_scale
        ) : position{initialPosition}, scale{p_scale}{
    // loading and applying texture
    texture.loadFromFile(assetPath.data());
    sprite.setTexture(texture);
    sprite.setScale(scale);

    // setting origin and position
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(position.x, position.y);
}

void GameObject::update(const float loopTime) {
    applyBehavior(loopTime);
    position += velocity * loopTime;
    handleFloorTemp();
    sprite.setPosition(position.x, position.y);
    updateRelatedObjects();
}

void GameObject::display(sf::RenderWindow &window) const {
    // TODO Reimplement duplication
    /*auto directions = std::array<sf::Vector2f, 9>{
            sf::Vector2f{-1, 0},
            sf::Vector2f{0, 0},
            sf::Vector2f{1, 0},
    };
    for(auto& direction : directions){
        auto transformation = sf::Transform{};
        transformation.translate(
                direction.x * Utils::getScreenWidth(),
                direction.y * Utils::getScreenHeight()
                );
        window.draw(sprite, transformation);
    }*/
    window.draw(sprite);
    displayRelatedObjects(window);
}

void GameObject::applyBehavior(const float loopTime) {}

void GameObject::testCollision(GameObject &otherObject) {
    if(!otherObject.isRemoved()){
        auto x_distance = static_cast<float>(std::abs(position.x - otherObject.getX()));
        auto y_distance = static_cast<float>(std::abs(position.y - otherObject.getY()));

        if(x_distance < getWidth()/2.4 + otherObject.getWidth()/2.4 && y_distance < getHeight()/2.4 + otherObject.getHeight()/2.4){
            handleCollision(otherObject);
        }
    }
}

void GameObject::handleFloorTemp() {}

void GameObject::updateRelatedObjects() {}

void GameObject::displayRelatedObjects(sf::RenderWindow &window) const {}

void GameObject::handleCollision(GameObject &otherObject) {}

void GameObject::onRemoval() {}

void GameObject::remove() {
    scale = sf::Vector2f(0,0);
    sprite.setScale(scale);
    removed = true;
    onRemoval();
}
