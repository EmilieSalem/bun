#include <iostream>
#include <SFML/Graphics.hpp>

const sf::Color BROWN{sf::Color(100,59,53)};
const sf::Color BEIGE{sf::Color{230, 202, 188}};
const sf::Color ORANGE{sf::Color{219,112,50}};
const sf::Color PINK{sf::Color{215,124,116}};

const float MAX_JUMP_FORCE{3500.f};
const float CHARGE_ACCELERATION{1.4f};

const int GRAVITY{5};

sf::Texture idleTexture{};
sf::Texture chargeTexture{};

struct BunnyData{
    float x_pos{350.f};
    float y_pos{100.f};
    float x_vel{0.f};
    float y_vel{300.f};
    float x_acc{350.f};
    float y_acc{MAX_JUMP_FORCE};
    float jump_force{0.f};
    bool grounded{true};
};

void move(sf::Sprite &bunny, sf::RectangleShape &bar, BunnyData &bunnyData, float &tempsBoucle) {
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
    bar.setPosition(bunnyData.x_pos + 65, bunnyData.y_pos);
}

void update(sf::Sprite &bunny, sf::RectangleShape &bar, sf::Text &debugText, float &tempsBoucle, float &pressedTime, BunnyData &bunnyData) {

    
    bunnyData.x_vel = 0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        bunnyData.x_vel += bunnyData.x_acc;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        bunnyData.x_vel -= bunnyData.x_acc;
    }
    if(bunnyData.grounded){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            bunny.setTexture(chargeTexture);
            pressedTime += tempsBoucle;
            bunnyData.jump_force = pressedTime * bunnyData.y_acc * CHARGE_ACCELERATION;
            if(bunnyData.jump_force > bunnyData.y_acc){
                bunnyData.jump_force = bunnyData.y_acc;
            }
            debugText.setString("Jump force : " + std::to_string(bunnyData.jump_force));
            bar.setScale(sf::Vector2f(1,-bunnyData.jump_force/MAX_JUMP_FORCE));
        } else{
            if(pressedTime != 0){
                bunny.setTexture(idleTexture);
                bunnyData.y_vel = -bunnyData.jump_force;
                bunnyData.jump_force = 0;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) bunnyData.x_vel = bunnyData.x_acc;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) bunnyData.x_vel = -bunnyData.x_acc;
                bunnyData.grounded = false;
                bar.setScale(sf::Vector2f(0,0));
            }
            pressedTime = 0;
            debugText.setString("Space is not pressed");
        }
    }

}

int main() {
    sf::RenderWindow fenetre{sf::VideoMode{1000, 600}, "bun"};

    idleTexture.loadFromFile("../assets/bunny_idle.png");
    chargeTexture.loadFromFile("../assets/bunny_charged.png");

    sf::Sprite bunny{};
    bunny.setTexture(idleTexture);
    bunny.setScale(2.5, 2.5);

    bunny.setOrigin(bunny.getLocalBounds().width / 2, bunny.getLocalBounds().height / 2);
    auto bunnyData = BunnyData{};

    // charge bar
    sf::RectangleShape bar(sf::Vector2f(17,50));
    bar.setScale(sf::Vector2f(1,0));
    bar.setFillColor(PINK);

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
        update(bunny, bar,debugText, tempsBoucle, pressedTime, bunnyData);
        move(bunny, bar, bunnyData, tempsBoucle);

        fenetre.clear(BEIGE);
        fenetre.draw(bunny);
        fenetre.draw(bar);
        fenetre.draw(debugText);
        fenetre.display();
    }
}






