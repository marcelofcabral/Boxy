#include "Camera.h"

#include "../objects/Object.h"
// #include "../objects/Player.h"
#include "../utils/Timing.h"

float Camera::rotationSpeed = 25.f;
float Camera::distanceToOrigin = 35.f;

glm::mat4& Camera::getViewMatrix()
{
    return viewMatrix;
}

glm::mat4& Camera::getProjectionMatrix()
{
    return projectionMatrix;
}

glm::vec3& Camera::getCameraPosition()
{
    return cameraPosition;
}

void Camera::move(const std::shared_ptr<Object>& player)
{
    if (isLocked) return;
    
    viewChanged = true;
    
    cameraPosition = player->getPosition() + cameraOffset;
    center = player->getPosition();
    viewMatrix = glm::lookAt(cameraPosition, center, glm::vec3{0.0f, 1.0f, 0.0f});
}

void Camera::rotateAroundOrigin(const CameraRotationType type, const CameraRotationDirection direction)
{
    viewChanged = true;

    if (direction == CameraRotationDirection::Clockwise)
    {
        if (type == CameraRotationType::Pitch)
        {
            worldPitch -= rotationSpeed * timing::deltaTime;
        }
        else
        {
            worldYaw -= rotationSpeed * timing::deltaTime;
        }
    }
    else
    {
        if (type == CameraRotationType::Pitch)
        {
            worldPitch += rotationSpeed * timing::deltaTime;
        }
        else
        {
            worldYaw += rotationSpeed * timing::deltaTime;
        }
    }
    
    cameraPosition = math::sphericalToCartesian(worldYaw, worldPitch) * distanceToOrigin;

    viewMatrix = glm::lookAt(cameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
