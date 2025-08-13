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

        // atan2 handles quadrants automatically
        /*
        if (directionVec.x > 0.f && directionVec.y > 0.f)
        {
            angle = glm::asin(directionVec.y);
        }
        else if (directionVec.x < 0.f && directionVec.y > 0.f)
        {
            angle = glm::acos(directionVec.x);
        }
        else if (directionVec.x < 0.f && directionVec.y < 0.f)
        {
            angle = glm::pi<float>() + glm::asin(-directionVec.y);
        }
        else if (directionVec.x > 0.f && directionVec.y < 0.f)
        {
            angle = 2 * glm::pi<float>() + glm::asin(directionVec.y);
        }
        */

        return angle;
    }
}
