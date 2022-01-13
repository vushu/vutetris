#pragma once
#include "scenes/gui_window_scene.hpp"
#include <bismuth/bismuth.hpp>
class GuiTest : public bi::Application{
    public:
        GuiTest() : bi::Application(1024, 768, "bismuth") {
        }
        ~GuiTest();
    private:
        void setupGuiEvents();
    protected:
        void init() override;
        void update(float dt) override;
        void render(float dt) override;
        void processInput(float dt) override;
        std::shared_ptr<bi::gui::GuiLabel> bismuthLabel;
        std::unique_ptr<scenes::GuiWindowScene> guiWindowScene;
        std::string bismuthSoundFile = "resources/assets/audio/bismuth.wav";
        std::string explosionSoundFile = "resources/assets/audio/explosion.wav";
        bi::utils::Counter bismuthCounter{0, 0.1f};
};
