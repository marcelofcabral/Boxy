#include "Fighter.h"

#include "Projectile.h"
#include "../collision/CollisionManager.h"
#include "../scene/Scene.h"
#include "../utils/Timing.h"

float Fighter::speed = 20.f;

shapes::Cuboid Fighter::shape{
    1.f,
    1.f,
    3.f
};

Fighter::Fighter(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Scene>& scene,
                 const std::vector<float>& colors, const glm::vec3& worldPosition) : Object(camera,
    worldPosition, shape, colors,
    "./shaders/shader_sources/PlayerVertexShader.glsl",
    "./shaders/shader_sources/PlayerFragmentShader.glsl"), scene{scene}, health{5}
{
}

bool Fighter::move(const glm::vec3& direction)
{
    const glm::vec3 movementVector = direction * speed * timing::deltaTime;
    
    modelMatrix[3] += glm::vec4{movementVector, 0.0f};

    const bool willCollide = modelMatrix[3].x < -50.f ||
        modelMatrix[3].y < -50.f || modelMatrix[3].x > 50.f || modelMatrix[3].y > 50.f || scene->isColliding<Object>(
            shared_from_this());

    if (!willCollide)
    {
        Object::move(movementVector, true);
    }
    else
    {
        modelMatrix[3] -= glm::vec4{movementVector, 0.0f};
    }

    return !willCollide;
}

void Fighter::takeDamage()
{
    --health;

    if (health == 0)
    {
        scene->markForRemoval(shared_from_this());
    }
}

void Fighter::shoot(const glm::vec3& direction, ProjectileOrigin projectileOrigin)
{
    glm::vec3 position = glm::vec3(modelMatrix[3].x, modelMatrix[3].y, -1.f) +
        direction * 2.f;

    const auto projectilePtr{
        std::static_pointer_cast<Object>(
            std::make_shared<Projectile>(camera, scene, direction, position, projectileOrigin))
    };

    scene->add(projectilePtr);
    scene->incrementProjectileCount();
}
