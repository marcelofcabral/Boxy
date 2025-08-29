#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Mouse.h"
#include "../camera/Camera.h"
#include "../collision/CollisionManager.h"
#include "../scene/Scene.h"

namespace
{
    double lastCollisionToggle = 0.f;
}

inline void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

inline void mouseMovementCallback(GLFWwindow* window, double x_pos, double y_pos)
{
    mouse::x = static_cast<float>(x_pos);
    mouse::y = static_cast<float>(y_pos);
}

inline void mouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        mouse::setLmbClicked(true);
    }
}

inline void scrollCallback(GLFWwindow* window, double x_offset, double y_offset)
{
}

inline void processKeyboardInput(GLFWwindow* window, const std::shared_ptr<Camera>& camera,
                                 const std::shared_ptr<Scene>& scene)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }

    const std::shared_ptr player{std::static_pointer_cast<Fighter>(scene->getPlayer())};

    if (!scene->isColliding(player))
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            player->move(glm::vec3{0.f, 1.f, 0.f});
            camera->move(player);
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            player->move(glm::vec3{0.f, -1.f, 0.f});
            camera->move(player);
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            player->move(glm::vec3{-1.f, 0.f, 0.f});
            camera->move(player);
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            player->move(glm::vec3{1.f, 0.f, 0.f});
            camera->move(player);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
    {
        camera->rotateAroundOrigin(CameraRotationType::Yaw, CameraRotationDirection::Clockwise);
    }

    if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
    {
        camera->rotateAroundOrigin(CameraRotationType::Yaw, CameraRotationDirection::CounterClockwise);
    }

    if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
    {
        camera->rotateAroundOrigin(CameraRotationType::Pitch, CameraRotationDirection::Clockwise);
    }

    if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
    {
        camera->rotateAroundOrigin(CameraRotationType::Pitch, CameraRotationDirection::CounterClockwise);
    }

    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
    {
        if (glfwGetTime() - lastCollisionToggle > 0.1f)
        {
            scene->toggleRenderCollisionBoxes();
            lastCollisionToggle = glfwGetTime();
        }
    }
}
