#include <cstdlib>
#include <exception>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#include "Input.h"
#include "Window.h"

int main() {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    try {
        Window window(800, 600, "SceneForge");
        window.initialize();

        Input input(window.getHandle());

        // ==============================
        // Bucle principal
        // ==============================
        while (!window.shouldClose()) {
            window.pollEvents();
            input.update();

            // Cerrar la ventana al presionar ESC
            if (input.isKeyPressed(GLFW_KEY_ESCAPE))
                window.close();

            window.clear(0.0157f, 0.0392f, 0.1216f, 1.0000f);

            /*
            Escenario futuro
            */

            window.swapBuffers();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}