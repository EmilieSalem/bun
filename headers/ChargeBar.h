#ifndef BUN_CHARGEBAR_H
#define BUN_CHARGEBAR_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class ChargeBar {
public:
    // constructor
    explicit ChargeBar();
    void updateProgress(float percentage);
    void display(sf::RenderWindow& window) const;
    void updatePosition(float referenceX, float referenceY);

    // disabling copy
    ChargeBar(ChargeBar const& other) = delete;
    void operator=(ChargeBar const& other) = delete;

private:
    // attributes
    sf::RectangleShape bar{};
    sf::Color color{};
    sf::Vector2f scale{};

    // constants
    static constexpr int BAR_WIDTH = 17;
    static constexpr int BAR_HEIGHT = 50;
    static constexpr float X_AXIS_SHIFT = 70;
    static constexpr float Y_AXIS_SHIFT = -50;
};


#endif //BUN_CHARGEBAR_H
