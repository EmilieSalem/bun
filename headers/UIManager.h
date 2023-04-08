#ifndef BUN_UIMANAGER_H
#define BUN_UIMANAGER_H

#include <SFML/Graphics.hpp>
#include "../headers/ColorPalette.h"
#include "Utils.h"

/// The UIManager is responsible for updating and displaying the UI on all screens and menus of the game.
class UIManager {
public:
    // CONSTRUCTOR --------------------------------------------------------------------
    /// Initializes a UIManager.
    /// Sets the appearance and position of all the UI elements.
    explicit UIManager();

    // UI LOOPS --------------------------------------------------------------------
    /// Updates the value of the score displayed on the screen.
    /// \param score Current score of the player.
    void updateScoreDisplay(int score);
    /// Displays UI elements for the game screen, aka the score
    /// and a flickering cue to go up if all carrots have been collected.
    /// \param window SFML window in which the game is running.
    /// \param withNextLevelCue Boolean indicating if the cue to go up should be displayed.
    void displayPLaying(sf::RenderWindow &window, bool withNextLevelCue);
    /// Displays UI elements for the continue screen, aka the right message (winning or losing),
    /// the yes/no choices and a command help indicating which button to press to confirm.
    /// \param window SFML window in which the game is running.
    /// \param losing Boolean indicating if the player has lost or won.
    void displayContinueMenu(sf::RenderWindow &window, bool losing);
    /// Displays UI element for the title screen, aka the background art,
    /// a flickering cue to start playing and a small gameplay explanation.
    /// \param window SFML window in which the game is running.
    void displayTitleScreen(sf::RenderWindow &window);
    /// Indicates whether the player wants to continue playing or not.
    /// \return Boolean indicating if the player wants to continue playing.
    inline bool getChoice() const{return choice;};

private:
    // PATHS --------------------------------------------------------------------
    /// Path to the font used for all text elements.
    static constexpr std::string_view FONT_PATH{"../assets/Early_GameBoy.ttf"};
    /// Path to the Carrot image asset used for the score display.
    static constexpr std::string_view CARROT_PATH{"../assets/carrot.png"};
    /// Path to the background art asset used for the title screen.
    static constexpr std::string_view TITLE_SCREEN_PATH{"../assets/title_screen.png"};

    // STRINGS --------------------------------------------------------------------
    /// Fixed part of the score display.
    static constexpr std::string_view FIXED_PART_STRING{"SCORE : "};
    /// Cue to go up displayed when there are no more carrots on the screen.
    static constexpr std::string_view NEXT_LEVEL_CUE_STRING{"UP HERE!"};
    /// Message displayed when losing the game.
    static constexpr std::string_view LOSING_MESSAGE_STRING{"GAME OVER"};
    /// Message displayed when winning the game.
    static constexpr std::string_view WINNING_MESSAGE_STRING{"YOU WON!"};
    /// Message displayed to ask whether the player wants to continue playing.
    static constexpr std::string_view CONTINUE_MESSAGE_STRING{"CONTINUE?"};
    /// Choice to continue playing.
    static constexpr std::string_view YES_MESSAGE_STRING{"YES"};
    /// Choice to stop playing.
    static constexpr std::string_view NO_MESSAGE_STRING{"NO"};
    /// Command help to know which button to press to confirm the continue choice.
    static constexpr std::string_view COMMAND_HELP_STRING{"PRESS E TO CONFIRM"};
    /// Arrow used to choose between the two continue choices.
    /// Though the symbol is ~, the game font renders it as an arrow.
    static constexpr std::string_view CHOICE_ARROW_STRING{"~"};
    /// Message displayed on the title screen.
    static constexpr std::string_view START_MESSAGE_STRING{"PRESS ENTER TO START"};

    // TEXT --------------------------------------------------------------------
    /// Font used by all text elements.
    sf::Font font{};
    /// Fixed part of the score display.
    sf::Text scoreDisplayFixed{};
    /// Variable part of the score display, updated with the score.
    sf::Text scoreDisplayVariable{};
    /// Cue to go up when there are no more carrots on screen.
    sf::Text nextLevelCue{};
    /// Message displayed when losing.
    sf::Text losingMessage{};
    /// Message displayed when winning.
    sf::Text winningMessage{};
    /// Message displayed to ask whether the player wants to continue playing.
    sf::Text continueMessage{};
    /// Choice to continue playing.
    sf::Text yesOption{};
    /// Choice to stop playing.
    sf::Text noOption{};
    /// Command help to know which button to press to confirm the continue choice.
    sf::Text commandHelp{};
    /// Arrow used to choose between the two continue choices.
    sf::Text choiceArrow{};
    /// Message displayed on the title screen.
    sf::Text startMessage{};
    /// Gameplay help indicating how many carrots should be collected to win.
    sf::Text gameplayHelp{};

    // SPRITES | TEXTURES --------------------------------------------------------------------
    /// Sprite for the carrot used in the score display.
    sf::Sprite carrotSprite{};
    /// Texture for the carrot used in the score display.
    sf::Texture carrotTexture{};
    /// Sprite for the title screen art.
    sf::Sprite titleScreenSprite{};
    /// Texture for the title screen art.
    sf::Texture titleScreenTexture{};

    // CONSTANTS --------------------------------------------------------------------
    /// Biggest font size, used for winning/losing messages.
    static int constexpr FONT_SIZE_BIG{100};
    /// Medium font size, used for the score display.
    static int constexpr FONT_SIZE_MEDIUM{70};
    /// Small font size, used for most text elements.
    static int constexpr FONT_SIZE_SMALL{45};
    /// Smallest font size, used for the gameplay/command helps.
    static int constexpr FONT_SIZE_TINY{25};
    /// Font color used by most text elements.
    static const sf::Color FONT_COLOR;
    /// Distance left between text elements and the limit of the screen for aesthetic purposes.
    static constexpr float DISTANCE_TO_BORDER{25};
    /// Scale of the carrot in the score display.
    static constexpr float CARROT_SCALE = 2.5;
    /// Horizontal correction of the carrot to align it with the text elements.
    static constexpr float CARROT_HORIZONTAL_SHIFT{25};
    /// Vertical correction of the carrot to align it with the text elements.
    static constexpr float CARROT_VERTICAL_SHIFT{15};
    /// Time during which the text is present/absent when flickering.
    static constexpr float FLICKER_TIME = 0.6f;

    // SCORE DISPLAY --------------------------------------------------------------------
    /// Displays the 3 elements of the score display: the fixed part, the variable part and the carrot sprite.
    void displayScore(sf::RenderWindow &window);

    // FLICKERING --------------------------------------------------------------------
    /// Chronometer used to measure elapsed time for flickering.
    sf::Clock chrono{};
    /// Time elapsed since the last flickering change (present or absent).
    float elapsedTime{};
    /// Boolean indicating whether the cue to go up should be displayed.
    bool cueVisible{true};
    /// Toggles the display of the cue to go up.
    inline void toggleCue(){cueVisible = !cueVisible;};
    /// Boolean indicating whether the start message should be displayed.
    bool startMessageVisible{true};
    /// Toggles the display of the start message.
    inline void toggleStartMessage(){startMessageVisible = !startMessageVisible;};

    // CONTINUE CHOICE --------------------------------------------------------------------
    /// Boolean indicating whether the player wants to continue playing.
    bool choice{true};
    /// Updates the continue choice of the player when the left/right arrow keys are pressed.
    void inputChoice();
    /// Updates the position of the arrow to make it point on the player's choice.
    void updateChoice();
};


#endif //BUN_UIMANAGER_H
