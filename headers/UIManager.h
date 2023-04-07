#ifndef BUN_UIMANAGER_H
#define BUN_UIMANAGER_H

#include <SFML/Graphics.hpp>
#include "../headers/ColorPalette.h"
#include "Utils.h"

class UIManager {
public:
    explicit UIManager();
    void updateScoreDisplay(int score);
    void displayPLaying(sf::RenderWindow &window, bool withNextLevelCue);
    void displayContinueMenu(sf::RenderWindow &window, bool losing);
    void displayTitleScreen(sf::RenderWindow &window);
    inline bool getChoice() const{return choice;};

private:
    // score display
    sf::Text scoreDisplayFixed{};
    sf::Text scoreDisplayVariable{};
    sf::Sprite carrotSprite{};
    sf::Texture carrotTexture{};
    sf::Font font{};
    void displayScore(sf::RenderWindow &window);

    // font
    static constexpr std::string_view FONT_PATH{"../assets/Early_GameBoy.ttf"};

    // text
    static int constexpr FONT_SIZE_BIG{100};
    static int constexpr FONT_SIZE_MEDIUM{70};
    static int constexpr FONT_SIZE_SMALL{45};
    static int constexpr FONT_SIZE_TINY{25};
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
    static constexpr std::string_view NEXT_LEVEL_CUE_STRING{"UP HERE!"};

    // to make the cue flicker
    bool cueVisible{true};
    sf::Clock chrono{};
    float elapsedTime{};
    static constexpr float FLICKER_TIME = 0.6f;
    inline void toggleCue(){cueVisible = !cueVisible;};

    // losing message
    sf::Text losingMessage{};
    static constexpr std::string_view LOSING_MESSAGE_STRING{"GAME OVER"};

    // winning message
    sf::Text winningMessage{};
    static constexpr std::string_view WINNING_MESSAGE_STRING{"YOU WON!"};

    // menu
    sf::Text continueMessage{};
    sf::Text yesOption{};
    sf::Text noOption{};
    sf::Text commandHelp{};
    static constexpr std::string_view CONTINUE_MESSAGE_STRING{"CONTINUE?"};
    static constexpr std::string_view YES_MESSAGE_STRING{"YES"};
    static constexpr std::string_view NO_MESSAGE_STRING{"NO"};
    static constexpr std::string_view COMMAND_HELP_STRING{"PRESS E TO CONFIRM"};

    // choice arrow
    sf::Text choiceArrow{};
    static constexpr std::string_view CHOICE_ARROW_STRING{"~"};
    bool choice{true};
    void inputChoice();
    void updateChoice();

    // start screen
    static constexpr std::string_view TITLE_SCREEN_PATH{"../assets/title_screen.png"};
    sf::Sprite titleScreenSprite{};
    sf::Texture titleScreenTexture{};
    sf::Text startMessage{};
    static constexpr std::string_view START_MESSAGE_STRING{"PRESS ENTER TO START!"};
    bool startMessageVisible{true};
    inline void toggleStartMessage(){startMessageVisible = !startMessageVisible;};
    sf::Text gameplayHelp{};
};


#endif //BUN_UIMANAGER_H
