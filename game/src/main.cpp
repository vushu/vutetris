#include "game.hpp"
#include <bismuth/logging.hpp>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
Game game;

void loop() {
    game.loop();
}
int main() {
    //bi::isLogging = false;
    game.run();
#ifdef __EMSCRIPTEN__
    bi::isLogging = false;
    emscripten_set_main_loop(loop, 0 ,-1);
#endif

}

