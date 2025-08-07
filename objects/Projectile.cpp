#include "Projectile.h"

#include "../utils/Timing.h"

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

Projectile::Projectile(const std::shared_ptr<Camera>& camera, const glm::vec3& direction,
                       const glm::vec3& worldPosition, const float projectileSpeed)
    : Object(camera, worldPosition, shape.getVertices(), colors,
             shape.getIndices(),
             "./shaders/shader_sources/PlayerVertexShader.glsl",
             "./shaders/shader_sources/PlayerFragmentShader.glsl"),
      direction{direction}, projectileSpeed{projectileSpeed}
{
    shouldTick = true;
}

void Projectile::tick()
{
    move(direction * projectileSpeed * timing::deltaTime);
}
