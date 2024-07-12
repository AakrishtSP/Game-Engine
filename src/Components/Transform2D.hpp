#pragma once
#include "../Component.hpp"



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

void Transform2D::update()
{
        std::cout << "Child GameObject" << owner->getParent().lock() << std::endl;
        auto parentObject = owner->getParent();
        if (auto parentTransform = parentObject.lock()->getComponent<Transform2D>())
        {
            worldPosition.x = parentTransform->worldPosition.x + position.x;
            worldPosition.y = parentTransform->worldPosition.y + position.y;
            worldRotation = parentTransform->worldRotation + rotation;
        }
        else
        {
            worldPosition = position;
            worldRotation = rotation;
        }

}