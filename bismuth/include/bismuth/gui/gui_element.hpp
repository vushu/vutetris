#pragma once
#include <functional>
#include <glm/glm.hpp>
#include <map>
#include <math.h>
#include <memory>
#include <vector>
#include "bismuth/collision/collision.hpp"
#include "bismuth/gui/gui_style.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/mouse.hpp"
#include "bismuth/mouselistener.hpp"
#include "glm/fwd.hpp"
namespace bi {
    namespace gui {
        class GuiElement{
            public:
                virtual ~GuiElement() {
                    log("Destroying", currentName);
                }

                GuiElement& getParent() {
                    return *parent;
                }

                virtual void draw() = 0;

                void setPosition(glm::vec2 position) {
                    this->position = position + offset;

                    for (auto& child : children) {
                        child->setPositionByPlacement(this->position, this->size);
                    }

                }

                void setPositionByPlacement(glm::vec2 parentPosition, glm::vec2 parentSize) {
                    switch (placement) {
                        case CENTER:
                            positionCenterTo(parentPosition, parentSize);
                            break;
                        case TOP_LEFT:
                            positionTopLeft(parentPosition);
                            break;
                        case TOP_RIGHT:
                            positionTopRightTo(parentPosition, parentSize);
                            break;
                        case TOP_CENTER:
                            positionTopCenterTo(parentPosition, parentSize);
                            break;
                        case BOTTOM_LEFT:
                            positionBottomLeftTo(parentPosition, parentSize);
                            break;
                        case BOTTOM_RIGHT:
                            positionBottomRightTo(parentPosition, parentSize);
                            break;
                        case BOTTOM_CENTER:
                            positionBottomCenterTo(parentPosition, parentSize);
                            break;
                        default:
                            positionTopLeft(parentPosition);

                    }
                }

                void add(std::shared_ptr<GuiElement> guielement) {
                    guielement->parent = this;
                    setPositionByPlacement(position, size);
                    this->children.push_back(guielement);
                }


                void add(std::shared_ptr<GuiElement> guielement, unsigned int placement) {
                    guielement->parent = this;
                    guielement->placement = placement;
                    setPositionByPlacement(position, size);
                    this->children.push_back(guielement);
                }

                void setOffset(glm::vec2 offset) {
                    this->offset = offset;
                }

                void setSize(glm::vec2 size) {
                    this->size = size;
                }

                void setScale(float scale) {
                    this->scale = scale;
                    this->size *= scale;
                }

                bool isPositionWithinRect(glm::vec2 position){
                    return bi::collision::isPositionWithinRect(position, this->position,  this->size);
                }

                void positionTopLeft(glm::vec2 parentPosition){
                    setPosition(parentPosition);
                }

                void positionTopRightTo(glm::vec2 parentPosition, glm::vec2 sizeOfParent){
                    setPosition({parentPosition.x + (sizeOfParent.x - size.x) , parentPosition.y});
                }

                void positionBottomLeftTo(glm::vec2 parentPosition, glm::vec2 sizeOfParent){
                    setPosition({parentPosition.x, parentPosition.y + (sizeOfParent.y - size.y)});
                }

                void positionBottomRightTo(glm::vec2 parentPosition, glm::vec2 sizeOfParent){
                    setPosition({parentPosition.x + (sizeOfParent.x - size.x) , parentPosition.y + sizeOfParent.y - size.y});
                }

                void positionCenterLeftTo(glm::vec2 parentPosition, glm::vec2 sizeOfParent){
                    setPosition({parentPosition.x, parentPosition.y + (sizeOfParent.y - size.y) * 0.5f});
                }

                void positionCenterRightTo(glm::vec2 parentPosition, glm::vec2 sizeOfParent){
                    setPosition({ parentPosition.x + sizeOfParent.x - size.x, parentPosition.y + (sizeOfParent.y - size.y) * 0.5f});
                }

                void positionCenterTo(glm::vec2 parentPosition, glm::vec2 sizeOfParent){
                    setPosition(parentPosition + (sizeOfParent * 0.5f) - (size * 0.5f));
                }

                void positionBottomCenterTo(glm::vec2 parentPosition, glm::vec2 sizeOfParent){
                    setPosition({parentPosition.x + sizeOfParent.x * 0.5f - size.x * 0.5f, parentPosition.y + sizeOfParent.y - size.y});
                }

                void positionTopCenterTo(glm::vec2 parentPosition, glm::vec2 sizeOfParent){
                    setPosition({parentPosition.x + sizeOfParent.x * 0.5f - size.x * 0.5f, parentPosition.y});
                }

                void setVisible(bool visible) {
                    this->visible = visible;
                }

                void virtual processInput(){};

                glm::vec2 position = {0,0}, size = {0,0}, offset = {0,0};
                unsigned int placement = TOP_LEFT;
                GuiElement* parent = nullptr;
                bool visible = true;

            protected:
                std::vector<std::shared_ptr<GuiElement>> children;
                std::string currentName = "GuiElement";
                std::string backgroundTextureFile;
                float scale = 1;

        };
    }
}
