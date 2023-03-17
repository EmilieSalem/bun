#ifndef BUN_PLATFORM_H
#define BUN_PLATFORM_H

#include "GameObject.h"

class Platform : public GameObject {
public:
    explicit Platform();

protected:

private:
    static constexpr std::string_view PLATFORM_PATH{"../assets/platform.png"};

};


#endif //BUN_PLATFORM_H
