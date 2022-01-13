#pragma once
#include "bismuth/color.hpp"
#include "bismuth/gui/gui_button.hpp"
#include "bismuth/scene.hpp"
#include "glm/fwd.hpp"
#include <bismuth/gui/gui_element.hpp>
namespace bi{
    namespace gui {
        class GuiWindow : public GuiElement {
            public:
                typedef std::function<void(GuiWindow&)> GuiWindowCallback;
                GuiWindow() {
                    currentName = "GuiWindow";
                }
                void draw() override;
                bool handleMouseClick(int action, glm::vec2 position);
                GuiWindow& setOutlineWidth(float outlineWidth);
                GuiWindow& setBackgroundColor(glm::vec4 color);
                GuiWindow& setOutlineColor(glm::vec4 color);
                GuiWindow& setSize(glm::vec2 size);
                bool mouseClicked();
                bool mouseReleased();
                void processDragging();
                void close();
                void show();

                Font font;
                float outlineWidth = 4.0f;
                glm::vec4 outlineColor = color::SOFT_BLUE;
                glm::vec4 backgroundColor = color::WHITE;
                bool isCloseButtonActivated = false;
                bool isClosed = false;
                bool isMouseOver = false;
                GuiButton closeButton;
                bool isDragging = false;
                bool closeButtonActivated = false;
                void processInput() override;
                void onMouseOver(GuiWindowCallback callback);
                void addScene(Scene* scene);
            private:
                Scene* scene;
                void handleMouseOver();
                void dragging();
                void draggingEnd();
                std::string sceneName;
                glm::vec2 windowMouseDiff;
                glm::vec2 positionBottomRight(glm::vec2 size);
                glm::vec2 positionTopRight(glm::vec2 size);
                GuiWindowCallback mouseOverCallback;
        };
    }
}
