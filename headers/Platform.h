#ifndef BUN_PLATFORM_H
#define BUN_PLATFORM_H

#include "GameObject.h"
#include "../headers/Utils.h"

class Platform : public GameObject {
public:
    enum class PlatformLevel{ LOW, MIDDLE, HIGH };
    explicit Platform(PlatformLevel p_platformLevel);

protected:
    // manage platform overlap
    void handleCollision(GameObject& otherObject) override;

private:
    // appearance
    static constexpr std::string_view PLATFORM_PATH{"../assets/platform.png"};

    // position
    PlatformLevel platformLevel{};
    void randomizePosition();

    // to avoid having platforms at the very top/bottom of the screen
    float static constexpr VERTICAL_BORDER{200.f};
};


#endif //BUN_PLATFORM_H
