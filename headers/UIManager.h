#ifndef BUN_UIMANAGER_H
#define BUN_UIMANAGER_H

#include <SFML/Graphics.hpp>
#include "../headers/ColorPalette.h"

class UIManager {
public:
    UIManager();
    void updateScoreDisplay(int score);
    void display(sf::RenderWindow &window, bool withNextLevelCue);

private:
    // score display
    sf::Text scoreDisplayFixed{};
    sf::Text scoreDisplayVariable{};
    sf::Sprite carrotSprite{};
    sf::Texture carrotTexture{};
    sf::Font font{};

    // font
    static constexpr std::string_view FONT_PATH{"../assets/Early_GameBoy.ttf"};

    // text
    static int constexpr FONT_SIZE_BIG{70};
    static int constexpr FONT_SIZE_SMALL{45};
    static const sf::Color FONT_COLOR;
    static constexpr float DISTANCE_TO_BORDER{25};
    static constexpr std::string_view FIXED_PART_STRING{"SCORE : "};

    // carrot
    static constexpr std::string_view CARROT_PATH{"../assets/carrot.png"};
    static constexpr float CARROT_SCALE = 2.5;
    static constexpr float CARROT_HORIZONTAL_SHIFT{25};
    static constexpr float CARROT_VERTICAL_SHIFT{15};

    // next level cue
    sf::Text nextLevelCue{};
    static constexpr std::string_view NEXT_LEVEL_CUE_STRING{"CARROTS HERE!"};
};


#endif //BUN_UIMANAGER_H
