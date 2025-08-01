#include "Scene.h"

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

void Scene::updateViewMatrix(const glm::mat4& viewMatrix, const std::set<std::shared_ptr<Object>>& except)
{
    for (const std::shared_ptr<Object>& object : objects)
    {
        if (except.find(object) == except.end()) object->updateViewMatrix(viewMatrix);
    }
}
