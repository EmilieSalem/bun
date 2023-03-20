#ifndef BUN_GAMEOBJECT_H
#define BUN_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "../headers/Utils.h"

class GameObject {
public:
    // constructor
    explicit GameObject(
            std::string_view const& assetPath,
            sf::Vector2f const& initialPosition,
            sf::Vector2f const& p_scale = sf::Vector2f(1, 1)
                    );

    // managing position
    inline float getWidth() const {return sprite.getGlobalBounds().width;};
    inline float getHeight() const {return sprite.getGlobalBounds().height;};
    void update(float loopTime);
    void display(sf::RenderWindow& window) const;

    // disabling copy
    GameObject(GameObject const& other) = delete;
    void operator=(GameObject const& other) = delete;

    // creating virtual destructor
    virtual ~GameObject() = default;

protected:
    // appearance
    sf::Sprite sprite{};
    sf::Texture texture{};
    sf::Vector2f scale{};

    // physics
    sf::Vector2f position{};
    sf::Vector2f velocity{};
    virtual void applyBehavior(float loopTime);
    virtual void handleCollision();

    // to display elements related to the GameObject, such as a ChargeBar
    virtual void updateRelatedObjects();
    virtual void displayRelatedObjects(sf::RenderWindow& window) const;
};


#endif //BUN_GAMEOBJECT_H
