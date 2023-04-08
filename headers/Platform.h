#ifndef BUN_PLATFORM_H
#define BUN_PLATFORM_H

#include "GameObject.h"
#include "../headers/Utils.h"

/// A Platform on which the Bunny can land. Its position is randomized.
class Platform : public GameObject {
public:
    // LEVELS  --------------------------------------------------------------------
    /// Defines the different levels at which a platform can be initialized.
    /// Each level corresponds to a third of the screen.
    enum class PlatformLevel{ LOW, MIDDLE, HIGH };

    // CONSTRUCTOR  --------------------------------------------------------------------
    /// Initializes a Platform at the given level of the screen.
    /// \param p_platformLevel Level of the screen at which the platform should be generated. Can be LOW, MIDDLE or HIGH.
    explicit Platform(PlatformLevel p_platformLevel);

protected:
    // COLLISION  --------------------------------------------------------------------
    /// Generates another position for the Platform if it overlaps with an existing one.
    /// Doesn't do anything if it collides with another type of GameObject.
    /// \param otherObject Other GameObject involved in the collision.
    void handleCollision(GameObject& otherObject) override;

private:
    // AESTHETIC  --------------------------------------------------------------------
    /// Path to the image file used as a texture for the sprite.
    static constexpr std::string_view PLATFORM_PATH{"../assets/platform.png"};

    // POSITION  --------------------------------------------------------------------
    /// Level of the Platform. Can be LOW, MIDDLE or HIGH.
    PlatformLevel platformLevel{};
    /// Generates a random position for the Platform in the right screen level.
    void randomizePosition();
    /// Defines a border at the bottom of the screen
    /// where Platforms can't be initialized for aesthetic purposes.
    float static constexpr VERTICAL_BORDER{150.f};
};


#endif //BUN_PLATFORM_H
