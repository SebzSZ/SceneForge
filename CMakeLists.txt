cmake_minimum_required(VERSION 3.16)
project(SceneForge LANGUAGES C CXX)

include(FetchContent)

# ==============================
# Descarga de dependencias
# ==============================
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

# ==============================
# Opciones de compilación de GLFW
# ==============================
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# ==============================
# Configuración de la aplicación
# ==============================
add_executable(ForgeApp
    src/main.cpp
    src/Input.cpp
    src/Window.cpp
    src/glad.c
)

# ==============================
# Enlaces y opciones de compilación
# ==============================
target_include_directories(ForgeApp PRIVATE include)
target_link_libraries(ForgeApp PRIVATE glfw)
target_compile_features(ForgeApp PRIVATE cxx_std_17)
target_compile_definitions(ForgeApp PRIVATE GLFW_INCLUDE_NONE)
target_compile_options(ForgeApp PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
set_target_properties(ForgeApp PROPERTIES CXX_EXTENSIONS OFF)