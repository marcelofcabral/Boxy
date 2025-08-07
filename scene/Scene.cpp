#include "Scene.h"

#include <iostream>
#include <ostream>

#include "../camera/Camera.h"
#include "../objects/Projectile.h"

Scene::Scene(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Object>& player) : camera{camera},
    player{player}
{
    objects.insert(player);
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
    objects.insert(object);
}

void Scene::remove(const std::shared_ptr<Object>& object)
{
    objects.erase(object);
}

void Scene::tick() const
{
    for (const std::shared_ptr<Object>& object : objects)
    {
        if (object->shouldTick)
        {
            object->tick();
        }
    }
}

void Scene::syncSceneToCamera() const
{
    if (camera->getViewChanged())
    {
        for (const std::shared_ptr<Object>& object : objects)
        {
            // the player sits in the center of the screen throughout gameplay. Everything else is moved
            if (object != player) object->syncViewMatrixToCamera();
        }
    }

    camera->setViewChanged(false);
}
