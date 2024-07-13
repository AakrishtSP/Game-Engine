#pragma once

#include "../Component.hpp"
#include "Transform2D.hpp"

class Transform2D;

class Collider: public Component
{
public:


private:
    mutable std::shared_ptr<Transform2D> transform = nullptr;
    Vector2 offset;
};