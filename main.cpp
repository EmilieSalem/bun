 #include <SFML/Graphics.hpp>
#include "headers/ColorPalette.h"
#include "headers/ObjectManager.h"
#include "headers/UIManager.h"

int main() {
    // window
    sf::RenderWindow window{sf::VideoMode(), "bun", sf::Style::Fullscreen};

    // objects
    ObjectManager objectManager{};
    objectManager.initializeGame();

    // UI
    UIManager uiManager{};

    while(window.isOpen()){
        auto event = sf::Event();

        while(window.pollEvent(event)){
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
        }

        window.clear(BEIGE);

        objectManager.updateCurrentScreen();
        objectManager.handleCollisionsInCurrentScreen();
        uiManager.updateScoreDisplay(objectManager.getScore());

        uiManager.display(window, objectManager.noMoreCarrotsInCurrentScreen());
        objectManager.displayCurrentScreen(window);

        window.display();

        objectManager.updateScreen();
    }
}