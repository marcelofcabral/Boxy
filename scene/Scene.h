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
    void tick();
    
    void add(const std::shared_ptr<Object>& object);
    bool contains(const std::shared_ptr<Object>& object);
    bool isColliding(const std::shared_ptr<Object>& object) const;

    template <class T>
    std::shared_ptr<T> findByClass();
    
    void markForRemoval(const std::shared_ptr<Object>& object);
    void setPlayer(const std::shared_ptr<Object>& player);
    std::shared_ptr<Object> getPlayer() const;

    void syncSceneToCamera() const;

    void incrementProjectileCount();
    void decrementProjectileCount();
    void printProjectileCount() const;

    bool shouldRenderCollisionBoxes = false;
    void toggleRenderCollisionBoxes();

private:
    std::set<std::shared_ptr<Object>> objects;

    void remove(const std::shared_ptr<Object>& object);
};

template <class T>
std::shared_ptr<T> Scene::findByClass()
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
