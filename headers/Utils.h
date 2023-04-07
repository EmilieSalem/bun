#ifndef BUN_UTILS_H
#define BUN_UTILS_H

#include <SFML/Graphics.hpp>

class Utils{
public:
    inline static float const getScreenWidth() {return static_cast<float>(sf::VideoMode::getDesktopMode().width);};
    inline static float const getScreenHeight() {return static_cast<float>(sf::VideoMode::getDesktopMode().height);};
    static int constexpr SCORE_TO_WIN = 15;
};

#endif //BUN_UTILS_H
