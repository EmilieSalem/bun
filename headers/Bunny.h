#ifndef BUN_BUNNY_H
#define BUN_BUNNY_H
#include "GameObject.h"
#include "ChargeBar.h"
#include "ObjectManager.h"

class Bunny : public GameObject {

public:
    // CONSTRUCTOR  --------------------------------------------------------------------
    /// Initializes a Bunny given its initial position and velocity.
    /// A reference to the ObjectManager is necessary for screen management.
    /// \param p_initialPosition Initial position vector.
    /// \param p_objectManager Reference to the ObjectManager that manages the Bunny.
    /// \param p_initialVelocity Initial velocity vector.
    explicit Bunny(sf::Vector2f p_initialPosition, ObjectManager &p_objectManager, sf::Vector2f p_initialVelocity = sf::Vector2f(0,0));

protected:
    // CONTROLS | PHYSICS  --------------------------------------------------------------------
    /// Applies the Bunny's specific behavior, i.e. gravity and jumps.
    /// \param loopTime Duration of the game loop in seconds.
    void applyBehavior(float loopTime) override;

    // CHARGE BAR  --------------------------------------------------------------------

    void updateRelatedObjects() override;
    void displayRelatedObjects(sf::RenderWindow& window) const override;

private:
    // AESTHETIC  --------------------------------------------------------------------
    /// Defines the states of the bunny that require different sprites.
    enum class BunnyStates{IDLE, CHARGING};

    /// Path to the image used as texture in the IDLE state.
    static constexpr std::string_view IDLE_BUNNY_PATH{"../assets/bunny_idle.png"};

    /// Path to the image used as texture in the CHARGING state.
    static constexpr std::string_view CHARGING_BUNNY_PATH{"../assets/bunny_charging.png"};

    /// Loads the right texture to the sprite depending on the Bunny state.
    /// \param bunnyState Current state of the Bunny. Can be IDLE or CHARGING.
    void loadTexture(BunnyStates bunnyState);

    // PHYSICS  --------------------------------------------------------------------

    /// Horizontal acceleration of the bunny when it is grounded.
    static constexpr float HORIZONTAL_GROUND_ACCELERATION{350.f};

    /// Horizontal acceleration of the bunny when it is midair.
    static constexpr float HORIZONTAL_JUMP_ACCELERATION{500.f};

    /// Indicates if the Bunny touches a Platform.
    bool isGrounded = true;

    /// Jump force that increases with user input.
    float jumpForce{};

    /// Maximum value that jumpForce can take.
    static constexpr float MAX_JUMP_FORCE{2500.f};

    /// Duration of the user pressing the space bar.
    float pressedTime{};

    /// Coefficient that controls the speed at which the charge bar charges up.
    static constexpr float CHARGE_ACCELERATION_COEFF{1.8f};

    /// Gravity that pulls the Bunny downwards when it is not grounded.
    static constexpr float GRAVITY{5};

    // COLLISIONS  --------------------------------------------------------------------

    /// Manages the Bunny's behavior when it reaches the limits of the window.
    /// Horizontally, it prevents it from leaving the screen.
    /// Vertically, it can either change/generate a screen or trigger the end of the game.
    void manageScreenLimits() override;

    /// Manages the Bunny's collision with another object.
    /// It picks up carrots and lands on platforms.
    /// \param otherObject Other GameObject involved in the collision.
    void handleCollision(GameObject& otherObject) override;

    // RELATED OBJECTS --------------------------------------------------------------------

    /// ChargeBar associated to the bunny, shows the jump charge progression.
    ChargeBar chargeBar{};

    /// Reference to the ObjectManager for screen management.
    ObjectManager &objectManager;
};


#endif //BUN_BUNNY_H
