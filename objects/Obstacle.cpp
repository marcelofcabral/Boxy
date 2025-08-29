#include "Obstacle.h"
#include "../camera/Camera.h"

shapes::Cuboid Obstacle::shape{
    5.f,
    5.f,
    8.f
};

std::vector<float> Obstacle::colors{
    0.07f, 0.060f, 0.215f, 1.f,
    0.07f, 0.060f, 0.215f, 1.f,
    0.07f, 0.060f, 0.215f, 1.f,
    0.07f, 0.060f, 0.215f, 1.f,
    0.07f, 0.060f, 0.215f, 1.f,
    0.07f, 0.060f, 0.215f, 1.f,
    0.07f, 0.060f, 0.215f, 1.f,
    0.07f, 0.060f, 0.215f, 1.f,
};

Obstacle::Obstacle(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition) : Object(
    camera, worldPosition, shape, colors,
    "./shaders/shader_sources/PlayerVertexShader.glsl",
    "./shaders/shader_sources/PlayerFragmentShader.glsl")
{
    id = std::string("Obstacle ") + std::to_string(std::rand());
}