#ifndef BUN_CARROT_H
#define BUN_CARROT_H

#include "GameObject.h"
#include "Platform.h"

/// A Carrot that the Bunny can pick up to increase the player's score.
class Carrot : public GameObject{
public:
    // CONSTRUCTOR  --------------------------------------------------------------------
    /// Initializes a Carrot.
    /// A reference to the score in necessary to update it when the Carrot is picked up.
    /// \param p_score Reference to the game score.
    explicit Carrot(int& p_score);

    // POSITION  --------------------------------------------------------------------
    /// Initializes the position of a Carrot on top of a Platform.
    /// \param platformX x position of the Platform.
    /// \param platFormY y position of the Platform.
    /// \param platformHeight Height of the Platform.
    void setPosition(float platformX, float platFormY, float platformHeight);

protected:
    // REMOVAL  --------------------------------------------------------------------
    /// Updates the score when the Carrot is picked up.
    void onRemoval() override;

private:
    // AESTHETIC  --------------------------------------------------------------------
    /// Path to the image file used as a texture for the sprite.
    static constexpr std::string_view CARROT_PATH{"../assets/carrot.png"};

    // SCORE --------------------------------------------------------------------
    /// Value of the Carrot. For the moment, it only yields 1 score point.
    int value{1};

    // TODO make it a reference to the game
    /// Reference to the total game score.
    int& score;
};


#endif //BUN_CARROT_H