#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <raylib.h>
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <vector>

#include "Base.hpp"

class Transform2D : public Component
{
public:
    Transform2D() : position({0, 0}), rotation(0), scale({1, 1}) {}
    Vector2 getPosition() const { return position; }
    void setPosition(const Vector2 &position) { this->position = position; }
    float getRotation() const { return rotation; }
    void setRotation(float rotation) { this->rotation = rotation; }
    Vector2 getScale() const { return scale; }
    void setScale(const Vector2 &scale) { this->scale = scale; }
    Vector2 getWorldPosition() const { return worldPosition; }
    float getWorldRotation() const { return worldRotation; }

    void update() override;

protected:
    Vector2 position;
    float rotation;
    Vector2 scale;
    Vector2 worldPosition;
    float worldRotation;
};

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
void Transform2D::update()
{
    // auto ownerGameObject = owner.lock();
    // if (!ownerGameObject)
    // {
    //     std::cerr << "Error: Owner GameObject is expired!" << std::endl;
    //     return;
    // }
    // if (ownerGameObject->getParent().lock() == nullptr)
    // {
    //     std::cout << "Root GameObject" << std::endl;
    // }
    // else
    // {
    //     std::cout << "Child GameObject" << ownerGameObject->getParent().lock() << std::endl;
    //     std::weak_ptr<GameObject> parent = ownerGameObject->getParent();
    //     if (std::shared_ptr parentPtr = parent.lock())
    //     {
    //         auto parentTransform = parentPtr->getComponent<Transform2D>();
    //         if (parentTransform != nullptr)
    //         {
    //             worldPosition.x = parentTransform->worldPosition.x + position.x;
    //             worldPosition.y = parentTransform->worldPosition.y + position.y;
    //             worldRotation = parentTransform->worldRotation + rotation;
    //         }
    //         else
    //         {
    //             worldPosition = position;
    //             worldRotation = rotation;
    //         }
    //     }
    //     else
    //     {
    //         worldPosition = position;
    //         worldRotation = rotation;
    //     }
    // }
}

SpriteRenderer::SpriteRenderer()
{
    // image = LoadImage("assets/Raylib_logo.png");
    image = GenImageColor(100, 100, BLACK);
    texture = LoadTextureFromImage(image);
}

void SpriteRenderer::draw() const
{
    auto ownerGameObject = owner.lock();
    if (!ownerGameObject)
    {
        std::cerr << "Error: Owner GameObject is expired!" << std::endl;
        return;
    }

    auto transform = ownerGameObject->getComponent<Transform2D>();
    if (!transform)
    {
        std::cerr << "Error: Transform2D component not found!" << std::endl;
        return;
    }

    DrawTextureV(texture, transform->getPosition(), Color{255, 255, 255, 255});
}
