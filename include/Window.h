#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();
    
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    
    // ==============================
    // Control de la ventana
    // ==============================
    void initialize();
    void swapBuffers();
    void pollEvents();
    void clear(float r, float g, float b, float a);
    bool shouldClose() const;
    void close();
    
    // ==============================
    // Dimensiones y acceso a la ventana
    // ==============================
    int getBufferWidth() const { return framebufferWidth_; }
    int getBufferHeight() const { return framebufferHeight_; }
    float getAspectRatio() const {
        if (framebufferHeight_ == 0)
        return 1.0f;
        
        return static_cast<float>(framebufferWidth_) / framebufferHeight_;
    }
    GLFWwindow* getHandle() const { return window_; }

    // ==============================
    // Estado interno y callbacks
    // ==============================
private:
   GLFWwindow* window_ = nullptr;
   GLint width_;
   GLint height_; 
   std::string title_;

   GLint framebufferWidth_ = 0;
   GLint framebufferHeight_ = 0;

   bool glfwInitialized_ = false;

   void printSystemInfo();
   static void framebufferSizeCallback(GLFWwindow* window, GLint width, GLint height);
   static void glfwErrorCallback(int code, const char* description);
};