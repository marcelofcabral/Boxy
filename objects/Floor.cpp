#include "Floor.h"
#include "../camera/Camera.h"

shapes::Cuboid Floor::shape{
    80.f,
    80.f,
    1.f
};

std::vector<float> Floor::colors{
    0.09f, 0.067f, 0.231f, 1.f,
    0.09f, 0.067f, 0.231f, 1.f,
    0.09f, 0.067f, 0.231f, 1.f,
    0.09f, 0.067f, 0.231f, 1.f,
    0.09f, 0.067f, 0.231f, 1.f,
    0.09f, 0.067f, 0.231f, 1.f,
    0.09f, 0.067f, 0.231f, 1.f,
    0.09f, 0.067f, 0.231f, 1.f,
};

Floor::Floor(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition) : Object(
    camera, worldPosition, shape, colors,
    "./shaders/shader_sources/PlayerVertexShader.glsl",
    "./shaders/shader_sources/PlayerFragmentShader.glsl")
{
    id = std::string("Floor ") + std::to_string(std::rand());
}
