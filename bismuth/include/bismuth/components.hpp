#pragma once
#include <string>
namespace bi {
    namespace components {
        struct Sprite {
            std::string name;
            bool flip = false;
        };

        struct Position {
            float x, y;
        };

        struct Velocity {
            float dx, dy;
        };
    }
}
