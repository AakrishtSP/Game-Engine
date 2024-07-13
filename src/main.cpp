// #include "Component.hpp"
// #include "Components/Components.hpp"
#include "Base.hpp"

int main()
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Raylib Game Engine");

    while(!IsWindowReady());

    GameObject root("Root");
    auto child1 = root.addChild("Child1");
    auto rootTransform = root.addComponent<Transform2D>();
    auto rootSprite = root.addComponent<SpriteRenderer>();
    std::cout << "after components" << std::endl;

    rootSprite->loadImage("./assets/Raylib_logo.png");
    rootSprite->resizeImage(100, 100);
    rootSprite->initTexture();
    rootTransform->setPosition({400, 225});
    rootSprite->getTransform();

    SetTargetFPS(60); // Set the game to run at 60 frames-per-second

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Draw
        BeginDrawing();

        ClearBackground(GRAY); // Clear the screen to white
        root.update();
        // rootSprite->draw();
        DrawText("this IS a texture loaded from an image!", 300, 370, 10, RED);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}