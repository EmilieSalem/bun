#include <iostream>
#include <SFML/Graphics.hpp>

const sf::Color BROWN{sf::Color(100,59,53)};
const sf::Color BEIGE{sf::Color{230, 202, 188}};

const int GRAVITY{5};

struct BunnyData{
    float x_pos{350.f};
    float y_pos{100.f};
    float x_vel{0.f};
    float y_vel{300.f};
    float x_acc{350.f};
    float y_acc{3000.f};
    float jump_force{0.f};
    bool grounded{true};
};

void move(sf::RectangleShape &bunny, BunnyData &bunnyData, float &tempsBoucle) {
    // Gravity
    bunnyData.y_vel += GRAVITY;

    // Update position
    bunnyData.x_pos += bunnyData.x_vel  * tempsBoucle;
    bunnyData.y_pos +=  bunnyData.y_vel * tempsBoucle;

    // Check for collision
    if(bunnyData.y_pos >= 550){
        bunnyData.y_pos = 550;
        bunnyData.y_vel = 0;
        bunnyData.grounded = true;
    }

    bunny.setPosition(bunnyData.x_pos, bunnyData.y_pos);
}

void update(sf::RectangleShape &bunny, sf::Text &debugText, float &tempsBoucle, float &pressedTime, BunnyData &bunnyData) {
    
    bunnyData.x_vel = 0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        bunnyData.x_vel += bunnyData.x_acc;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        bunnyData.x_vel -= bunnyData.x_acc;
    }
    if(bunnyData.grounded){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            pressedTime += tempsBoucle;
            debugText.setString("Space pressed for : " + std::to_string(pressedTime) + " s");
        } else{
            if(pressedTime != 0){
                bunnyData.y_vel = -bunnyData.y_acc;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) bunnyData.x_vel = bunnyData.x_acc;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) bunnyData.x_vel = -bunnyData.x_acc;
                bunnyData.grounded = false;
            }
            pressedTime = 0;
            debugText.setString("Space is not pressed");
        }
    }

}

int main() {
    sf::RenderWindow fenetre{sf::VideoMode{800, 600}, "bun"};

    sf::RectangleShape bunny(sf::Vector2f(50, 50));
    bunny.setFillColor(BROWN);
    bunny.setOrigin(bunny.getLocalBounds().width / 2, bunny.getLocalBounds().height / 2);
    auto bunnyData = BunnyData{};

    sf::Clock chrono{};

    sf::Text debugText{};
    sf::Font police{};
    police.loadFromFile("../assets/debug_font.ttf");
    debugText.setFont(police);
    debugText.setFillColor(BROWN);
    debugText.setString("Hello !");
    debugText.setPosition(15, 15);

    float pressedTime{};

    while (fenetre.isOpen()) {
        auto evenement = sf::Event();

        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == sf::Event::Closed) fenetre.close();
        }

        // bunny behavior
        auto tempsBoucle = chrono.restart().asSeconds();
        update(bunny, debugText, tempsBoucle, pressedTime, bunnyData);
        move(bunny, bunnyData, tempsBoucle);

        fenetre.clear(BEIGE);
        fenetre.draw(bunny);
        fenetre.draw(debugText);
        fenetre.display();
    }
}






