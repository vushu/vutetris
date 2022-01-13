#pragma once

#include "renderer.hpp"
#include "iomanager.hpp"

namespace bi {
    class Scene {
    public:
        Scene();

        ~Scene();

        virtual void processInput(float dt);

        virtual void update(float dt);

        virtual void render(float dt);

        virtual void init();

        virtual void start();

        virtual void close();

        void sceneStart();

        void sceneInit();

        std::string nextScene = "";
        bool started = false;
    protected:
        Renderer &getRenderer();

        ShapeRenderer &getShapeRenderer();

        Window &getWindow();

        Camera &getCamera();

        AudioManager &getAudioManager();

        AssetManager &getAssetManager();

        TiledManager &getTileManager();

        Cursor& getCursor();
    private:
    };
}
