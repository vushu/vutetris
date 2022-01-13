#pragma once
#include "bismuth/bismuth.hpp"
namespace scenes{
    class GuiWindowScene : public bi::Scene {
        public:
            GuiWindowScene();
            ~GuiWindowScene();

            void init() override;
            void start() override;
            void processInput(float dt) override;
            void update(float dt) override;
            void render(float dt) override;
            void close() override;
        private:
            void setupGuiEvents();
            void setupAnimations();
            std::unique_ptr<bi::gui::GuiWindow> window;
            std::shared_ptr<bi::gui::GuiLabel> fpsLabel;
            std::shared_ptr<bi::gui::GuiButton> startBtn;
            std::shared_ptr<bi::gui::GuiTexture> guiTexture;
            std::shared_ptr<bi::gui::GuiAnimatedSprite> guiAnimatedSprite;

            std::string bismuthSoundFile;
            std::string plingSoundFile;
            std::string explosionSoundFile;
            std::string tickSoundFile;
            bi::utils::Counter counter{10, 1.0f};
    };
}
