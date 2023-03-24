#include <iostream>
#include "../headers/UIManager.h"
#include "../headers/Utils.h"

 sf::Color const UIManager::FONT_COLOR{BROWN};

UIManager::UIManager() {
    // font
    font.loadFromFile(FONT_PATH.data());

    // fixed part
    scoreDisplayFixed.setFont(font);
    scoreDisplayFixed.setCharacterSize(FONT_SIZE_BIG);
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
    scoreDisplayVariable.setCharacterSize(FONT_SIZE_BIG);
    scoreDisplayVariable.setFillColor(FONT_COLOR);
    scoreDisplayVariable.setPosition(CARROT_HORIZONTAL_SHIFT*3 + carrotSprite.getLocalBounds().width + scoreDisplayFixed.getLocalBounds().width, DISTANCE_TO_BORDER);

    // next level cue
    nextLevelCue.setFont(font);
    nextLevelCue.setCharacterSize(FONT_SIZE_SMALL);
    nextLevelCue.setFillColor(FONT_COLOR);
    nextLevelCue.setString(NEXT_LEVEL_CUE_STRING.data());
    nextLevelCue.setOrigin(nextLevelCue.getLocalBounds().width/2, nextLevelCue.getLocalBounds().height);
    nextLevelCue.setPosition(Utils::getScreenWidth()/2, Utils::getScreenHeight() - DISTANCE_TO_BORDER*1.5f);
}

void UIManager::updateScoreDisplay(int score) {
    scoreDisplayVariable.setString(std::to_string(score));
}

void UIManager::display(sf::RenderWindow &window, bool withNextLevelCue) {
    window.draw(scoreDisplayFixed);
    window.draw(carrotSprite);
    window.draw(scoreDisplayVariable);
    if(withNextLevelCue){
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
