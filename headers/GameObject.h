#ifndef BUN_GAMEOBJECT_H
#define BUN_GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject {
public:
    // constructor
    explicit GameObject(
            std::string_view const& assetPath,
            sf::Vector2f const& initialPosition,
            sf::Vector2f const& scale = sf::Vector2f(1,1)
                    );

    // managing position
    float getRadius() const;
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
    sf::Vector2f objectScale{};

    // physics
    sf::Vector2f position{};
    sf::Vector2f velocity{};
    sf::Vector2f acceleration{};
    virtual void applyBehavior(float loopTime);
};


#endif //BUN_GAMEOBJECT_H
