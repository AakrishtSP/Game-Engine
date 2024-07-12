#pragma once
#include "../Component.hpp"
#include "Transform2D.hpp"

class Transform2D;

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(); // Constructor: initialize with a name

    ~SpriteRenderer() { UnloadTexture(texture); }

    void update() override { std::cout << "SpriteRenderer update" << std::endl; };
    void draw() const;

protected:
    Texture2D texture;
    Image image;
};

SpriteRenderer::SpriteRenderer()
{
    // image = LoadImage("assets/Raylib_logo.png");
    image = GenImageColor(100, 100, BLACK);
    texture = LoadTextureFromImage(image);
}

void SpriteRenderer::draw() const
{
        auto transform = owner->getComponent<Transform2D>();
        DrawTextureV(texture, transform->getPosition(), Color{255, 255, 255, 255});
    
    if (!transform){
        std::cerr << "transform not found" << std::endl;
        return;
    }
}
