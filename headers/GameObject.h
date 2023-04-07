#ifndef BUN_GAMEOBJECT_H
#define BUN_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "../headers/Utils.h"

/// Defines the different types of GameObjects.
enum class ObjectType{BUNNY, PLATFORM, CARROT, OTHER};

/// An element of the game, represented by a sprite.
/// The GameObject class only defines overarching methods, specific behaviors are defined in its subclasses.
class GameObject {
public:

    // CONSTRUCTOR | DESTRUCTOR --------------------------------------------------------------------
    /// Initializes a GameObject.
    /// \param assetPath Path to the image file used as a texture for the sprite.
    /// \param initialPosition Initial position vector.
    /// \param p_scale Scale of the sprite. Defaults to (1,1).
    explicit GameObject(std::string_view const& assetPath,
                        sf::Vector2f const& initialPosition,
                        sf::Vector2f const& p_scale = sf::Vector2f(1, 1));

    /// Disables the possibility to construct a GameObject from another.
    /// \param other Other GameObject.
    GameObject(GameObject const& other) = delete;

    /// Disables the possibility to copy a GameObject.
    /// \param other Other GameObject.
    void operator=(GameObject const& other) = delete;

    /// Makes the destructor virtual.
    virtual ~GameObject() = default;

    // GETTERS --------------------------------------------------------------------
    /// Gets the x position of the sprite.
    /// \return x position of the sprite.
    inline float getX() const {return position.x;};

    /// Gets the y position of the sprite.
    /// \return y position of the sprite.
    inline float getY() const {return position.y;};

    /// Gets the width of the sprite.
    /// \return Width of the sprite
    inline float getWidth() const {return sprite.getGlobalBounds().width;};

    /// Gets the height of the sprite.
    /// \return Height of the sprite.
    inline float getHeight() const {return sprite.getGlobalBounds().height;};

    /// Indicates whether the GameObject is currently removed from the screen.
    /// \return Boolean indicating if the GameObject is removed.
    inline bool isRemoved() const {return removed;};

    /// Gets the specific type of the GameObject.
    /// \return Type of the GameObject. Can be BUNNY, PLATFORM, CARROT or OTHER.
    inline ObjectType getType() const {return type;};

    // UPDATE | DISPLAY --------------------------------------------------------------------

    /// Updates the position and velocity of the GameObject, as well as its related objects (e.g. a charge bar).
    /// Specific behavior of the object (gravity, user input...) and screen limits are enforced.
    /// \param loopTime Duration of the game loop in seconds.

    void update(float loopTime);

    /// Removes a GameObject from the screen.
    void remove();

    /// Displays the GameObject and its related objects in the given window.
    /// \param window SFML window in which the game runs.
    void display(sf::RenderWindow& window) const;

    // COLLISIONS --------------------------------------------------------------------

    /// Tests if a collision is happening with another GameObject.
    /// If it is the case, handles the collision.
    /// \param otherObject Other GameObject involved in the collision.
    virtual void testCollision(GameObject& otherObject);

    /// Applies the right collision behavior to the GameObject (changes in position, velocity...).
    /// \param otherObject Other GameObject involved in the collision.
    virtual void handleCollision(GameObject& otherObject);

    /// Applies the right behavior to the GameObject when it goes outside the screen limits.
    virtual void manageScreenLimits();

protected:
    /// Sprite of the GameObject.
    sf::Sprite sprite{};

    /// Texture applied to the sprite.
    sf::Texture texture{};

    /// Scale of the sprite.
    sf::Vector2f scale{};

    /// Type of the GameObject, defaults to OTHER.
    ObjectType type{ObjectType::OTHER};

    /// Position vector.
    sf::Vector2f position{};

    /// Velocity vector.
    sf::Vector2f velocity{};
    virtual void applyBehavior(float loopTime);

    /// Indicates if the GameObject is currently removed from the screen.
    bool removed{false};

    /// Defines additional instructions to perform when removing an object from the screen.
    virtual void onRemoval();

    /// Updates the state of objects that directly depend on the GameObject (e.g. a charge bar).
    virtual void updateRelatedObjects();

    /// Displays objects related to the GameObject.
    virtual void displayRelatedObjects(sf::RenderWindow& window) const;
};


#endif //BUN_GAMEOBJECT_H
