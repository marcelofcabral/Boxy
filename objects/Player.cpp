#include "Player.h"

#include "Projectile.h"
#include "../camera/Camera.h"
#include "../scene/Scene.h"

float Player::playerSpeed = 15.f;

shapes::Cuboid Player::shape{
    1.f,
    1.f,
    3.f
};

std::vector<float> Player::colors{
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
};

Player::Player(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Scene>& scene) : Object(camera,
    glm::vec3{0.f}, shape, colors,
    "./shaders/shader_sources/PlayerVertexShader.glsl",
    "./shaders/shader_sources/PlayerFragmentShader.glsl"), scene{scene}
{
}

void Player::shoot(const glm::vec3& direction)
{
    // revert view matrix transformations since Player is always on screen center (worldPosition is always 0, 0, 0)
    glm::vec3 position = glm::vec3(-camera->getViewMatrix()[3].x, -camera->getViewMatrix()[3].y, 0.5f) +
        direction;

    const auto projectilePtr{
        std::static_pointer_cast<Object>(std::make_shared<Projectile>(camera, scene, direction, position, ProjectileOrigin::Player))
    };

    scene->add(projectilePtr);
    scene->incrementProjectileCount();
}
