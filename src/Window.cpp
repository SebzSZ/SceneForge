#include <iostream>
#include <stdexcept>

#include "Window.h"

// ==============================
// Constructor & Destructor
// ==============================
Window::Window(int width, int height, const std::string& title)
    : width_(width), height_(height), title_(title) {}
    
Window::~Window() {
    if (window_)
        glfwDestroyWindow(window_);
    if (glfwInitialized_)
        glfwTerminate();
}

// ==============================
// Inicialización
// ==============================
void Window::initialize() {
    if (glfwInitialized_)
        throw std::runtime_error("[Window] GLFW ya fue inicializado.");

    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
        throw std::runtime_error("[Window] No se pudo inicializar GLFW.");
    glfwInitialized_ = true;
    
    // Versión de OpenGL 3.3 con Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    // Para MacOS, se requiere habilitar la compatibilidad hacia adelante
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Crear la ventana
    window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
    if (!window_)
        throw std::runtime_error("[Window] No se pudo crear la ventana.");

    // Contexto de OpenGL y callback de cambio de tamaño
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);
    glfwSetWindowUserPointer(window_, this);
    glfwSetFramebufferSizeCallback(window_, framebufferSizeCallback);

    // Cargar GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("[Window] No se pudo cargar GLAD.");

    // Obtener el tamaño del framebuffer
    glfwGetFramebufferSize(window_, &framebufferWidth_, &framebufferHeight_);
    glViewport(0, 0, framebufferWidth_, framebufferHeight_);

    // Test de profundidad
    glEnable(GL_DEPTH_TEST);

    // Información de la ventana
    printSystemInfo();
}

// ==============================
// Configuración de la ventana
// ==============================
void Window::swapBuffers() {
    if (!window_)
        throw std::runtime_error("[Window] La ventana no ha sido inicializada.");

    glfwSwapBuffers(window_);
}

void Window::pollEvents() {
    if (!window_)
        throw std::runtime_error("[Window] La ventana no ha sido inicializada.");
    
    glfwPollEvents();
}

void Window::clear(float r, float g, float b, float a) {
    if (!window_)
        throw std::runtime_error("[Window] La ventana no ha sido inicializada.");

    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// ==============================
// Información del sistema
// ==============================
void Window::printSystemInfo() {
    const char* versionStr = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    const char* rendererStr = reinterpret_cast<const char*>(glGetString(GL_RENDERER));

    std::string version = versionStr ? versionStr : "Desconocido";
    std::string gpu = rendererStr ? rendererStr : "Desconocido";

    version = version.substr(0, version.find(' '));
    gpu = gpu.substr(0, gpu.find('/'));

    std::cout << "\n======================================================\n";
    std::cout << "[i] INFORMACIÓN DEL SISTEMA\n";
    std::cout << "======================================================\n";
    std::cout << "  > Ventana : " << title_ << " (" << width_ << "x" << height_ << ")\n";
    std::cout << "  > OpenGL  : " << version << "\n";
    std::cout << "  > GPU     : " << gpu << "\n";
    std::cout << "======================================================\n\n";
}

// ==============================
// Callbacks y eventos
// ==============================
void Window::glfwErrorCallback(int code, const char* description) {
    std::cerr << "[Window] Error de GLFW (" << code << ") — " << description << '\n';
}

void Window::framebufferSizeCallback(GLFWwindow* window, GLint width, GLint height) {
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (self) {
        self->framebufferWidth_ = width;
        self->framebufferHeight_ = height;
    }
    glViewport(0, 0, width, height);
}

// ==============================
// Cerrar ventana
// ==============================
bool Window::shouldClose() const {
    if (!window_)
        throw std::runtime_error("[Window] La ventana no ha sido inicializada.");

    return glfwWindowShouldClose(window_);
}

void Window::close() {
    if (!window_)
        throw std::runtime_error("[Window] La ventana no ha sido inicializada.");
    glfwSetWindowShouldClose(window_, GLFW_TRUE);
}