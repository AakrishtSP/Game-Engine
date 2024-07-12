#pragma once
#include "../Component.hpp"
#include "Transform2D.hpp"

class Transform2D;
class GameObject;

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(); 
    ~SpriteRenderer();

    void update() override;
    void draw() const;

protected:
    mutable std::shared_ptr<Transform2D> transform = nullptr;
    Texture2D texture;
    Image image;
    void getTransform();
};

SpriteRenderer::SpriteRenderer()
{
    // image = LoadImage("assets/Raylib_logo.png");
    image = GenImageColor(100, 100, BLACK);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

SpriteRenderer::~SpriteRenderer()
{
    UnloadTexture(texture);
    UnloadImage(image);
}

void SpriteRenderer::update()
{
    if (!transform)
    {
        getTransform();
    }
    draw();
}

void SpriteRenderer::draw() const
{
    if (transform) {
        DrawTextureV(texture, transform->getPosition(), WHITE);
    } else {
        std::cerr << "Transform not available for drawing." << std::endl;
    }
}

void SpriteRenderer::getTransform()
{
    if (!owner)
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
