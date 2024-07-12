#include <raylib.h>
#include <iostream>

// #include "Base.hpp"
#include "BaseComponents.hpp"

int main()
{
    GameObject root("Root");
    auto rootTransform = root.addComponent<Transform2D>();
    // auto rootSprite = root.addComponent<SpriteRenderer>();

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