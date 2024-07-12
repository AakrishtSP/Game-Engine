#pragma once

#include "GameObject.hpp"

class GameObject;

class Component {
public:
    virtual ~Component() = default;
    virtual void update() = 0;
    void setOwner(GameObject* owner) { this->owner = owner; }

protected:
    GameObject* owner = nullptr;
};

