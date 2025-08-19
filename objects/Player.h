#pragma once
#include "Object.h"
#include "../utils/shapes/Cuboid.h"

class Scene;

class Player final : public Object
{
private:
    static shapes::Cuboid shape;
    static std::vector<float> colors;

    std::shared_ptr<Scene> scene;

public:
    static float playerSpeed;

    explicit Player(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Scene>& scene);

    void shoot(const glm::vec3& direction);
};
