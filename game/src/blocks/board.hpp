#pragma once
#include "bismuth/gui/gui_button.hpp"
#include "bismuth/utils/counter.hpp"
#include "block.hpp"
#include <map>
#include <string>
namespace blocks {
    class Board{
        public:
            Board();
            ~Board();
            void draw();
            void init();
            void setCurrentBlock(std::string letter);
            void print(std::string letter);
            void centerPosition();
            void update();
            void processInput();
            void isHittingGround();

        private:
            void setupDebugButton();
            std::shared_ptr<bi::gui::GuiButton> leftDebugButton;
            std::shared_ptr<bi::gui::GuiButton> rightDebugButton;
            std::shared_ptr<bi::gui::GuiButton> upDebugButton;
            std::shared_ptr<bi::gui::GuiButton> downDebugButton;
            std::shared_ptr<bi::gui::GuiButton> rotateRightDebugButton;
            std::shared_ptr<bi::gui::GuiButton> rotateLeftDebugButton;
            void drawDebugButtons();
            bool isColliding();
            bi::utils::Counter counter{0, 1};
            void drawGrid();
            int tilesize = 16;
            std::string currentBlock = "L";
            std::map<std::string, Block> tetrominoes;
            glm::vec2 position = {0,0};
    };
}
