#include "Wall.h"
#include "../camera/Camera.h"
#include "../utils/Logging.h"

shapes::Cuboid Wall::shape{
    20.f,
    1.f,
    8.f
};

std::vector<float> Wall::colors{
    0.07f, 0.060f, 0.215f, 1.f,
    0.07f, 0.060f, 0.215f, 1.f,
    0.07f, 0.060f, 0.215f, 1.f,
    0.07f, 0.060f, 0.215f, 1.f,
    0.07f, 0.060f, 0.215f, 1.f,
    0.07f, 0.060f, 0.215f, 1.f,
    0.07f, 0.060f, 0.215f, 1.f,
    0.07f, 0.060f, 0.215f, 1.f,
};

Wall::Wall(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition, const float rotation) : Object(
    camera, worldPosition, shape, colors,
    "./shaders/shader_sources/PlayerVertexShader.glsl",
    "./shaders/shader_sources/PlayerFragmentShader.glsl")
{
    id = std::string("Wall ") + std::to_string(std::rand());

    setRotation(glm::radians(rotation), glm::vec3{0.f, 0.f, 1.f});
}