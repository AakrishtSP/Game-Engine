#pragma once
#include "../Component.hpp"



class Transform2D : public Component
{
public:
    Transform2D() : position({0, 0}), rotation(0), scale(1){}
    Vector2 getPosition() const { return position; }
    void setPosition(const Vector2 &position) { this->position = position; }
    float getRotation() const { return rotation; }
    void setRotation(float rotation) { this->rotation = rotation; }
    float getScale() const { return scale; }
    void setScale(const float &scale) { this->scale = scale; }
    Vector2 getWorldPosition() const { return worldPosition; }
    float getWorldRotation() const { return worldRotation; }
    float getWorldScale() const { return worldScale; }
    void translate(const Vector2 &translation) { position = position + translation; }
    void rotate(float rotation) { this->rotation += rotation; }
    Vector2 getGamePosition() { return gamePosition; }


    void transferOrigin();

    void calculateWorldPosition();

    void update() override;

protected:
    Vector2 position;
    float rotation;
    float scale;
    float worldScale;
    Vector2 worldPosition;
    float worldRotation;

    Vector2 gamePosition;
};

inline void Transform2D::transferOrigin()
{
    gamePosition = {(GetScreenWidth()/2) + worldPosition.x,(GetScreenHeight()/2) -worldPosition.y};
}

inline void Transform2D::calculateWorldPosition()
{
        if (owner == nullptr)
        {
            std::cerr << "owner not found" << std::endl;
            return;
        }
        auto parentObject = owner->getParent();
        if(parentObject == nullptr ){
            worldPosition = position;
            worldRotation = rotation;
            worldScale = scale;
            return;
        }
        else {
            auto parentTransform = parentObject->getComponent<Transform2D>();
            if (parentTransform) {
                worldPosition.x = parentTransform->worldPosition.x + position.x;
                worldPosition.y = parentTransform->worldPosition.y + position.y;
                worldRotation = parentTransform->worldRotation + rotation;
                worldScale = parentTransform->worldScale * scale;
            }
        }
}


void Transform2D::update()
{
    calculateWorldPosition();
    transferOrigin();
    // std::cout << "World Position: " << worldPosition.x << ", " << worldPosition.y << std::endl;
    // std::cout << "World Rotation: " << worldRotation << std::endl;
}