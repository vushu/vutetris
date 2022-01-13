#pragma once
#include "bismuth/font.hpp"
#include "bismuth/gui/gui_element.hpp"
#include "bismuth/color.hpp"
#include "bismuth/iomanager.hpp"
namespace bi {
    namespace gui{

        class GuiLabel : public GuiElement{
            public:
                GuiLabel() {
                    this->font = bi::ioManager().assetmanager->getDefaultFont();
                    currentName = "GuiLabel";
                };

                GuiLabel(Font* font) {
                    this->font = font;
                    currentName = "GuiLabel";
                };

                void setText(std::string text);
                void setColor(glm::vec4 color);
                void setFont(Font* font);
                void draw() override;
                bool isClicked = false;
                float fontScale = 0.5f;
            private:
                glm::vec4 color = color::SOFT_YELLOW;
                Font* font;
                std::string text = "";
        };
    }
}
