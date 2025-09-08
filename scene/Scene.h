#pragma once
#include <iostream>
#include <memory>
#include <set>

#include "../collision/CollisionManager.h"
#include "../objects/Fighter.h"
#include "../rendering/Drawable.h"
#include "../objects/Object.h"
#include "../objects/Projectile.h"

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

    template <class T>
    bool isColliding(const std::shared_ptr<Object>& object, bool* outIsOpponent = nullptr) const;

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

// this excessive use of dynamic_pointer_cast certainly is not good, but I believe it's okay for this simple application
template <class T>
bool Scene::isColliding(const std::shared_ptr<Object>& object, bool* outIsOpponent) const
{
    for (const std::shared_ptr<Object>& other : objects)
    {
        if (other != object && CollisionManager::checkForBoxCollision(object, other))
        {
            // const bool isObjectProjectile{std::dynamic_pointer_cast<Projectile>(object)};
            const bool isOtherProjectile{std::dynamic_pointer_cast<Projectile>(other)};

            if (isOtherProjectile) continue;
            
            if (outIsOpponent)
            {
                *outIsOpponent = std::dynamic_pointer_cast<T>(other) != nullptr;

                if (*outIsOpponent)
                {
                    const auto& fighter{std::dynamic_pointer_cast<Fighter>(other)};
                    fighter->takeDamage();
                }
            }

            return true;
        }
    }

    return false;
}