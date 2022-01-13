#pragma once

#include <string>
#include <memory>
#include <map>
#include "scene.hpp"
#include "iomanager.hpp"

namespace bi {

    class SceneManager {
    public:
        // constructors, asssignment, destructor
        SceneManager();

        ~SceneManager();

        void addScene(std::string name, std::unique_ptr<Scene> scene, bool isStart = false);

        void setScene(std::string name);

        void processInput(float dt);

        void update(float dt);

        void render(float dt);


    private:
        std::string currentScene = "";
        std::map<std::string, std::unique_ptr<Scene>> scenes;
    };
}
