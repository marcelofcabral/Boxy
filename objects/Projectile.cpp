#include "Projectile.h"

#include "../utils/Timing.h"
#include "../scene/Scene.h"

shapes::Cuboid Projectile::shape{
    0.25f,
    0.25f,
    0.25f
};

std::vector<float> Projectile::colors{
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
};

Projectile::Projectile(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Scene>& scene, const glm::vec3& direction,
                       const glm::vec3& worldPosition, const float projectileSpeed)
    : Object(camera, worldPosition, shape.getVertices(), colors,
             shape.getIndices(),
             "./shaders/shader_sources/PlayerVertexShader.glsl",
             "./shaders/shader_sources/PlayerFragmentShader.glsl"),
      direction{direction}, projectileSpeed{projectileSpeed}, scene{scene}
{
    shouldTick = true;
}

void Projectile::tick()
{
    const glm::vec3 cameraPosition{camera->getViewMatrix()[3].x, camera->getViewMatrix()[3].y, 0.f};

    if (glm::distance(cameraPosition, glm::vec3{0.f}) >= 50.f)
    {
        scene->remove(std::static_pointer_cast<Object>(shared_from_this()));
        return;
    }

    move(direction * projectileSpeed * timing::deltaTime);
}
