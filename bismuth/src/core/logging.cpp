#include <bismuth/logging.hpp>
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/gtx/string_cast.hpp>
bool bi::isLogging = true;

void bi::log(std::string message) {

    if (bi::isLogging) {
        std::cout << message << std::endl;
    }
}
void bi::log(int message) {

    if (bi::isLogging) {
        std::cout << std::to_string(message) << std::endl;
    }
}
void bi::log(std::string from, int message) {

    if (bi::isLogging) {
        std::cout<< from << " " << std::to_string(message) << std::endl;
    }
}

void bi::log(std::string from, float message) {

    if (bi::isLogging) {
        std::cout<< from << " " << std::to_string(message) << std::endl;
    }
}

void bi::log(float message) {

    if (bi::isLogging) {
        std::cout << std::to_string(message) << std::endl;
    }
}

void bi::log(std::string from, std::string message) {

    if (bi::isLogging) {
        std::cout << from << " " << message << std::endl;
    }
}

void bi::log(std::string from, glm::vec2 vec) {

    if (bi::isLogging) {
        std::cout << from << " " << glm::to_string(vec) << std::endl;
    }
}

void bi::log(std::string from, bool value) {

    if (bi::isLogging) {
        std::cout << from << " " << (value ? "true" : "false") << std::endl;
    }
}
