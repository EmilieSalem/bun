#include "../headers/ObjectManager.h"
#include "../headers/Platform.h"
#include "../headers/Carrot.h"
#include "../headers/Bunny.h"

ObjectManager::ObjectManager() = default;

void ObjectManager::addObject(std::unique_ptr<GameObject> object) {
    gameObjects.push_back(std::move(object));
}

void ObjectManager::initializeGame() {
    generatePlatforms();
    checkPlatformValidity();
    generateCarrots();
    generateBunny();
}

void ObjectManager::generatePlatforms() {
    // generating 2 of each type of platform
    addObject(std::make_unique<Platform>(Platform::PlatformLevel::LOW));
    addObject(std::make_unique<Platform>(Platform::PlatformLevel::LOW));
    addObject(std::make_unique<Platform>(Platform::PlatformLevel::MIDDLE));
    addObject(std::make_unique<Platform>(Platform::PlatformLevel::MIDDLE));
    addObject(std::make_unique<Platform>(Platform::PlatformLevel::MIDDLE));
    addObject(std::make_unique<Platform>(Platform::PlatformLevel::HIGH));
    addObject(std::make_unique<Platform>(Platform::PlatformLevel::HIGH));
}

void ObjectManager::checkPlatformValidity() {
    // checking if platforms collide and regenerating them if necessary
    // the number is arbitrarily high to make sure all collisions have been handled before adding carrots
    for(auto _{0u}; _       < NB_COLLISION_TESTS; ++_){
        for(auto i{0u}; i<gameObjects.size(); ++i){
            for(auto j{0u}; j<gameObjects.size(); ++j){
                if(i != j){
                    gameObjects[i]->testCollision(*gameObjects[j]);
                }
            }
        }
    }
}

void ObjectManager::generateCarrots() {
    // adding a carrot on top of each platform in the list of game objects
    for(auto i{0u}; i<gameObjects.size(); ++i){
        if(gameObjects[i]->getType() == ObjectType::PLATFORM){
            std::unique_ptr<Carrot> carrot = std::make_unique<Carrot>(score);
            carrot->setPosition(gameObjects[i]->getX(), gameObjects[i]->getY(), gameObjects[i]->getHeight());
            gameObjects.push_back(std::move(carrot));
        }
    }
}


void ObjectManager::generateBunny() {
    sf::Vector2f initialPosition{gameObjects[0]->getX(), gameObjects[0]->getY() - gameObjects[0]->getHeight()/3};
    addObject(std::make_unique<Bunny>(initialPosition));
}

void ObjectManager::update() {
    auto loopTime = chrono.restart().asSeconds();
    for(auto i{0u}; i<gameObjects.size(); ++i){
        gameObjects[i]->update(loopTime);
    }
}

void ObjectManager::handleCollisions() {
    for(auto i{0u}; i<gameObjects.size(); ++i){
        for(auto j{0u}; j<gameObjects.size(); ++j){
            if(i != j){
                gameObjects[i]->testCollision(*gameObjects[j]);
            }
        }
    }
}

void ObjectManager::display(sf::RenderWindow &window) {
    for(auto& gameObject : gameObjects){
        gameObject->display(window);
    }
}



