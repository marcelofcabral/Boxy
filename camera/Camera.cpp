#include "Camera.h"

#include "../objects/Player.h"
#include "../utils/Timing.h"

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
