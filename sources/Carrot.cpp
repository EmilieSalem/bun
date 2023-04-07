#include "../headers/Carrot.h"

// CONSTRUCTOR  --------------------------------------------------------------------

Carrot::Carrot(int& p_score) : GameObject(
        CARROT_PATH,
        sf::Vector2f(500, 995),
        sf::Vector2f(2.2, 2.2)),
        score{p_score}{
    type = ObjectType::CARROT;
}

// REMOVAL  --------------------------------------------------------------------

void Carrot::onRemoval() {
    score += value; // increasing the score when the carrot is picked up
}

// POSITION  --------------------------------------------------------------------

void Carrot::setPosition(float platformX, float platFormY, float platformHeight) {
    // placed slightly above the platform for aesthetic purposes
    position = sf::Vector2f(platformX, platFormY - platformHeight/2);
    sprite.setPosition(position);
}
