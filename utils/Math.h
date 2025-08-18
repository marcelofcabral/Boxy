#pragma once
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
}
