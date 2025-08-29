#define GLM_ENABLE_EXPERIMENTAL

#include "Player.h"

#include <glm/gtx/string_cast.hpp>

#include "Projectile.h"
#include "../camera/Camera.h"
#include "../scene/Scene.h"

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

Player::Player(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Scene>& scene) : Fighter(camera,
    scene, colors, glm::vec3{0.f})
{
    id = std::string("Player ") + std::to_string(std::rand());
}

void Player::shoot(const glm::vec3& direction)
{
    // revert view matrix transformations since Player is always on screen center (worldPosition is always 0, 0, 0)
    glm::mat4 inversedViewMatrix{glm::inverse(camera->getViewMatrix())};

    // not sure why the inverse matrix has the y coordinate about -25 units of where it is supposed to be.
    // I'll investigate, but I'll leave this hack here meanwhile
    glm::vec3 position = glm::vec3(inversedViewMatrix[3].x, inversedViewMatrix[3].y + 25.f, 0.5f) +
        direction;

    const auto projectilePtr{
        std::static_pointer_cast<Object>(
            std::make_shared<Projectile>(camera, scene, direction, position, ProjectileOrigin::Player))
    };

    scene->add(projectilePtr);
    scene->incrementProjectileCount();
}
