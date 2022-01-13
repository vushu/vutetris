#pragma once
#include <array>
#include <string>
#include <glm/glm.hpp>
#include "color.hpp"
namespace bi{
    class Cursor{
        public:
            // constructors, assignment, destructor
            Cursor(std::string cursorFilePath) : cursorFilePath(cursorFilePath) {};
            ~Cursor();
            void init();
            void draw();
            void setMouseOver(bool enable);
            void setColor(glm::vec4 color);
            void setTexture(std::string cursorFilePath);
            glm::vec2 size {32, 32};
            glm::vec2 offset {-4,-2};
        private:
            std::string cursorFilePath;
            int cursorTextureId;
            glm::vec4 color = color::WHITE;
            bool isMouseOver = false;
            std::array<glm::vec2, 4> currentTextCoord;

            static constexpr std::array<glm::vec2, 4> pointerCursorTexcoords = {
                glm::vec2(0.5f, 1.0f), //br
                glm::vec2(0.5f, 0.0f), //tr
                glm::vec2(0.0f, 0.0f),//tl
                glm::vec2(0.0f, 1.0f)//bl
            };
            static constexpr std::array<glm::vec2, 4> mouseOverCursorTexcoords = {

                glm::vec2(1.0f, 1.0f), //br
                glm::vec2(1.0f, 0.0f), //tr
                glm::vec2(0.5f, 0.0f),//tl
                glm::vec2(0.5f, 1.0f)//bl
            };



    };
}
