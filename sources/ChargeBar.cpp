#include "../headers/ChargeBar.h"
#include "../headers/ColorPalette.h"

// CONSTRUCTOR --------------------------------------------------------------------

ChargeBar::ChargeBar() :
    bar{sf::RectangleShape(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT))},
    color{PINK},
    scale{sf::Vector2f(1,0)}
{
    // applying scale and color
    bar.setScale(scale);
    bar.setFillColor(color);
}

// BAR STATE --------------------------------------------------------------------

void ChargeBar::updateProgress(float percentage) {
    // updating scale based on charge progress
    scale.y = percentage;
    bar.setScale(scale);
}

void ChargeBar::updatePosition(float referenceX, float referenceY) {
    // displays the bar next to the reference object (e.g. bunny)
    bar.setPosition(referenceX + X_AXIS_SHIFT, referenceY + Y_AXIS_SHIFT);
}

// TODO think of a better conception to share it with GameObject
void ChargeBar::display(sf::RenderWindow &window) const {
    window.draw(bar);
}