#pragma once
#include "../Component.hpp"
#include "Transform2D.hpp"

class Transform2D;

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(); // Constructor: initialize with a name

    ~SpriteRenderer() { UnloadTexture(texture); }

    void update() override;
    void draw() const;

protected:
    mutable std::shared_ptr<Transform2D> transform;
    Texture2D texture;
    Image image;

    void getTransform();
};

SpriteRenderer::SpriteRenderer()
{
    // image = LoadImage("assets/Raylib_logo.png");
    image = GenImageColor(100, 100, BLACK);
    texture = LoadTextureFromImage(image);
}

void SpriteRenderer::update()
{
    getTransform();

}

void SpriteRenderer::draw() const
{
        DrawTextureV(texture, transform->getPosition(), Color{255, 255, 255, 255});
    
    if (!transform){
        std::cerr << "transform not found" << std::endl;
        return;
    }
}

void SpriteRenderer::getTransform()
{
    if (owner == nullptr)
    {
        std::cerr << "owner not found" << std::endl;
        return;
    }
    transform = owner->getComponent<Transform2D>();
    if (!transform)
    {
        transform = owner->addComponent<Transform2D>();
    }
}
