#include <iostream>
#include "../headers/ObjectManager.h"
#include "../headers/Platform.h"
#include "../headers/Carrot.h"
#include "../headers/Bunny.h"

// INITIALIZATION --------------------------------------------------------------------

void ObjectManager::addObject(std::unique_ptr<GameObject> object, std::vector<std::unique_ptr<GameObject>> &gameObjects) {
    gameObjects.push_back(std::move(object));
}

void ObjectManager::initializeGame() {
    // to reset parameters
    hasLost = false;
    score = -1;
    bunnyInLowerScreen = true;

    // generating lower screen
    generatePlatforms(gameObjectsLowerScreen);
    checkPlatformValidity(gameObjectsLowerScreen);
    generateCarrots(gameObjectsLowerScreen);

    // generating upper screen
    generatePlatforms(gameObjectsUpperScreen);
    checkPlatformValidity(gameObjectsUpperScreen);
    generateCarrots(gameObjectsUpperScreen);

    // generating bunny in the lower screen
    generateBunny(gameObjectsLowerScreen);

    // to reset the chrono since it started at the ObjectManager creation,
    // which is not necessarily when the game actually starts
    chrono.restart().asSeconds();
}

void ObjectManager::generatePlatforms(std::vector<std::unique_ptr<GameObject>> &gameObjects) {
    // generating 7 platforms of different types
    addObject(std::make_unique<Platform>(Platform::PlatformLevel::LOW), gameObjects);
    addObject(std::make_unique<Platform>(Platform::PlatformLevel::LOW), gameObjects);
    addObject(std::make_unique<Platform>(Platform::PlatformLevel::MIDDLE), gameObjects);
    addObject(std::make_unique<Platform>(Platform::PlatformLevel::MIDDLE), gameObjects);
    addObject(std::make_unique<Platform>(Platform::PlatformLevel::MIDDLE), gameObjects);
    addObject(std::make_unique<Platform>(Platform::PlatformLevel::HIGH), gameObjects);
    addObject(std::make_unique<Platform>(Platform::PlatformLevel::HIGH), gameObjects);
}

void ObjectManager::checkPlatformValidity(std::vector<std::unique_ptr<GameObject>> &gameObjects) {
    // checking if platforms collide and regenerating them if necessary
    // the number is arbitrarily high to make sure all collisions have been handled before adding carrots
    for(auto _{0u}; _       < NB_COLLISION_TESTS; ++_){
        for(auto i{0u}; i < gameObjects.size(); ++i){
            for(auto j{0u}; j < gameObjects.size(); ++j){
                if(i != j){
                    gameObjects[i]->testCollision(*gameObjects[j]);
                }
            }
        }
    }
}

void ObjectManager::generateCarrots(std::vector<std::unique_ptr<GameObject>> &gameObjects) {
    // adding a carrot on top of each platform in the list of game objects
    for(auto i{0u}; i < gameObjects.size(); ++i){
        if(gameObjects[i]->getType() == ObjectType::PLATFORM){
            std::unique_ptr<Carrot> carrot = std::make_unique<Carrot>(score);
            carrot->setPosition(gameObjects[i]->getX(), gameObjects[i]->getY(), gameObjects[i]->getHeight());
            gameObjects.push_back(std::move(carrot));
        }
    }
}


void ObjectManager::generateBunny(std::vector<std::unique_ptr<GameObject>> &gameObjects) {
    // generating the bunny on the first platform of the screen
    sf::Vector2f initialPosition{gameObjects[0]->getX(), gameObjects[0]->getY() - gameObjects[0]->getHeight() / 3};
    addObject(std::make_unique<Bunny>(initialPosition, *this), gameObjects);
}

void ObjectManager::generateBunny(std::vector<std::unique_ptr<GameObject>> &gameObjects, sf::Vector2f initialPosition, sf::Vector2f initialVelocity) {
    // generating the bunny with the given position and velocity
    addObject(std::make_unique<Bunny>(initialPosition, *this, initialVelocity), gameObjects);
}

// GAME LOOP --------------------------------------------------------------------

void ObjectManager::update(std::vector<std::unique_ptr<GameObject>> &gameObjects) {
    auto loopTime = chrono.restart().asSeconds();
    for(auto i{0u}; i < gameObjects.size(); ++i){
        gameObjects[i]->update(loopTime);
    }
}

void ObjectManager::updateCurrentScreen() {
    if(bunnyInLowerScreen) {
        update(gameObjectsLowerScreen);
    }
    else {
        update(gameObjectsUpperScreen);
    }
}

void ObjectManager::handleCollisions(std::vector<std::unique_ptr<GameObject>> &gameObjects) {
    for(auto i{0u}; i < gameObjects.size(); ++i){
        for(auto j{0u}; j < gameObjects.size(); ++j){
            if(i != j){
                gameObjects[i]->testCollision(*gameObjects[j]);
            }
        }
    }
}

void ObjectManager::handleCollisionsInCurrentScreen() {
    if(bunnyInLowerScreen) {
        handleCollisions(gameObjectsLowerScreen);
    }
    else {
        handleCollisions(gameObjectsUpperScreen);
    }
}

void ObjectManager::display(sf::RenderWindow &window, std::vector<std::unique_ptr<GameObject>> &gameObjects) {
    for(auto& gameObject : gameObjects){
        gameObject->display(window);
    }
}

void ObjectManager::displayCurrentScreen(sf::RenderWindow &window) {
    if(bunnyInLowerScreen) {
        display(window, gameObjectsLowerScreen);
    }
    else {
        display(window, gameObjectsUpperScreen);
    }
}

// SCREEN MANAGEMENT  --------------------------------------------------------------------

bool ObjectManager::noMoreCarrots(std::vector<std::unique_ptr<GameObject>> &gameObjects) {
    for(auto i{0u}; i < gameObjects.size(); ++i){
        if(gameObjects[i]->getType() == ObjectType::CARROT){
            if(!gameObjects[i]->isRemoved()) return false;
        }
    }
    return true;
}

bool ObjectManager::noMoreCarrotsInCurrentScreen() {
    if(bunnyInLowerScreen) {
        return noMoreCarrots(gameObjectsLowerScreen);
    }
    else {
        return noMoreCarrots(gameObjectsUpperScreen);
    }
}

void ObjectManager::generateNewScreen(sf::Vector2f initialBunnyPosition, sf::Vector2f initialBunnyVelocity) {
    toClear = true;
    bunnyStartPosition = initialBunnyPosition;
    bunnyStartVelocity = initialBunnyVelocity;
}

void ObjectManager::changeScreen(sf::Vector2f initialBunnyPosition, sf::Vector2f initialBunnyVelocity) {
    toChange = true;
    bunnyStartPosition = initialBunnyPosition;
    bunnyStartVelocity = initialBunnyVelocity;
}

void ObjectManager::gameOver() {
    hasLost = true;
}

void ObjectManager::manageScreens() {
    if(toClear){ // new screen generation
        gameObjectsLowerScreen.clear();
        gameObjectsUpperScreen.pop_back(); // removing the bunny from the upper screen

        // the upper screen becomes the lower screen
        for(auto i{0u}; i < gameObjectsUpperScreen.size(); ++i){
            gameObjectsLowerScreen.push_back(std::move(gameObjectsUpperScreen[i]));
        }

        gameObjectsUpperScreen.clear();

        // generating a new upper screen
        generatePlatforms(gameObjectsUpperScreen);
        checkPlatformValidity(gameObjectsUpperScreen);
        generateCarrots(gameObjectsUpperScreen);

        // generating bunny in the upper screen
        generateBunny(gameObjectsUpperScreen, bunnyStartPosition, bunnyStartVelocity);

        toClear = false;
    }

    if(toChange){ // switching between existing screens
        if(bunnyInLowerScreen){ // removing the bunny from the lower screen to put it in the upper screen
            gameObjectsLowerScreen.pop_back();
            generateBunny(gameObjectsUpperScreen, bunnyStartPosition, bunnyStartVelocity);
        } else{ // removing the bunny from the upper screen to put it in the lower screen
            gameObjectsUpperScreen.pop_back();
            generateBunny(gameObjectsLowerScreen, bunnyStartPosition, bunnyStartVelocity);
        }
        bunnyInLowerScreen = !bunnyInLowerScreen;
        toChange = false;
    }

    if(gameIsOver() || gameIsWon()){ // ending the game
        gameObjectsUpperScreen.clear();
        gameObjectsLowerScreen.clear();
    }
}




