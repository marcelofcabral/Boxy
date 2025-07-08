#pragma once

#include <GLFW/glfw3.h>

inline void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

inline void mouseCallback(GLFWwindow* window, double x_pos, double y_pos)
{
    
}

inline void scrollCallback(GLFWwindow* window, double x_offset, double y_offset)
{
    
}

inline void processKeyboardInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
}