cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)

project(computer_graphic VERSION 1.0 DESCRIPTION "Computer Graphics Laboratory work" LANGUAGES CXX)

find_package(directxtk CONFIG REQUIRED)

add_executable(computer_graphic src/Main.cpp
        src/Input/InputDevice.cpp
        src/Game/Game.cpp
        src/Utils/Delegates.cpp
        src/Window/Window.cpp
        src/Window/Window.h
        src/Renderer/Renderer.cpp
        src/Renderer/Renderer.h
        src/Object/Components/Scene/Render/ShaderComponent.cpp
        src/Object/Components/Scene/Render/ShaderComponent.h
        src/Object/Primitives/Triangle.cpp
        src/Object/Primitives/Triangle.h
        src/Renderer/SceneManager.cpp
        src/Renderer/SceneManager.h
        src/Object/Components/Scene/Render/RenderComponent.cpp
        src/Utils/SMath.h
        src/Object/Components/Scene/Render/MeshComponent.cpp
        src/Object/Object.cpp
        src/Object/Object.h
        src/Renderer/Vertex.cpp
        src/Renderer/Vertex.h
        src/Object/Primitives/Rectangle.cpp
        src/Object/Primitives/Rectangle.h
        src/Utils/Colors.h
        src/Object/Components/Scene/Transform.cpp
        src/Object/Components/Scene/Transform.h
        src/Object/Components/Scene/SceneComponent.cpp
        src/Object/Components/Scene/SceneComponent.h
        src/Object/Components/Component.cpp
        src/Object/Components/Component.h
)

target_link_libraries(computer_graphic Microsoft::DirectXTK)