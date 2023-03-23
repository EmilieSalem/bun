#include "../headers/Carrot.h"

Carrot::Carrot(int& p_score) : GameObject(
        CARROT_PATH,
        sf::Vector2f(500, 995),
        sf::Vector2f(2.2, 2.2)),
        score{p_score}{
    type = ObjectType::CARROT;
}

void Carrot::onRemoval() {
    score += value;
}

void Carrot::setPosition(Platform* platform) {
    position = sf::Vector2f(platform->getX(), platform->getY() - platform->getHeight()/2.5f);
    sprite.setPosition(position);
}
