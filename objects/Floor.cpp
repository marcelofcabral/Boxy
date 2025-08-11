#include "Floor.h"
#include "../camera/Camera.h"

shapes::Cuboid Floor::shape{
    30.f,
    30.f,
    1.f
};

std::vector<float> Floor::colors{
    0.5f, 0.5f, 0.5f, 1.f,
    0.5f, 0.5f, 0.5f, 1.f,
    0.5f, 0.5f, 0.5f, 1.f,
    0.5f, 0.5f, 0.5f, 1.f,
    0.5f, 0.5f, 0.5f, 1.f,
    0.5f, 0.5f, 0.5f, 1.f,
    0.5f, 0.5f, 0.5f, 1.f,
    0.5f, 0.5f, 0.5f, 1.f,
};

Floor::Floor(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition) : Object(
    camera, worldPosition, shape.getVertices(), colors, shape.getIndices(),
    "./shaders/shader_sources/PlayerVertexShader.glsl",
    "./shaders/shader_sources/PlayerFragmentShader.glsl")
{
}
