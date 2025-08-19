#include "Camera.h"

#include "../objects/Player.h"
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

void Camera::move(const CameraMovtDirection direction)
{
    viewChanged = true;
    
    if (direction == CameraMovtDirection::Up)
    {
        viewMatrix = glm::translate(viewMatrix, glm::vec3(0.f, -1.f, 0.f) * Player::playerSpeed * timing::deltaTime);
        return;
    }
    
    if (direction == CameraMovtDirection::Down)
    {
        viewMatrix = glm::translate(viewMatrix, glm::vec3(0.f, 1.f, 0.f) * Player::playerSpeed * timing::deltaTime);
        return;
    }

    if (direction == CameraMovtDirection::Right)
    {
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-1.f, 0.f, 0.f) * Player::playerSpeed * timing::deltaTime);
        return;
    }
    
    if (direction == CameraMovtDirection::Left)
    {
        viewMatrix = glm::translate(viewMatrix, glm::vec3(1.f, 0.f, 0.f) * Player::playerSpeed * timing::deltaTime);
    }
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
