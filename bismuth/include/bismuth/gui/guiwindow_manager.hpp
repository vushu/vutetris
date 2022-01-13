#pragma once
#include <memory>
#include <vector>
#include <map>
#include "gui_window.hpp"
namespace bi{
    namespace gui{
        class GuiWindowManager{
            public:
                // constructors, assignment, destructor
                GuiWindowManager();
                ~GuiWindowManager();

                GuiWindowManager& add(std::unique_ptr<GuiWindow> window);
                void processInput();
                void update();
                void draw();


            private:
                bool isOnceClicked = false;
                std::vector<std::unique_ptr<GuiWindow>> windows;
        };
    }
}
