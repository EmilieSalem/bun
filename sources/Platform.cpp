#include "../headers/Platform.h"

Platform::Platform() : GameObject(
        PLATFORM_PATH,
        sf::Vector2f(sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height/2),
        sf::Vector2f(2.2, 2.2)){
}
