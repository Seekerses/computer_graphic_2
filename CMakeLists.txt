cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)

project(computer_graphic VERSION 1.0 DESCRIPTION "Computer Graphics Laboratory work" LANGUAGES CXX)

find_package(directxtk CONFIG REQUIRED)

add_executable(computer_graphic
        src/Main.cpp
        src/Game/Game.cpp
        src/Input/InputDevice.cpp
        src/Window/Window.cpp
        src/Renderer/Renderer.cpp
        src/Scene/SceneManager.cpp
        src/Components/Component.cpp
        src/Components/Script/ScriptComponent.cpp
        src/Components/Scene/Transform.cpp
        src/Components/Scene/SceneComponent.cpp
        src/Components/Scene/Render/ShaderComponent.cpp
        src/Components/Scene/Render/RenderComponent.cpp
        src/Components/Scene/Render/MeshComponent.cpp
        src/Object/Object.cpp
        src/Object/GameObject/GameObject.cpp
        src/Object/GameObject/Primitives/Triangle.cpp
        src/Object/GameObject/Primitives/Rectangle.cpp
        src/Asset/Shader/ShaderAsset.cpp
        src/Asset/Mesh/MeshAsset.cpp
        src/Types/Vertex.cpp
        src/Utils/Delegates.cpp
)

add_subdirectory(src)

target_link_libraries(computer_graphic Microsoft::DirectXTK)