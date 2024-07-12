#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <raylib.h>
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <vector>
#include "Component.hpp"


class Component; // Forward declaration of Component

class GameObject : public std::enable_shared_from_this<GameObject>{
public:

    GameObject(const std::string& name): name(name) {}

    std::string getName() const { return name; }

    template<typename T>
    T& addComponent();

    template<typename T>
    T* getComponent();

    void addChild(std::shared_ptr<GameObject> child);
    GameObject& addChild(const std::string& name);

    std::weak_ptr<GameObject> getParent() const;

    void update();

    virtual ~GameObject() {}

protected:
    std::string name;
    std::weak_ptr<GameObject> parent;
    std::vector<std::shared_ptr<GameObject>> children;
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
};



template<typename T>
T& GameObject::addComponent() {
    auto component = std::make_shared<T>();
    component->setOwner(shared_from_this());
    T& ref = *component;
    components[std::type_index(typeid(T))] = component;
    return ref;
}


template<typename T>
T* GameObject::getComponent() {
    auto component = components.find(std::type_index(typeid(T)));
    if (component != components.end()) {
        return static_cast<T*>(component->second.get());
    }
    return nullptr;
}

void GameObject::addChild(std::shared_ptr<GameObject> child) {
    child->parent = shared_from_this();
    children.push_back(child);
}

GameObject& GameObject::addChild(const std::string& name) {
    auto child = std::make_shared<GameObject>(name);
    child->parent = shared_from_this();
    children.push_back(child);
    addChild(child);
    return *child;
}

std::weak_ptr<GameObject> GameObject::getParent() const {
    return parent;
}

void GameObject::update() {
    // Use a local copy of components to avoid issues with modification during iteration
    auto currentComponents = components;

    for (auto& [type, component] : currentComponents) {
        if (component) {
            component->update();
        } else {
            // Handle case where component has been removed or is invalid
            components.erase(type);
        }
    }
}
