#pragma once

#include "GameObject.hpp"

class GameObject;

class Component {
public:
    virtual ~Component() = default;
    virtual void update() = 0;
    void setOwner(std::weak_ptr<GameObject> owner) { this->owner = owner.lock(); }

protected:
    std::shared_ptr<GameObject> owner;
};

