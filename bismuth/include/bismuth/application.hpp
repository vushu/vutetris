#pragma once
#include "scenemanager.hpp"
#include "iomanager.hpp"

#include <memory>

namespace bi {
    class Application {
    public:
        // constructors, asssignment, destructor
        Application();

        Application(std::string title);

        Application(int width, int height, std::string title);

        Application(glm::vec4 tileInfo, std::string title);

        Application(glm::vec2 resolution, glm::vec4 tileInfo, std::string title, bool lockFPS = true);

        ~Application();

        void loop();

        void run();

        void fixedLoop();

        Renderer &getRenderer();

        ShapeRenderer &getShapeRenderer();

        Window &getWindow();

        Camera &getCamera();

        AudioManager &getAudioManager();

        AssetManager &getAssetManager();

        Framebuffer &getMainFramebuffer();

        SceneManager &getSceneManager();

        IOManager &getIOManager();

        Cursor& getCursor();
    protected:

        virtual void init();
        virtual void processInput(float dt);
        virtual void update(float dt);
        virtual void render(float dt);


    private:

        const float FRAMES_PER_SEC = 1.0f / 60.0f;
        bool lockFPS = false;

        float accumulated;

        //std::shared_ptr<IOManager> ioManager;
        std::unique_ptr<SceneManager> scenemanager;

        void construct(glm::vec2 resolution, glm::vec4 tileInfo, std::string title, bool lockFPS = true);

        void applicationInit();

        void initOpenGL();

        void nativeLoop();

        std::string title;
        float beginTime;
        float endTime;
        float dt;


    };

}
