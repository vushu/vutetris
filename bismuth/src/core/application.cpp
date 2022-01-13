#include "bismuth/assetmanager.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/renderer.hpp"
#include <exception>
#include <stdexcept>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <bismuth/application.hpp>
#include <bismuth/logging.hpp>
#include <glm/glm.hpp>
#include <memory>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
using namespace bi;

Application::Application() {
    construct({800, 600}, {}, "Bismuth");
}

Application::Application(std::string title) {
    construct({0, 0}, {}, title);
}

Application::Application(glm::vec4 tileInfo, std::string title) {
    construct({0, 0}, tileInfo, title);
}

Application::Application(int width, int height, std::string title) {
    construct({width, height}, {}, title);
}

Application::Application(glm::vec2 resolution, glm::vec4 tileInfo, std::string title, bool lockFPS) {
    construct(resolution, tileInfo, title, lockFPS);
}

void Application::construct(glm::vec2 resolution, glm::vec4 tileInfo, std::string title, bool lockFPS) {
    getIOManager().construct(resolution, tileInfo, title);
    this->scenemanager = std::make_unique<SceneManager>();
    this->title = title;
    this->lockFPS = lockFPS;
}

Application::~Application() {
    log("Application: " + this->title + " is now destroyed");
}

void Application::run() {
    log("Running Application: " + title);
    applicationInit();
    init();
#ifdef __EMSCRIPTEN__
    beginTime = glfwGetTime();
    endTime = glfwGetTime();
    dt = 1.0f / 60.0f;
    //dt = -1.0f;
#else
    nativeLoop();
#endif
}

void Application::init() {}

void Application::processInput(float dt) {}

void Application::update(float dt) {}

void Application::render(float dt) {}

void Application::loop() {

    getWindow().pollEvents();

    getRenderer().resetStats();

    update(dt);

    this->scenemanager->update(dt);

    getWindow().swapBuffers();

    endTime = glfwGetTime();
    dt = endTime - beginTime;
    beginTime = endTime;
}

void Application::fixedLoop() {
    getWindow().pollEvents();

    getRenderer().resetStats();
    beginTime = glfwGetTime();
    dt = beginTime - endTime;
    accumulated += dt;

    getIOManager().setDeltaTime(dt);

    processInput(dt);
    this->scenemanager->processInput(dt);

    while (accumulated >= FRAMES_PER_SEC) {
        getIOManager().setDeltaTime(FRAMES_PER_SEC);
        update(FRAMES_PER_SEC);
        this->scenemanager->update(FRAMES_PER_SEC);
        accumulated -= FRAMES_PER_SEC;
        accumulated = std::max(0.0f, accumulated);
    }

    render(dt);
    this->scenemanager->render(dt);

    getWindow().swapBuffers();
    endTime = beginTime;
}

void Application::nativeLoop() {
    beginTime = glfwGetTime();
    endTime = glfwGetTime();
    dt = 1.0f / 60.0f;
    if (lockFPS) {
        bi::log("Game is fixed to 60 fps");
    }
    else {
        bi::log("Game is using variable time step");
    }
    while (!getWindow().windowShouldClose() && lockFPS) {
        fixedLoop();
    }

    while (!getWindow().windowShouldClose() && !lockFPS) {
        loop();
    }

    getIOManager().destroy();
}

void Application::initOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        log("Renderer: Failed to initialize GLAD");
        throw std::runtime_error("Renderer: Failed to initialize GLAD");
    }
    // alpha blending
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    //stencil buffer
    glEnable(GL_STENCIL_TEST);
}

void Application::applicationInit() {
    log("Application: init ====================================================");
    getWindow().init();
    initOpenGL();
    getRenderer().init();
    getShapeRenderer().init();
    getAssetManager().initDefaults();
    getCursor().init();
}

Renderer &Application::getRenderer() {
    return *bi::ioManager().renderer;
}

ShapeRenderer &Application::getShapeRenderer() {
    return *bi::ioManager().shaperenderer;
}

Window &Application::getWindow() {
    return *bi::ioManager().window;
}

Camera &Application::getCamera() {
    return *bi::ioManager().camera;
}

AudioManager &Application::getAudioManager() {
    return *bi::ioManager().audioManager;
}

AssetManager &Application::getAssetManager() {
    return *bi::ioManager().assetmanager;
}

Framebuffer &Application::getMainFramebuffer() {
    return *bi::ioManager().mainFramebuffer;
}

SceneManager &Application::getSceneManager() {
    return *this->scenemanager;
}

Cursor& Application::getCursor() {
    return *bi::ioManager().cursor;
}

IOManager &Application::getIOManager() {
    return bi::ioManager();
}
