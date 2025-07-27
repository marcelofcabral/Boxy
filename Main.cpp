#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "objects/Object.h"
#include "scene/Scene.h"
#include "utils/Dimensions.h"
#include "utils/InputCallbacks.h"
#include "utils/timing.h"
#include "utils/shapes/Cuboid.h"
#include "utils/shapes/Plane.h"

int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(static_cast<int>(Dimensions::WindowWidth),
                                          static_cast<int>(Dimensions::WindowHeight), "Boxy", nullptr, nullptr);

    if (!window)
    {
        std::cout << "Failed to create GLFW window" << '\n';
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << '\n';
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, static_cast<int>(Dimensions::WindowWidth), static_cast<int>(Dimensions::WindowHeight));

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    shapes::Cuboid cuboid{1.f, 1.f, 5.f};

    std::vector colors{
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
    };

    const auto cuboidObjectPtr{
        std::make_shared<Object>(
            cuboid.getVertices(), colors, cuboid.getIndices(), "./shaders/shader_sources/PlayerVertexShader.glsl",
            "./shaders/shader_sources/PlayerFragmentShader.glsl"
        )
    };

    Scene mainScene;
    mainScene.addRenderable(cuboidObjectPtr);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::mat4 modelMatrix{1.f};
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
        
        glm::mat4 projectionMatrix{
            glm::perspective(glm::radians(45.0f),
                             static_cast<float>(Dimensions::WindowWidth) / static_cast<float>(Dimensions::WindowHeight),
                             0.1f, 100.0f)
        };


        glm::mat4 viewMatrix{
            glm::lookAt(glm::vec3(0.f, -8.f, 20.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f))
        };

        cuboidObjectPtr->updateModelMatrix(modelMatrix);
        cuboidObjectPtr->updateProjectionMatrix(projectionMatrix);
        cuboidObjectPtr->updateViewMatrix(viewMatrix);

        mainScene.render();

        const char* ptr = nullptr;
        const int errors{glfwGetError(&ptr)};

        if (errors != GLFW_NO_ERROR && ptr)
        {
            std::cout << "GLFW error: " << errors << " " << ptr << '\n';
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        processKeyboardInput(window);

        timing::currentFrame = static_cast<float>(glfwGetTime());

        timing::deltaTime = timing::currentFrame - timing::lastFrame;
        timing::lastFrame = timing::currentFrame;
    }

    glfwTerminate();
    return 0;
}
