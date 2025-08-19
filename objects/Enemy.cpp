#include "Enemy.h"

float Enemy::enemySpeed = 15.f;

shapes::Cuboid Enemy::shape{
    1.f,
    1.f,
    3.f
};

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

Enemy::Enemy(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition) : Object(camera, worldPosition, shape, colors,
                                                               "./shaders/shader_sources/PlayerVertexShader.glsl",
                                                               "./shaders/shader_sources/PlayerFragmentShader.glsl")
{
}