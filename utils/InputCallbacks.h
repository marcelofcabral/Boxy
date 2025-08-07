#pragma once

#include <GLFW/glfw3.h>
#include "./Timing.h"
#include "Mouse.h"
#include "../camera/Camera.h"

namespace
{
    float playerSpeed = 10.f;
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

inline void processKeyboardInput(GLFWwindow* window, const std::shared_ptr<Camera>& camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera->move(CameraMovtDirection::Up);
    }
    
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera->move(CameraMovtDirection::Down);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera->move(CameraMovtDirection::Left);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera->move(CameraMovtDirection::Right);
    }
        
}