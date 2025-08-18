#pragma once
#include <glm/gtc/matrix_transform.hpp>

#include "../utils/Dimensions.h"
#include "../utils/Math.h"

enum class CameraMovtDirection : uint8_t
{
    Up,
    Down,
    Left,
    Right
};

enum class CameraRotationType : uint8_t
{
    Pitch,
    Yaw,
};

enum class CameraRotationDirection : uint8_t
{
    Clockwise,
    CounterClockwise,
};

class Camera
{
private:
    static float rotationSpeed;
    static float distanceToOrigin;

    float worldPitch = -45.f, worldYaw = 90.f;
    
    // glm::vec3 cameraPosition{0.f, -10.f, 18.f};
    // conversion from spherical to cartesian coordinates
    glm::vec3 cameraPosition{
        math::sphericalToCartesian(worldYaw, worldPitch) * distanceToOrigin,
    };
    
    glm::mat4 projectionMatrix{
        glm::perspective(glm::radians(45.0f),
                         static_cast<float>(Dimensions::WindowWidth) / static_cast<float>(Dimensions::WindowHeight),
                         0.1f, 100.0f)
    };

    glm::mat4 viewMatrix{
        glm::lookAt(cameraPosition, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f))
    };

    bool viewChanged{false};

public:
    glm::mat4& getViewMatrix();
    glm::mat4& getProjectionMatrix();
    glm::vec3& getCameraPosition();
    
    void move(CameraMovtDirection direction);
    void rotateAroundOrigin(CameraRotationType type, CameraRotationDirection direction);
    
    [[nodiscard]] bool getViewChanged() const { return viewChanged; }
    void setViewChanged(const bool newState) { viewChanged = newState; }
};
