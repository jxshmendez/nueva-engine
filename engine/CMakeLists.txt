find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_library(Engine
        source/Engine.hpp
        source/Engine.cpp
        source/Application.hpp
        source/Application.cpp
        source/input/InputManager.hpp
        source/input/InputManager.cpp
        source/graphics/ShaderProgram.hpp
        source/graphics/ShaderProgram.cpp
        source/graphics/GraphicsAPI.hpp
        source/graphics/GraphicsAPI.cpp
        source/render/Material.hpp
        source/render/Material.cpp
        source/render/Mesh.hpp
        source/render/Mesh.cpp
        source/render/RenderQueue.hpp
        source/render/RenderQueue.cpp
        source/scene/GameObject.hpp
        source/scene/GameObject.cpp
        source/scene/Scene.hpp
        source/scene/Scene.cpp
        source/eng.hpp
        vendor/include/glad.c
        vendor/include/stb_image.cpp
)

target_include_directories(Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/include
)

target_link_libraries(Engine PUBLIC
        OpenGL::GL
        glfw
)
