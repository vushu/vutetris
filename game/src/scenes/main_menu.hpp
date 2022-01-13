#pragma once
#include "bismuth/gui/gui_window.hpp"
#include "bismuth/scene.hpp"
#include "bismuth/utils/counter.hpp"
namespace scenes {
    class MainMenu : public bi::Scene {
        public:
            MainMenu();
            ~MainMenu();

            void init() override;
            void start() override;
            void processInput(float dt) override;
            void update(float dt) override;
            void render(float dt) override;
            void close() override;
        private:
            void initWindow();
            bool fullscreen = false;
            std::unique_ptr<bi::gui::GuiWindow> windowMenu;
            std::shared_ptr<bi::gui::GuiButton> startBtn;
            std::shared_ptr<bi::gui::GuiButton> fullscreenBtn;
            std::shared_ptr<bi::gui::GuiButton> quitBtn;
            bi::utils::Counter counter{0,1};
            std::string mouseOverSoundFile = "resources/assets/audio/button_hover.mp3";
    };
}
