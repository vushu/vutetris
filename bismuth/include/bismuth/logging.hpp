#pragma once
#include <string>
#include "animatedsprite.hpp"

namespace bi {

    extern bool isLogging;
    void log(std::string message);
    void log(std::string from, std::string message);
    void log(float message);
    void log(int message);
    void log(std::string from,int message);
    void log(std::string from,float message);
    void log(std::string from, bool value);
    void log(std::string from, glm::vec2 vec);
}
