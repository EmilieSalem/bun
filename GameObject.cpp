#include "GameObject.h"

GameObject::GameObject(
        const std::string_view &assetPath,
        const sf::Vector2f &initialPosition,
        const sf::Vector2f &scale
        ) : position{initialPosition}, objectScale{scale}{
    // loading and applying texture
    texture.loadFromFile(assetPath.data());
    sprite.setTexture(texture);
    sprite.setScale(objectScale);

    // setting origin and position
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height);
    sprite.setPosition(position.x, position.y);
}

float GameObject::getRadius() const {
    return sprite.getGlobalBounds().height/2.4f;
}

void GameObject::update(const float loopTime) {
    applyBehavior(loopTime);
    position += velocity * loopTime;
    sprite.setPosition(position.x, position.y);
}

// TODO change to only apply the duplication behavior horizontally
void GameObject::display(sf::RenderWindow &window) const {
    auto directions = std::array<sf::Vector2f, 9>{
            sf::Vector2f{-1, 1},
            sf::Vector2f{0, -1},
            sf::Vector2f{1, -1},
            sf::Vector2f{-1, 0},
            sf::Vector2f{0, 0},
            sf::Vector2f{1, 0},
            sf::Vector2f{-1, 1},
            sf::Vector2f{0, 1},
            sf::Vector2f{1, 1}
    };
    for(auto& direction : directions){
        auto transformation = sf::Transform{};
        transformation.translate(
                direction.x * static_cast<float>(sf::VideoMode::getDesktopMode().width),
                direction.y * static_cast<float>(sf::VideoMode::getDesktopMode().height)
                );
        window.draw(sprite, transformation);
    }
}

void GameObject::applyBehavior(const float loopTime) { }
