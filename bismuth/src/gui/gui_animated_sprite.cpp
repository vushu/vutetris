#include "bismuth/iomanager.hpp"
#include "bismuth/gui/gui_animated_sprite.hpp"
#include "bismuth/animatedsprite.hpp"
using namespace bi;
using namespace gui;

void GuiAnimatedSprite::setAnimation(std::string animationName) {
    this->currentAnimation = animationName;
}

void GuiAnimatedSprite::setAnimatedSprite(std::shared_ptr<AnimatedSprite> animatedsprite) {
    this->animatedSprite = animatedsprite;
}

void GuiAnimatedSprite::addAnimation(bi::Animation animation) {
    this->animatedSprite->addAnimation(animation);
}

void GuiAnimatedSprite::addAnimation(std::string name, int texId, std::vector<int> tileNumbers, glm::vec2 size, glm::vec4 color, float frameTime) {
    this->animatedSprite->addAnimation(name, texId, tileNumbers, size, color, frameTime);
}

void GuiAnimatedSprite::draw() {
    if (!currentAnimation.empty()) {
        animatedSprite->play(currentAnimation, this->position, this->size);
    }
}

