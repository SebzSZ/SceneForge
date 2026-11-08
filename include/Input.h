#pragma once

#include <array>
#include <GLFW/glfw3.h> 

class Input {
public:
    // Evita que un puntero a GLFWwindow se convierta implícitamente en un objeto Input
    explicit Input(GLFWwindow* window);

    void update();
    bool isKeyDown(int key) const;
    bool isKeyPressed(int key) const;

    // ==============================
    // Estado interno
    // ==============================
private:
    GLFWwindow* window_;
    std::array<bool, GLFW_KEY_LAST + 1> current_{};
    std::array<bool, GLFW_KEY_LAST + 1> previous_{};

    static bool isValidKey(int key);
};