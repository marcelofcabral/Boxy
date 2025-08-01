#pragma once

#include <GLFW/glfw3.h>
#include "./Timing.h"
#include "Mouse.h"

namespace
{
    float playerSpeed = 10.f;
}

inline void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

inline void mouseCallback(GLFWwindow* window, double x_pos, double y_pos)
{
    mouse::x = static_cast<float>(x_pos);
    mouse::y = static_cast<float>(y_pos);
}

inline void scrollCallback(GLFWwindow* window, double x_offset, double y_offset)
{
    
}

inline void processKeyboardInput(GLFWwindow* window, const std::shared_ptr<Object>& player, glm::mat4& viewMatrix)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        // player->move(glm::vec3(0.f, 1.f, 0.f) * playerSpeed);
        viewMatrix = glm::translate(viewMatrix, glm::vec3(0.f, -1.f, 0.f) * playerSpeed * timing::deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        // player->move(glm::vec3(0.f, -1.f, 0.f) * playerSpeed);
        viewMatrix = glm::translate(viewMatrix, glm::vec3(0.f, 1.f, 0.f) * playerSpeed * timing::deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        // player->move(glm::vec3(-1.f, 0.f, 0.f) * playerSpeed);
        viewMatrix = glm::translate(viewMatrix, glm::vec3(1.f, 0.f, 0.f) * playerSpeed * timing::deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        // player->move(glm::vec3(1.f, 0.f, 0.f) * playerSpeed);
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-1.f, 0.f, 0.f) * playerSpeed * timing::deltaTime);
    }
        
}