#ifndef BUN_BUNNY_H
#define BUN_BUNNY_H
#include "GameObject.h"
#include "ChargeBar.h"

class Bunny : public GameObject {

public:
    // constructor
    explicit Bunny(sf::Vector2f p_initialPosition);

protected:
    // bunny controls and physics
    void applyBehavior(float loopTime) override;

    // charge bar management
    void updateRelatedObjects() override;
    void displayRelatedObjects(sf::RenderWindow& window) const override;

private:
    // appearance
    enum class BunnyStates{IDLE, CHARGING};
    static constexpr std::string_view IDLE_BUNNY_PATH{"../assets/bunny_idle.png"};
    static constexpr std::string_view CHARGING_BUNNY_PATH{"../assets/bunny_charging.png"};
    void loadTexture(BunnyStates bunnyState);

    // left/right movement physics
    static constexpr float HORIZONTAL_GROUND_ACCELERATION{350.f};
    static constexpr float HORIZONTAL_JUMP_ACCELERATION{500.f};

    // jumping physics
    bool isGrounded = true;
    float jumpForce{};
    float pressedTime{};
    static constexpr float MAX_JUMP_FORCE{2000.f};
    static constexpr float CHARGE_ACCELERATION_COEFF{1.8f};
    static constexpr float GRAVITY{5};

    // collisions
    void manageScreenLimits() override;
    void handleCollision(GameObject& otherObject) override;

    // charge bar
    ChargeBar chargeBar{};
};


#endif //BUN_BUNNY_H
