#ifndef BUN_CHARGEBAR_H
#define BUN_CHARGEBAR_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

/// A bar associated to the Bunny to indicate the progress of the jump charge when pressing the space key.
class ChargeBar {
public:
    // CONSTRUCTOR --------------------------------------------------------------------
    /// Initializes a ChargeBar.
    explicit ChargeBar();
    /// Disables the possibility to construct a ChargeBar from another.
    /// \param other Other ChargeBar.
    ChargeBar(ChargeBar const& other) = delete;
    /// Disables the possibility to copy a ChargeBar.
    /// \param other Other ChargeBar.
    void operator=(ChargeBar const& other) = delete;

    // BAR STATE --------------------------------------------------------------------
    /// Updates the size of the ChargeBar based on the jump charge progress.
    /// \param percentage Progress of the jump charge (between 0 and 1).
    void updateProgress(float percentage);
    /// Sets the position of the ChargeBar so that it is floating next to a reference object (e.g. the Bunny).
    /// \param referenceX x position of the reference object.
    /// \param referenceY y position of the reference object.
    void updatePosition(float referenceX, float referenceY);
    /// Displays the ChargeBar in the given window.
    /// \param window SFML window in which the game runs.
    void display(sf::RenderWindow& window) const;

private:
    // AESTHETIC --------------------------------------------------------------------
    /// Rectangular shape representing the ChargeBar.
    sf::RectangleShape bar{};
    /// Color of the ChargeBar.
    sf::Color color{};
    /// Scale of the ChargeBar.
    sf::Vector2f scale{};

    // CONSTANTS --------------------------------------------------------------------
    /// Width of the ChargeBar.
    static constexpr int BAR_WIDTH = 17;
    /// Height of the ChargeBar.
    static constexpr int BAR_HEIGHT = 50;
    /// X axis distance to the reference object the ChargeBar floats next to.
    static constexpr float X_AXIS_SHIFT = 70;
    /// Y axis distance to the reference object the ChargeBar floats next to.
    static constexpr float Y_AXIS_SHIFT = 0;
};


#endif //BUN_CHARGEBAR_H
