#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include <bismuth/scenemanager.hpp>

using namespace bi;

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {
    bi::log("Destroying scenemanager");
    if (scenes.count(this->currentScene) > 0) {
        bi::log("Closing currentScene " + this->currentScene);
        this->scenes.at(this->currentScene)->close();
    }
}

void SceneManager::addScene(std::string name, std::unique_ptr<Scene> scene, bool isStart) {
    if (name.empty()) {
        bi::log("No scene name defined, scene isn't added");
        return;
    }
    scene->sceneInit();
    scene->init();
    scenes.emplace(name, std::move(scene));
    if (currentScene == "" && isStart)
        setScene(name);
}

void SceneManager::setScene(std::string name) {
    if (scenes.count(name) > 0)
        this->currentScene = name;
}

void SceneManager::update(float dt) {

    if (scenes.count(currentScene) > 0) {
        scenes.at(currentScene)->sceneStart();
        scenes.at(currentScene)->update(dt);

        std::string nextScene = scenes.at(currentScene)->nextScene;

        if (!nextScene.empty() && scenes.count(nextScene) > 0) {
            bi::log("nextScene:", nextScene);
            scenes.at(currentScene)->nextScene = "";
            scenes.at(currentScene)->started = false;
            scenes.at(currentScene)->close();
            bi::keyInput().reset();
            setScene(nextScene);
        }
    }
}

void SceneManager::render(float dt) {
    if (scenes.count(currentScene) > 0)
        scenes.at(currentScene)->render(dt);
}

void SceneManager::processInput(float dt) {
    if (scenes.count(currentScene) > 0)
        scenes.at(currentScene)->processInput(dt);
}
