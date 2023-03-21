#ifndef BUN_CARROT_H
#define BUN_CARROT_H

#include "GameObject.h"

class Carrot : public GameObject{
public:
    // constructor
    explicit Carrot();

protected:
    // behavior when picked up
    void onRemoval() override;

private:
    // appearance
    static constexpr std::string_view CARROT_PATH{"../assets/carrot.png"};
};


#endif //BUN_CARROT_H
