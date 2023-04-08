#ifndef BUN_UTILS_H
#define BUN_UTILS_H

#include <SFML/Graphics.hpp>

/// A class that contains various functions and variables used over the whole project.
class Utils{
public:
    // SCREEN --------------------------------------------------------------------
    /// Gets the width of the player's screen.
    /// \return Screen width in pixels.
    inline static float getScreenWidth() {return static_cast<float>(sf::VideoMode::getDesktopMode().width);};
    /// Gets the height of the player's screen.
    /// \return Screen height in pixels.
    inline static float getScreenHeight() {return static_cast<float>(sf::VideoMode::getDesktopMode().height);};

    // GAMEPLAY --------------------------------------------------------------------
    /// Score (aka number of carrots) required to win the game.
    static int constexpr SCORE_TO_WIN = 15;
};

#endif //BUN_UTILS_H
