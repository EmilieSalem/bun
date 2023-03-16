#ifndef BUN_BUNNY_H
#define BUN_BUNNY_H
#include "GameObject.h"

class Bunny : public GameObject {

public:
    explicit Bunny();

protected:
    void applyBehavior(float loopTime) override;

private:
    // appearance
    static constexpr std::string_view IDLE_BUNNY_PATH{"../assets/bunny_idle.png"};
    static constexpr std::string_view CHARGING_BUNNY_PATH{"../assets/bunny_charging.png"};

    // left/right movement physics
    static constexpr float HORIZONTAL_ACCELERATION{350.f};

    // jumping physics
    bool isGrounded = true;
    float jumpForce{};
    float pressedTime{};
    static constexpr float MAX_JUMP_FORCE{3500.f};
    static constexpr float CHARGE_ACCELERATION_COEFF{1.4f};
};


#endif //BUN_BUNNY_H
