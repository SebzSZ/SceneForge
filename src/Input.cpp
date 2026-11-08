#include "Input.h"

Input::Input(GLFWwindow* window) : window_(window) {}

// ==============================
// Actualización del estado de las teclas
// ==============================
void Input::update() {
    // Guardar el estado anterior para detectar nuevas pulsaciones
    previous_ = current_;

    for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++)
        current_[key] = (glfwGetKey(window_, key) == GLFW_PRESS);
}

// ==============================
// Consultas del estado de las teclas
// ==============================
bool Input::isKeyDown(int key) const {
    return isValidKey(key) && current_[key];
}

bool Input::isKeyPressed(int key) const {
    return isValidKey(key) && current_[key] && !previous_[key];
}

// ==============================
// Validación de teclas
// ==============================
bool Input::isValidKey(int key) {
    return key >= GLFW_KEY_SPACE && key <= GLFW_KEY_LAST;
}