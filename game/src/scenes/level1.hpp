#pragma once
#include "bismuth/gui/gui_label.hpp"
#include "bismuth/scene.hpp"
#include "../blocks/board.hpp"
#include <memory>
namespace scenes {
    class Level1 : public bi::Scene {
        public:
            Level1();
            ~Level1();

            void init() override;
            void start() override;
            void processInput(float dt) override;
            void update(float dt) override;
            void render(float dt) override;
            void close() override;
        private:
            int tilesize = 16;
            std::shared_ptr<bi::gui::GuiLabel> title;
            blocks::Board board;
    };
}
