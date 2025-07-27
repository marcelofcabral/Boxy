#include "Scene.h"

void Scene::render() const
{
    for (const std::shared_ptr<IRenderable>& renderable : renderables)
    {
        renderable->render();
    }
}

void Scene::addRenderable(const std::shared_ptr<IRenderable>& renderable)
{
    renderables.insert(renderable);
}

void Scene::removeRenderable(const std::shared_ptr<IRenderable>& renderable)
{
    renderables.erase(renderable);
}
