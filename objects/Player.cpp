#include "Player.h"

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

Player::Player(const std::shared_ptr<Camera>& camera) : Object(camera, glm::vec3{0.f}, shape.getVertices(), colors,
                                                               shape.getIndices(),
                                                               "./shaders/shader_sources/PlayerVertexShader.glsl",
                                                               "./shaders/shader_sources/PlayerFragmentShader.glsl")
{
}
