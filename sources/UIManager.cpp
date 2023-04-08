#include "../headers/UIManager.h"

 sf::Color const UIManager::FONT_COLOR{BROWN};

// CONSTRUCTOR --------------------------------------------------------------------

UIManager::UIManager() {
    // font
    font.loadFromFile(FONT_PATH.data());

    // fixed part
    scoreDisplayFixed.setFont(font);
    scoreDisplayFixed.setCharacterSize(FONT_SIZE_MEDIUM);
    scoreDisplayFixed.setFillColor(FONT_COLOR);
    scoreDisplayFixed.setPosition(DISTANCE_TO_BORDER, DISTANCE_TO_BORDER);
    scoreDisplayFixed.setString(FIXED_PART_STRING.data());

    // carrot display
    carrotTexture.loadFromFile(CARROT_PATH.data());
    carrotSprite.setTexture(carrotTexture);
    carrotSprite.setScale(sf::Vector2f(CARROT_SCALE,CARROT_SCALE));
    carrotSprite.setOrigin(carrotSprite.getLocalBounds().width / 2, 0);
    carrotSprite.setPosition(CARROT_HORIZONTAL_SHIFT + scoreDisplayFixed.getLocalBounds().width,CARROT_VERTICAL_SHIFT);

    // variable part
    scoreDisplayVariable.setFont(font);
    scoreDisplayVariable.setCharacterSize(FONT_SIZE_MEDIUM);
    scoreDisplayVariable.setFillColor(FONT_COLOR);
    scoreDisplayVariable.setPosition(CARROT_HORIZONTAL_SHIFT*3 + carrotSprite.getLocalBounds().width + scoreDisplayFixed.getLocalBounds().width, DISTANCE_TO_BORDER);

    // next level cue
    nextLevelCue.setFont(font);
    nextLevelCue.setCharacterSize(FONT_SIZE_SMALL);
    nextLevelCue.setFillColor(FONT_COLOR);
    nextLevelCue.setString(NEXT_LEVEL_CUE_STRING.data());
    nextLevelCue.setOrigin(nextLevelCue.getLocalBounds().width/2, nextLevelCue.getLocalBounds().height);
    nextLevelCue.setPosition(Utils::getScreenWidth()/2, DISTANCE_TO_BORDER + nextLevelCue.getLocalBounds().height);

    // losing message
    losingMessage.setFont(font);
    losingMessage.setCharacterSize(FONT_SIZE_BIG);
    losingMessage.setFillColor(FONT_COLOR);
    losingMessage.setString(LOSING_MESSAGE_STRING.data());
    losingMessage.setOrigin(losingMessage.getLocalBounds().width/2, losingMessage.getLocalBounds().height/2);
    losingMessage.setPosition(Utils::getScreenWidth()/2, Utils::getScreenHeight()/2 - 100);

    // winning message
    winningMessage.setFont(font);
    winningMessage.setCharacterSize(FONT_SIZE_BIG);
    winningMessage.setFillColor(FONT_COLOR);
    winningMessage.setString(WINNING_MESSAGE_STRING.data());
    winningMessage.setOrigin(winningMessage.getLocalBounds().width/2, winningMessage.getLocalBounds().height/2);
    winningMessage.setPosition(Utils::getScreenWidth()/2, Utils::getScreenHeight()/2 - 100);

    // continue message
    continueMessage.setFont(font);
    continueMessage.setCharacterSize(FONT_SIZE_SMALL);
    continueMessage.setFillColor(FONT_COLOR);
    continueMessage.setString(CONTINUE_MESSAGE_STRING.data());
    continueMessage.setOrigin(continueMessage.getLocalBounds().width/2, continueMessage.getLocalBounds().height/2);
    continueMessage.setPosition(Utils::getScreenWidth()/2, Utils::getScreenHeight()/2 + 25);

    // yes message
    yesOption.setFont(font);
    yesOption.setCharacterSize(FONT_SIZE_SMALL);
    yesOption.setFillColor(FONT_COLOR);
    yesOption.setString(YES_MESSAGE_STRING.data());
    yesOption.setOrigin(yesOption.getLocalBounds().width/2, yesOption.getLocalBounds().height/2);
    yesOption.setPosition(800, Utils::getScreenHeight()/2 + losingMessage.getLocalBounds().height*4.2 - 200);

    // no message
    noOption.setFont(font);
    noOption.setCharacterSize(FONT_SIZE_SMALL);
    noOption.setFillColor(FONT_COLOR);
    noOption.setString(NO_MESSAGE_STRING.data());
    noOption.setOrigin(noOption.getLocalBounds().width/2, noOption.getLocalBounds().height/2);
    noOption.setPosition(Utils::getScreenWidth() - 800, Utils::getScreenHeight()/2 + losingMessage.getLocalBounds().height*4.2 - 200);

    // command help
    commandHelp.setFont(font);
    commandHelp.setCharacterSize(FONT_SIZE_TINY);
    commandHelp.setFillColor(PINK);
    commandHelp.setString(COMMAND_HELP_STRING.data());
    commandHelp.setOrigin(commandHelp.getLocalBounds().width/2, commandHelp.getLocalBounds().height/2);
    commandHelp.setPosition(Utils::getScreenWidth()/2, Utils::getScreenHeight() - 50);

    // choice/arrow
    choiceArrow.setFont(font);
    choiceArrow.setCharacterSize(FONT_SIZE_SMALL);
    choiceArrow.setFillColor(FONT_COLOR);
    choiceArrow.setString(CHOICE_ARROW_STRING.data());
    choiceArrow.setOrigin(choiceArrow.getLocalBounds().width/2, choiceArrow.getLocalBounds().height/2);
    choiceArrow.setPosition(yesOption.getPosition().x - yesOption.getLocalBounds().width/2 - 50, yesOption.getPosition().y);

    // title screen
    titleScreenTexture.loadFromFile(TITLE_SCREEN_PATH.data());
    titleScreenSprite.setTexture(titleScreenTexture);
    titleScreenSprite.setOrigin(titleScreenSprite.getLocalBounds().width / 2, titleScreenSprite.getLocalBounds().height / 2);
    titleScreenSprite.setPosition(Utils::getScreenWidth()/2, Utils::getScreenHeight()/2);

    // start message
    startMessage.setFont(font);
    startMessage.setCharacterSize(FONT_SIZE_SMALL);
    startMessage.setFillColor(FONT_COLOR);
    startMessage.setString(START_MESSAGE_STRING.data());
    startMessage.setOrigin(startMessage.getLocalBounds().width/2, startMessage.getLocalBounds().height/2);
    startMessage.setPosition(Utils::getScreenWidth()/2, Utils::getScreenHeight()/2 + 220);

    // gameplay
    gameplayHelp.setFont(font);
    gameplayHelp.setCharacterSize(FONT_SIZE_TINY);
    gameplayHelp.setFillColor(PINK);
    gameplayHelp.setString("COLLECT " + std::to_string(Utils::SCORE_TO_WIN) + " CARROTS WITHOUT FALLING!");
    gameplayHelp.setOrigin(gameplayHelp.getLocalBounds().width/2, gameplayHelp.getLocalBounds().height/2);
    gameplayHelp.setPosition(Utils::getScreenWidth()/2, Utils::getScreenHeight() - 50);
}

// SCORE DISPLAY --------------------------------------------------------------------

void UIManager::updateScoreDisplay(int score) {
    scoreDisplayVariable.setString(std::to_string(score));
}

void UIManager::displayScore(sf::RenderWindow &window) {
    window.draw(scoreDisplayFixed);
    window.draw(carrotSprite);
    window.draw(scoreDisplayVariable);
}

// UI LOOPS --------------------------------------------------------------------

void UIManager::displayPLaying(sf::RenderWindow &window, bool withNextLevelCue) {
    displayScore(window);
    if(withNextLevelCue){
        // TODO create a flickering function since it is used by several text elements
        auto loopTime = chrono.restart().asSeconds();
        elapsedTime += loopTime;
        if(elapsedTime > FLICKER_TIME){ // makes the text appear/disappear after a set interval of time
            elapsedTime = 0;
            toggleCue();
        }
        if(cueVisible){
            window.draw(nextLevelCue);
        }
    }
}

void UIManager::displayContinueMenu(sf::RenderWindow &window, bool losing) {
    displayScore(window);
    if(losing) {
        window.draw(losingMessage);
    } else {
        window.draw(winningMessage);
    }
    inputChoice();
    updateChoice();
    window.draw(continueMessage);
    window.draw(yesOption);
    window.draw(noOption);
    window.draw(choiceArrow);
    window.draw(commandHelp);
}

void UIManager::displayTitleScreen(sf::RenderWindow &window) {
    window.draw(titleScreenSprite);
    // flickering
    auto loopTime = chrono.restart().asSeconds();
    elapsedTime += loopTime;
    if(elapsedTime > FLICKER_TIME){ // makes the text appear/disappear after a set interval of time
        elapsedTime = 0;
        toggleStartMessage();
    }
    if(startMessageVisible){
        window.draw(startMessage);
    }
    window.draw(gameplayHelp);
}

// CONTINUE CHOICE --------------------------------------------------------------------

void UIManager::inputChoice() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        choice = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        choice = false;
    }
}

void UIManager::updateChoice() {
    if(choice){ // moves the arrow in front of "yes"
        choiceArrow.setPosition(yesOption.getPosition().x - yesOption.getLocalBounds().width/2 - 50, yesOption.getPosition().y);
    } else{ // moves the arrow in front of "no"
        choiceArrow.setPosition(noOption.getPosition().x - noOption.getLocalBounds().width/2 - 50, noOption.getPosition().y);
    }
}
