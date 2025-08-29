#include "Scene.h"

#include <iostream>
#include <ostream>

#include "../camera/Camera.h"
#include "../collision/CollisionManager.h"
#include "../objects/Projectile.h"

Scene::Scene(const std::shared_ptr<Camera>& camera) : camera{camera}
{
}

void Scene::render() const
{
    for (const std::shared_ptr<Object>& object : objects)
    {
        object->render();
    }
}

void Scene::add(const std::shared_ptr<Object>& object)
{
    const auto res{objects.insert(object)};

    if (res.second)
    {
        std::cout << "Objects added" << std::endl;
    }
}

bool Scene::contains(const std::shared_ptr<Object>& object)
{
    return objects.find(object) != objects.end();
}

bool Scene::isColliding(const std::shared_ptr<Object>& object) const
{
    for (const std::shared_ptr<Object>& other : objects)
    {
        if (other != object && CollisionManager::checkForBoxCollision(object, other))
        {
            std::cout << "Collision detected between " << object->id << " and " << other->id << std::endl;
            return true;
        }
    }

    // make player vs other objects collision work

    return false;
}

void Scene::remove(const std::shared_ptr<Object>& object)
{
    objects.erase(object);
}

void Scene::tick()
{
    for (const std::shared_ptr<Object>& object : objects)
    {
        if (object->shouldTick)
        {
            object->tick();
        }
    }

    for (const std::shared_ptr<Object>& object : toBeRemoved)
    {
        remove(object);
        std::cout << "removed object" << '\n';
    }

    toBeRemoved.clear();
}

void Scene::markForRemoval(const std::shared_ptr<Object>& object)
{
    toBeRemoved.push_back(object);
}

void Scene::setPlayer(const std::shared_ptr<Object>& player)
{
    this->player = player;
}

std::shared_ptr<Object> Scene::getPlayer() const
{
    return player;
}

void Scene::syncSceneToCamera() const
{
    if (camera->getViewChanged())
    {
        for (const std::shared_ptr<Object>& object : objects)
        {
            object->syncViewMatrixToCamera();
        }
    }

    camera->setViewChanged(false);
}

void Scene::incrementProjectileCount()
{
    ++projectileCount;
}

void Scene::decrementProjectileCount()
{
    --projectileCount;
}

void Scene::printProjectileCount() const
{
    std::cout << "Number of projectiles: " << projectileCount << '\n';
}

void Scene::toggleRenderCollisionBoxes()
{
    std::cout << "toggle render bb" << '\n';
    shouldRenderCollisionBoxes = !shouldRenderCollisionBoxes;
    
    for (const std::shared_ptr<Object>& object : objects)
    {
        object->shouldRenderBoundingBox = shouldRenderCollisionBoxes;
    }
}
