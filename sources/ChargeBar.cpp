#include "../headers/ChargeBar.h"
#include "../headers/ColorPalette.h"

ChargeBar::ChargeBar() :
    bar{sf::RectangleShape(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT))},
    color{PINK},
    scale{sf::Vector2f(1,0)}
{
    // applying scale and color
    bar.setScale(scale);
    bar.setFillColor(color);
}

void ChargeBar::updateProgress(float percentage) {
    // updating scale based on charge progress
    scale.y = percentage;
    bar.setScale(scale);
}

// TODO change to only apply the duplication behavior horizontally
// TODO think of a better conception to share it with GameObject
void ChargeBar::display(sf::RenderWindow &window) const {
    auto directions = std::array<sf::Vector2f, 9>{
            sf::Vector2f{-1, 1},
            sf::Vector2f{0, -1},
            sf::Vector2f{1, -1},
            sf::Vector2f{-1, 0},
            sf::Vector2f{0, 0},
            sf::Vector2f{1, 0},
            sf::Vector2f{-1, 1},
            sf::Vector2f{0, 1},
            sf::Vector2f{1, 1}
    };
    for(auto& direction : directions){
        auto transformation = sf::Transform{};
        transformation.translate(
                direction.x * static_cast<float>(sf::VideoMode::getDesktopMode().width),
                direction.y * static_cast<float>(sf::VideoMode::getDesktopMode().height)
        );
        window.draw(bar, transformation);
    }
}

void ChargeBar::updatePosition(float referenceX, float referenceY) {
    // displays the bar next to the reference object (e.g. bunny)
    bar.setPosition(referenceX + X_AXIS_SHIFT, referenceY + Y_AXIS_SHIFT);
}