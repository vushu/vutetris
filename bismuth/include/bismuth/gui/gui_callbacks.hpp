#pragma once
#include <functional>
namespace bi {
    namespace gui {
        class GuiButton;
        typedef std::function<void(GuiButton&)> GuiButtonCallback;
    }
}
