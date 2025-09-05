#pragma once
#include <random>
#include <glm/vec3.hpp>
#include <glm/ext/scalar_constants.hpp>

namespace math
{
    inline float getRotationAngleFromDirectionVec(const glm::vec3& directionVec)
    {
        float angle{std::atan2(directionVec.y, directionVec.x)};

        if (angle < 0.f)
            angle += 2.f * glm::pi<float>();

        return angle;
    }

    inline glm::vec3 sphericalToCartesian(const float yaw, const float pitch)
    {
        return glm::vec3{
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        };
    }

    inline glm::vec3 getRandomUnitVectorOnXYPlane()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

        const float randomSin{dist(gen)};
        const float correspondingCos{sqrt(1 - pow(randomSin, 2.f))};

        return {correspondingCos, randomSin, 0.f};
    }
}
