#pragma once
#include "renderer.hpp"
#include "shaperenderer.hpp"
#include "window.hpp"
#include "audiomanager.hpp"
#include "framebuffer.hpp"
#include "tiledmanager.hpp"
#include "cursor.hpp"
#include <memory>
namespace bi {

    class IOManager {
        public:
            IOManager();
            ~IOManager();
            void init();

            std::unique_ptr<Renderer> renderer;
            std::unique_ptr<Window> window;
            std::unique_ptr<Camera> camera;
            std::unique_ptr<AudioManager> audioManager;
            std::unique_ptr<AssetManager> assetmanager;
            std::unique_ptr<Framebuffer> mainFramebuffer;
            std::unique_ptr<ShapeRenderer> shaperenderer;
            std::unique_ptr<TiledManager> tiledManager;
            std::unique_ptr<Cursor> cursor;
            float getDeltaTime();
            void setDeltaTime(float dt);
            void construct(glm::vec2 resolution, glm::vec4 tileInfo, std::string);
            void destroy();
            static IOManager& get() {
                static IOManager instance;
                return instance;
            }
        private:
            glm::vec2 resolution;
            std::string title;
            glm::vec4 tileInfo;
            float deltaTime = 0;

    };

    bi::IOManager& ioManager();

}
