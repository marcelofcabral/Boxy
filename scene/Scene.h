#pragma once
#include <memory>
#include <set>

#include "../rendering/Drawable.h"
#include "../objects/Object.h"

class Camera;

class Scene
{
private:
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Object> player;

    uint8_t projectileCount = 0;

    std::vector<std::shared_ptr<Object>> toBeRemoved;
    
public:
    explicit Scene(const std::shared_ptr<Camera>& camera);
    
    void render() const;
    void add(const std::shared_ptr<Object>& object);

    template <class T>
    std::shared_ptr<T> find();
    
    void tick();
    void markForRemoval(const std::shared_ptr<Object>& object);
    void setPlayer(const std::shared_ptr<Object>& player);

    void syncSceneToCamera() const;

    void incrementProjectileCount();
    void decrementProjectileCount();
    void printProjectileCount() const;

private:
    std::set<std::shared_ptr<Object>> objects;

    void remove(const std::shared_ptr<Object>& object);
};

template <class T>
std::shared_ptr<T> Scene::find()
{
    for (const std::shared_ptr<Object>& object : objects)
    {
        if (std::shared_ptr<T> dynamicPtr = std::dynamic_pointer_cast<T>(object))
        {
            return dynamicPtr;
        }
    }

    return nullptr;
}
