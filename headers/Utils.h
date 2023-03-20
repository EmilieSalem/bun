#ifndef BUN_UTILS_H
#define BUN_UTILS_H

#include <SFML/Graphics.hpp>

class Utils{
public:
    inline static float const getScreenWidth() {return static_cast<float>(sf::VideoMode::getDesktopMode().width);};
    inline static float const getScreenHeight() {return static_cast<float>(sf::VideoMode::getDesktopMode().height);};
};

#endif //BUN_UTILS_H
