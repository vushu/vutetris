#include "bismuth/assetmanager.hpp"
#include "bismuth/iomanager.hpp"
#include <bismuth/scene.hpp>
using namespace bi;

Scene::Scene() { }

Scene::~Scene() { }

void Scene::sceneInit() {
}

void Scene::init() {}

void Scene::sceneStart() {
    if (!started) {
        start();
        started = true;
    }
}

void Scene::start() {}
void Scene::close() {}
void Scene::update(float dt) {}
void Scene::render(float dt) {}
void Scene::processInput(float dt) {}

Renderer& Scene::getRenderer() {
    return *bi::ioManager().renderer;
}

ShapeRenderer& Scene::getShapeRenderer() {
    return *bi::ioManager().shaperenderer;
}

Window& Scene::getWindow() {
    return *bi::ioManager().window;
}

Camera& Scene::getCamera() {
    return *bi::ioManager().camera;
}

AudioManager& Scene::getAudioManager() {
    return *bi::ioManager().audioManager;
}

AssetManager& Scene::getAssetManager() {
    return *bi::ioManager().assetmanager;
}

TiledManager& Scene::getTileManager() {
    return *bi::ioManager().tiledManager;
}

Cursor& Scene::getCursor() {
    return *bi::ioManager().cursor;
}


