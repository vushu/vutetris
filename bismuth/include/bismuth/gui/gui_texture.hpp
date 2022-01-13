#pragma once
#include "gui_element.hpp"
namespace bi{
    namespace gui{
        class GuiTexture : public GuiElement {
            public:
                GuiTexture(std::string filepath) : filepath(filepath) {}
                void init();
                void draw() override;
                void setColor(glm::vec4 color);

            protected:
                glm::vec4 color = {1, 1, 1, 1};
                std::string filepath;
                int textureId;
        };
    }
}
