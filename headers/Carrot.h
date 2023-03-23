#ifndef BUN_CARROT_H
#define BUN_CARROT_H

#include "GameObject.h"
#include "Platform.h"

class Carrot : public GameObject{
public:
    // constructor
    explicit Carrot(int& p_score);
    void setPosition(float platformX, float platFormY, float platformHeight);

protected:
    // behavior when picked up
    void onRemoval() override;

private:
    // appearance
    static constexpr std::string_view CARROT_PATH{"../assets/carrot.png"};

    // score management
    int value{1};

    // TODO make it a reference to the game
    int& score;
};


#endif //BUN_CARROT_H
