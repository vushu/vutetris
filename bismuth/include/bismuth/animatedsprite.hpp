#pragma once
#include <map>
#include <bismuth/animation.hpp>
namespace bi {
    class AnimatedSprite{
        public:
            AnimatedSprite();
            ~AnimatedSprite();
            void addAnimation(Animation animation);
            void addAnimation(std::string name, int texId, std::vector<int> tileNumbers, glm::vec2 size, glm::vec4 color, float frameTime);
            void play(std::string name, glm::vec2 position, glm::vec2 size, float angle = 0.0f);

        private:
            std::map<std::string, Animation> animations;


    };
}
