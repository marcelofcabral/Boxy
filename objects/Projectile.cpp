#define GLM_ENABLE_EXPERIMENTAL

#include "Projectile.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "Enemy.h"
#include "Player.h"
#include "../collision/CollisionManager.h"
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

Projectile::Projectile(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Scene>& scene,
                       const glm::vec3& direction,
                       const glm::vec3& worldPosition, ProjectileOrigin origin, const float projectileSpeed)
    : Object(camera, worldPosition, shape, colors,
             "./shaders/shader_sources/PlayerVertexShader.glsl",
             "./shaders/shader_sources/PlayerFragmentShader.glsl"),
      scene{scene}, direction{direction}, projectileSpeed{projectileSpeed}
{
    shouldTick = true;
    this->origin = origin;

    id = std::string("Projectile ") + std::to_string(std::rand());
}

void Projectile::tick()
{
    if (glm::distance(getPosition(), glm::vec3{0.f}) >= 110.f)
    {
        scene->markForRemoval(std::static_pointer_cast<Object>(shared_from_this()));
        return;
    }

    bool isOpponent = false;

    const bool isColliding{
        origin == ProjectileOrigin::Player
            ? scene->isColliding<Enemy>(shared_from_this(), &isOpponent)
            : scene->isColliding<Player>(shared_from_this(), &isOpponent)
    };

    if (isColliding)
    {
        scene->markForRemoval(std::static_pointer_cast<Object>(shared_from_this()));
        return;
    }

    move(direction * projectileSpeed * timing::deltaTime);
}
