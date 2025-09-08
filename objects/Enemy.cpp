#include "Enemy.h"

#include <random>
#include <GLFW/glfw3.h>

#include "Projectile.h"
#include "../camera/Camera.h"
#include "../scene/Scene.h"
#include "../objects/Player.h"

float Enemy::shotInterval = .58f;

std::vector<float> Enemy::colors{
    1.f, 0.f, 0.f, 1.f,
    1.f, 0.f, 0.f, 1.f,
    1.f, 0.f, 0.f, 1.f,
    1.f, 0.f, 0.f, 1.f,
    1.f, 0.f, 0.f, 1.f,
    1.f, 0.f, 0.f, 1.f,
    1.f, 0.f, 0.f, 1.f,
    1.f, 0.f, 0.f, 1.f,
};

Enemy::Enemy(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Scene>& scene,
             const glm::vec3& worldPosition) : Fighter(camera,
                                                       scene, colors, worldPosition)
{
    id = std::string("Enemy ") + std::to_string(std::rand());

    health = 3;
}

void Enemy::shoot(const glm::vec3& direction)
{
    Fighter::shoot(direction, ProjectileOrigin::Enemy);
}

void Enemy::tick()
{
    if (const std::shared_ptr player{scene->getPlayer()}; glm::distance(player->getPosition(), getPosition()) <= 30.f)
    {
        const glm::vec3 playerDirection{glm::normalize(player->getPosition() - getPosition())};
        
        setRotation(math::getRotationAngleFromDirectionVec(playerDirection), glm::vec3{0.f, 0.f, 1.f});

        // shooting
        if (player->hasMoved && glfwGetTime() - lastShotTimestamp > shotInterval)
        {
            shoot(playerDirection);
            lastShotTimestamp = glfwGetTime();
        }
    }
    

    // movement
    if (!move(movementDirection))
    {
        const float newDirectionAngle{math::getRotationAngleFromDirectionVec(movementDirection) + 180.f};
        
        movementDirection = glm::vec3(cos(newDirectionAngle), sin(newDirectionAngle), 0.f);

        move(movementDirection);
    }
}
