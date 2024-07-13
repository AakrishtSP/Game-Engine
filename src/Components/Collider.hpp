#pragma once

#include "../Component.hpp"
#include "Transform2D.hpp"

class Transform2D;



class Collider: public Component
{
public:
    Collider();
    ~Collider();

    void update() override;


private:
    mutable std::shared_ptr<Transform2D> transform = nullptr;
    Rectangle rectangle;
    Vector2 offset;
};

Collider::Collider()
{

}

Collider::~Collider()
{
}

void Collider::update()
{
}
