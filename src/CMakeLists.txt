add_subdirectory(Asset)
add_subdirectory(Components)
add_subdirectory(Object)

target_include_directories(computer_graphic PRIVATE
        Asset
        Components
        Game
        Input
        Object
        Renderer
        Scene
        Types
        Utils
        Window
)