#pragma once
#include "bismuth/animatedsprite.hpp"
#include "bismuth/gui/gui_element.hpp"
namespace bi {
    namespace gui {
        class GuiAnimatedSprite : public GuiElement {
            public:
                GuiAnimatedSprite() {animatedSprite = std::make_shared<AnimatedSprite>();};
                ~GuiAnimatedSprite() {};
                void addAnimation(Animation animation);
                void setAnimation(std::string animationName);
                void addAnimation(std::string name, int texId, std::vector<int> tileNumbers, glm::vec2 size, glm::vec4 color, float frameTime);
                void setAnimatedSprite(std::shared_ptr<AnimatedSprite> animatedsprite);
                void draw() override;
            private:
                std::shared_ptr<AnimatedSprite> animatedSprite;
                std::string currentAnimation = "";

        };
    }
}
