#include <iostream>
#include <string>
#include <raylib.h>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <vector>


class GameObject : public std::enable_shared_from_this<GameObject>{
public:
    GameObject(const std::string& name):name(name) {} // Constructor: initialize with a name

    template<typename T, typename... Args>
    T& addComponent(Args&&... args) { // Add a component to the game object
        //makes component a unique pointer to a instance of a component and pass args to the constructor of the component
        auto component = std::make_unique<T>(std::forward<Args>(args)...); 
        component->setOwner(shared_from_this()); //gives the component a pointer to the game object
        T& ref = *component; //dereference the component
        components[typeid(T)] = std::move(component); //move the component to the components map
        return ref;  //return the reference to the component
    }

    template<typename T>
    T* getComponent() {
        auto component = components.find(typeid(T)); //find the component in the components map of the type
        if (component != components.end()) {  //if the component is found
            return static_cast<T*>(component->second.get()); //return the component
        }
        return nullptr; //if the component is not found return null
    }

    //Creating Node system
    void addChild(std::shared_ptr<GameObject> child) {
        child->parent = shared_from_this(); //set the parent of the child to the current game object
        children.push_back(child); //add the child to the children vector
    }

    std::shared_ptr<GameObject> getParent() const { return parent.lock(); } //return the parent of the game object {lock the weak pointer to get the shared pointer}


    //Update function to update all the components
    void update() {
        for (auto& [type, component] : components) {
            component->update();
        }
    }


    virtual ~GameObject() {}
protected:
    std::string name;
    std::weak_ptr<GameObject> parent;   //weak pointer to the parent cuz we dont want child to keep the parent alive:- Only parent is allowed to keep the child alive
    std::vector<std::shared_ptr<GameObject>> children; //vector of shared pointers to the children
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};


class Component {
public:
    virtual ~Component() = default;
    virtual void update() = 0;
    void setOwner(GameObject* owner) { this->owner = owner; }

protected:
    GameObject* owner = nullptr;
};
