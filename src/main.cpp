// #include "Component.hpp"
// #include "Components/Components.hpp"
#include "Base.hpp"

int main()
{
    std::cout << "before objects" << std::endl;
    GameObject root("Root");
    std::cout << "after objects"  << root.getName()  << std::endl;

    

    auto child1 = root.addChild("Child1");

    auto dummyComponent = root.addComponent<EmptyComponent>();
    auto rootTransform = root.addComponent<Transform2D>();
    auto rootSprite = root.addComponent<SpriteRenderer>();
    std::cout << "after components" << std::endl;


    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Game Engine");

    SetTargetFPS(60); // Set the game to run at 60 frames-per-second

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE); // Clear the screen to white

        // rootSprite.draw();

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}