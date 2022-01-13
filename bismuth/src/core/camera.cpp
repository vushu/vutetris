#include "bismuth/logging.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <bismuth/camera.hpp>
#include <glm/glm.hpp>

using namespace bi;

Camera::~Camera() {
    bi::log("Camera destroyed");
}

void Camera::adjustProjection(float width, float height) {
    projectionMatrix = glm::mat4(1.0);
    //camera viewport
    projectionMatrix = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 100.0f);
    inverseProjectionMatrix = glm::inverse(projectionMatrix);
    inverseViewMatrix = glm::inverse(viewMatrix);
    //projectionMatrix = glm::orthoRH(0.0f, 32.0f * 40.0f, 0.0f, 32.0f * 40.0f, 0.0f, 1.0f);
    //projectionMatrix = glm::orthoLH(0.0f, 225.0f * 40.0f, 0.0f, 225.0f * 21.0f, 0.0f, 100.0f);
}

void Camera::zoom(float scaleFactor) {
    this->width *= scaleFactor;
    this->height *= scaleFactor;
    adjustProjection(this->width, this->height);
}

void Camera::setPosition(glm::vec2 pos) {
    this->position = pos;
    //this->viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(pos,0));
}

glm::mat4 Camera::getViewMatrix() {
    glm::vec3 cameraFront{0.0f,0.0f,-1.0f};
    glm::vec3 cameraUp{0.0f,1.0f,0.0f};

    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::lookAt({position.x, position.y, 20.0f}, cameraFront + glm::vec3(position.x, position.y, 0.0f), cameraUp);

    this->inverseViewMatrix = glm::inverse(this->viewMatrix);
    return this->viewMatrix;
}

glm::mat4 Camera::getInversePV() {
    //return this->inverseViewMatrix * this->inverseProjectionMatrix;
    return this->inverseProjectionMatrix * this->inverseViewMatrix;
}

