#include <bismuth/keylistener.hpp>
#include <bismuth/mouselistener.hpp>
#include <bismuth/window.hpp>
#include <bismuth/logging.hpp>
#include <glad/glad.h>
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
using namespace bi;

void errorCallback(int error, const char* description) {
    log("Window: " + std::string(description));
}

void bi::Window::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0,0, width, height);
}

void Window::resizeWindowCallback(GLFWwindow* window, int width, int height) {
    Window* ptr = reinterpret_cast<bi::Window*>(glfwGetWindowUserPointer(window));
    if (ptr) {
        ptr->width = width;
        ptr->height = height;
    }
}
Window::Window(std::string title) {
    this->title = title;
}

Window::Window(int width, int height, std::string title) {
    this->width = width;
    this->height = height;
    this->title = title;
}

Window::~Window() {
    //destroy();
}

void Window::destroy() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::fullscreen() {
    fullscreen(maxWidth, maxHeight);
}

void Window::fullscreen(int width, int height) {
    this->isFullscreen = true;
    glfwSetWindowMonitor(this->window, glfwGetPrimaryMonitor(), 0,0, width, height, 0);
}

void Window::windowed(int width, int height) {
    this->isFullscreen = false;
    glfwSetWindowMonitor(this->window, nullptr, 0,0, width, height, 0);
}
void Window::configureOpenGL() {
    //#ifdef __EMSCRIPTEN__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    //glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    //glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // antialiasing;
    //glfwWindowHint(GLFW_SAMPLES, 4);

    //#else

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    //#endif

    //glfwDefaultWindowHints();
}

void Window::setupCallbacks() {
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, bi::KeyListener::keyCallback);
    glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));
    glfwSetWindowSizeCallback(window, bi::Window::resizeWindowCallback);
    glfwSetFramebufferSizeCallback(window, bi::Window::frameBufferSizeCallback);
    glfwSetCursorPosCallback(window, bi::MouseListener::mousePosCallback);
    glfwSetMouseButtonCallback(window, bi::MouseListener::mouseButtonCallback);
    glfwSetScrollCallback(window, bi::MouseListener::mouseScrollCallback);
}

void Window::pollEvents() {
    glfwPollEvents();
}

bool Window::windowShouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

glm::vec2 Window::maxSize() {
    return { maxWidth, maxHeight };
}

glm::vec2 Window::size() {
    return { width, height };
}

void Window::close() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::init() {

    if (!glfwInit()) {
        log("Window: GLFW failed to initialized!");
        throw std::runtime_error("Failed to init GLFW");
    }

    getResolution();
    configureOpenGL();

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (window == NULL) {
        bi::log("Window: Failed to create GLFW window");
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW Window");
    }

    glfwMakeContextCurrent(window);
    //ENABLE VSYNC
    glfwSwapInterval(GLFW_TRUE);

    setupCallbacks();

    bi::log("Window: GLFW window successfully created!");
}

void Window::getResolution() {
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    maxWidth = mode->width;
    maxHeight = mode->height;

    if (this->width == 0 && this->height == 0){
        this->width = maxWidth;
        this->height = maxHeight;
    }
    bi::log("width max", maxWidth);
    bi::log("height max", maxHeight);
}


