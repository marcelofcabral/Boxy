#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "objects/Floor.h"
#include "objects/Object.h"
#include "objects/Player.h"
#include "objects/Projectile.h"
#include "scene/Scene.h"
#include "utils/Dimensions.h"
#include "utils/InputCallbacks.h"
#include "utils/Math.h"
#include "utils/timing.h"

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

    const auto cameraPtr{
        std::make_shared<Camera>()
    };
    
    const auto playerObjectPtr{
        std::static_pointer_cast<Object>(std::make_shared<Player>(cameraPtr))
    };
    
    const auto floorObjectPtr{
        std::static_pointer_cast<Object>(std::make_shared<Floor>(cameraPtr, glm::vec3{0.0f, 0.0f, -3.5f}))
    };
    
    Scene mainScene{cameraPtr, playerObjectPtr};
    
    mainScene.add(floorObjectPtr);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainScene.tick();
        mainScene.render();

        const char* ptr = nullptr;
        const int errors{glfwGetError(&ptr)};

        if (errors != GLFW_NO_ERROR && ptr)
        {
            std::cout << "GLFW error: " << errors << " " << ptr << '\n';
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        processKeyboardInput(window, cameraPtr);

        mainScene.syncSceneToCamera();
        
        glm::vec3 directionVec{glm::normalize(glm::vec3(mouse::convertXToNdc(), mouse::convertYToNdc(), 0.f))};

        if (mouse::getLmbClicked())
        {
            std::cout << "lmb clicked" << '\n';
            const auto projectilePtr{
                std::static_pointer_cast<Object>(std::make_shared<Projectile>(cameraPtr, directionVec))
            };
            
            mainScene.add(projectilePtr);
        }
        
        float angle{math::getRotationAngleFromDirectionVec(directionVec)};

        playerObjectPtr->setRotation(angle, glm::vec3{0.0f, 0.0f, 1.0f});

        timing::currentFrame = static_cast<float>(glfwGetTime());

        timing::deltaTime = timing::currentFrame - timing::lastFrame;
        timing::lastFrame = timing::currentFrame;
    }

    glfwTerminate();
    return 0;
}
