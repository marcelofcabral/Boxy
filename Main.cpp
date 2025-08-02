#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "objects/Object.h"
#include "scene/Scene.h"
#include "utils/Dimensions.h"
#include "utils/InputCallbacks.h"
#include "utils/Math.h"
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
    glfwSetCursorPosCallback(window, mouseMovementCallback);
    glfwSetMouseButtonCallback(window, mouseClickCallback);
    glfwSetScrollCallback(window, scrollCallback);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

    shapes::Cuboid player{1.f, 1.f, 3.f};
    shapes::Cuboid floor{15.f, 15.f, 1.f};
    // shapes::Cuboid debugCube{3.f, 0.25f, 0.25f};

    std::vector floorColors{
        0.5f, 0.5f, 0.5f, 1.f,
        0.5f, 0.5f, 0.5f, 1.f,
        0.5f, 0.5f, 0.5f, 1.f,
        0.5f, 0.5f, 0.5f, 1.f,
        0.5f, 0.5f, 0.5f, 1.f,
        0.5f, 0.5f, 0.5f, 1.f,
        0.5f, 0.5f, 0.5f, 1.f,
        0.5f, 0.5f, 0.5f, 1.f,
    };

    std::vector playerColors{
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
    };
    /*
    std::vector debugCubeColors{
        0.f, 0.f, 1.f, 1.f,
        0.f, 0.f, 1.f, 1.f,
        0.f, 0.f, 1.f, 1.f,
        0.f, 0.f, 1.f, 1.f,
        0.f, 0.f, 1.f, 1.f,
        0.f, 0.f, 1.f, 1.f,
        0.f, 0.f, 1.f, 1.f,
        0.f, 0.f, 1.f, 1.f,
    };
    */
    const auto playerObjectPtr{
        std::make_shared<Object>(
            player.getVertices(), playerColors, player.getIndices(), "./shaders/shader_sources/PlayerVertexShader.glsl",
            "./shaders/shader_sources/PlayerFragmentShader.glsl"
        )
    };

    const auto floorObjectPtr{
        std::make_shared<Object>(
            floor.getVertices(), floorColors, floor.getIndices(), "./shaders/shader_sources/PlayerVertexShader.glsl",
            "./shaders/shader_sources/PlayerFragmentShader.glsl"
        )
    };
    /*
    const auto debugCubeObjectPtr{
        std::make_shared<Object>(
            debugCube.getVertices(), debugCubeColors, debugCube.getIndices(),
            "./shaders/shader_sources/PlayerVertexShader.glsl",
            "./shaders/shader_sources/PlayerFragmentShader.glsl"
        )
    };
    */
    glm::mat4 initialModelMatrix{1.f};
    /*
    glm::vec3 debugCubePosition{2.f, 0.f, 0.f};
    float distanceFromOrigin{glm::distance(debugCubePosition, glm::vec3(0.f, 0.f, 0.f))};
    */
    glm::mat4 initialPlayerModelMatrix = glm::translate(initialModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    // glm::mat4 initialDebugCubeModelMatrix = glm::translate(initialModelMatrix, debugCubePosition);
    glm::mat4 initialFloorModelMatrix = glm::translate(initialModelMatrix, glm::vec3(0.0f, 0.0f, -3.5f));

    glm::mat4 projectionMatrix{
        glm::perspective(glm::radians(45.0f),
                         static_cast<float>(Dimensions::WindowWidth) / static_cast<float>(Dimensions::WindowHeight),
                         0.1f, 100.0f)
    };


    glm::mat4 viewMatrix{
        glm::lookAt(glm::vec3(0.f, -8.f, 18.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f))
    };

    playerObjectPtr->updateModelMatrix(initialPlayerModelMatrix);
    playerObjectPtr->updateProjectionMatrix(projectionMatrix);
    playerObjectPtr->updateViewMatrix(viewMatrix);

    floorObjectPtr->updateModelMatrix(initialFloorModelMatrix);
    floorObjectPtr->updateProjectionMatrix(projectionMatrix);
    floorObjectPtr->updateViewMatrix(viewMatrix);

    // debugCubeObjectPtr->updateModelMatrix(initialDebugCubeModelMatrix);
    // debugCubeObjectPtr->updateProjectionMatrix(projectionMatrix);
    // debugCubeObjectPtr->updateViewMatrix(viewMatrix);

    Scene mainScene;
    mainScene.add(playerObjectPtr);
    mainScene.add(floorObjectPtr);
    // mainScene.add(debugCubeObjectPtr);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainScene.render();

        const char* ptr = nullptr;
        const int errors{glfwGetError(&ptr)};

        if (errors != GLFW_NO_ERROR && ptr)
        {
            std::cout << "GLFW error: " << errors << " " << ptr << '\n';
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (mouse::getLmbClicked())
        {
            std::cout << "lmb clicked" << '\n';
        }
        
        processKeyboardInput(window, playerObjectPtr, viewMatrix);

        std::set except{playerObjectPtr/*, debugCubeObjectPtr*/};

        mainScene.updateViewMatrix(viewMatrix, except);

        glm::vec3 directionVec{glm::normalize(glm::vec3(mouse::convertXToNdc(), mouse::convertYToNdc(), 0.f))};

        float angle{math::getRotationAngleFromDirectionVec(directionVec)};
        
        playerObjectPtr->setRotation(angle, glm::vec3{0.0f, 0.0f, 1.0f});
    /*
        // Create the model matrix for the debug cube
        glm::mat4 debugObjectModelMatrix = glm::mat4(1.0f);

        // Rotate it on the origin: this "switches" the matrix to local space
        debugObjectModelMatrix = glm::rotate(debugObjectModelMatrix, angle, glm::vec3(0.0f, 0.0f, 1.0f));

        // Translate it forward, since the x-axis here is the local space's x-axis
        debugObjectModelMatrix = glm::translate(debugObjectModelMatrix, glm::vec3(distanceFromOrigin, 0.0f, 0.0f));

        // Update the debug cube's model matrix
        debugCubeObjectPtr->updateModelMatrix(debugObjectModelMatrix);
        */
        timing::currentFrame = static_cast<float>(glfwGetTime());

        timing::deltaTime = timing::currentFrame - timing::lastFrame;
        timing::lastFrame = timing::currentFrame;
    }

    glfwTerminate();
    return 0;
}
