#include "Enemy.h"

#include <random>

#include "../camera/Camera.h"
#include "../scene/Scene.h"

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
}

void Enemy::shoot(const glm::vec3& direction)
{
    
}
