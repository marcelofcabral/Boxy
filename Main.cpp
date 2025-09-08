#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "objects/Enemy.h"
#include "objects/Floor.h"
#include "objects/Object.h"
#include "objects/Obstacle.h"
#include "objects/Player.h"
#include "objects/Projectile.h"
#include "objects/Wall.h"
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

    const auto mainScenePtr{
        std::make_shared<Scene>(cameraPtr)
    };

    const auto playerPtr{std::make_shared<Player>(cameraPtr, mainScenePtr)};
    
    const auto playerObjectPtr{
        std::static_pointer_cast<Object>(playerPtr)
    };

    mainScenePtr->setPlayer(playerObjectPtr);
    /*
    const auto leftWallObjectPtr{
        std::static_pointer_cast<Object>(std::make_shared<Wall>(cameraPtr, glm::vec3{-40.f, 0.f, -2.5f}, 90.f))
    };
    */
    const auto floorObjectPtr{
        std::static_pointer_cast<Object>(std::make_shared<Floor>(cameraPtr, glm::vec3{0.0f, 0.0f, -3.5f}))
    };

    const auto enemyObjectPtr0{
        std::static_pointer_cast<Object>(std::make_shared<Enemy>(cameraPtr, mainScenePtr, glm::vec3{15.f, 15.f, -2.3f}))
    };

    const auto enemyObjectPtr1{
        std::static_pointer_cast<Object>(std::make_shared<Enemy>(cameraPtr, mainScenePtr, glm::vec3{-15.f, -15.f, -2.3f}))
    };

    const auto enemyObjectPtr2{
        std::static_pointer_cast<Object>(std::make_shared<Enemy>(cameraPtr, mainScenePtr, glm::vec3{0.f, -20.f, -2.3f}))
    };

    const auto enemyObjectPtr3{
        std::static_pointer_cast<Object>(std::make_shared<Enemy>(cameraPtr, mainScenePtr, glm::vec3{0.f, 20.f, -2.3f}))
    };

    const auto enemyObjectPtr4{
        std::static_pointer_cast<Object>(std::make_shared<Enemy>(cameraPtr, mainScenePtr, glm::vec3{-20.f, 0.f, -2.3f}))
    };

    const auto enemyObjectPtr5{
        std::static_pointer_cast<Object>(std::make_shared<Enemy>(cameraPtr, mainScenePtr, glm::vec3{20.f, 0.f, -2.3f}))
    };






    
    const auto obstacleObjectPtr0{
        std::static_pointer_cast<Object>(std::make_shared<Obstacle>(cameraPtr, glm::vec3{10.f, 10.f, -2.5f}))
    };

    const auto obstacleObjectPtr1{
        std::static_pointer_cast<Object>(std::make_shared<Obstacle>(cameraPtr, glm::vec3{-10.f, -10.f, -2.5f}))
    };

    const auto obstacleObjectPtr2{
        std::static_pointer_cast<Object>(std::make_shared<Obstacle>(cameraPtr, glm::vec3{10.f, -10.f, -2.5f}))
    };

    const auto obstacleObjectPtr3{
        std::static_pointer_cast<Object>(std::make_shared<Obstacle>(cameraPtr, glm::vec3{-10.f, 10.f, -2.5f}))
    };

    const auto obstacleObjectPtr4{
        std::static_pointer_cast<Object>(std::make_shared<Obstacle>(cameraPtr, glm::vec3{30.f, 0.f, -2.5f}))
    };

    const auto obstacleObjectPtr5{
        std::static_pointer_cast<Object>(std::make_shared<Obstacle>(cameraPtr, glm::vec3{-30.f, 0.f, -2.5f}))
    };

    const auto obstacleObjectPtr6{
        std::static_pointer_cast<Object>(std::make_shared<Obstacle>(cameraPtr, glm::vec3{30.f, 25.f, -2.5f})) 
    };

    const auto obstacleObjectPtr7{
        std::static_pointer_cast<Object>(std::make_shared<Obstacle>(cameraPtr, glm::vec3{-30.f, 25.f, -2.5f})) 
    };

    const auto obstacleObjectPtr8{
        std::static_pointer_cast<Object>(std::make_shared<Obstacle>(cameraPtr, glm::vec3{30.f, -25.f, -2.5f})) 
    };

    const auto obstacleObjectPtr9{
        std::static_pointer_cast<Object>(std::make_shared<Obstacle>(cameraPtr, glm::vec3{-30.f, -25.f, -2.5f})) 
    };

    const auto obstacleObjectPtr10{
        std::static_pointer_cast<Object>(std::make_shared<Obstacle>(cameraPtr, glm::vec3{10.f, 35.f, -2.5f})) 
    };

    const auto obstacleObjectPtr11{
        std::static_pointer_cast<Object>(std::make_shared<Obstacle>(cameraPtr, glm::vec3{10.f, -35.f, -2.5f})) 
    };
    
    const auto obstacleObjectPtr12{
        std::static_pointer_cast<Object>(std::make_shared<Obstacle>(cameraPtr, glm::vec3{-10.f, 35.f, -2.5f})) 
    };

    const auto obstacleObjectPtr13{
        std::static_pointer_cast<Object>(std::make_shared<Obstacle>(cameraPtr, glm::vec3{-10.f, -35.f, -2.5f})) 
    };

    mainScenePtr->add(playerObjectPtr);
    mainScenePtr->add(floorObjectPtr);
    mainScenePtr->add(enemyObjectPtr0);
    mainScenePtr->add(enemyObjectPtr1);
    mainScenePtr->add(enemyObjectPtr2);
    mainScenePtr->add(enemyObjectPtr3);
    mainScenePtr->add(enemyObjectPtr4);
    mainScenePtr->add(enemyObjectPtr5);
    mainScenePtr->add(obstacleObjectPtr0);
    mainScenePtr->add(obstacleObjectPtr1);
    mainScenePtr->add(obstacleObjectPtr2);
    mainScenePtr->add(obstacleObjectPtr3);
    mainScenePtr->add(obstacleObjectPtr4);
    mainScenePtr->add(obstacleObjectPtr5);
    mainScenePtr->add(obstacleObjectPtr6);
    mainScenePtr->add(obstacleObjectPtr7);
    mainScenePtr->add(obstacleObjectPtr8);
    mainScenePtr->add(obstacleObjectPtr9);
    mainScenePtr->add(obstacleObjectPtr10);
    mainScenePtr->add(obstacleObjectPtr11);
    mainScenePtr->add(obstacleObjectPtr12);
    mainScenePtr->add(obstacleObjectPtr13);
    
    // mainScenePtr->add(leftWallObjectPtr);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainScenePtr->tick();
        mainScenePtr->render();

        const char* ptr = nullptr;
        const int errors{glfwGetError(&ptr)};

        if (errors != GLFW_NO_ERROR && ptr)
        {
            std::cout << "GLFW error: " << errors << " " << ptr << '\n';
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        processKeyboardInput(window, cameraPtr, mainScenePtr);

        mainScenePtr->syncSceneToCamera();

        glm::vec3 directionVec{glm::normalize(glm::vec3(mouse::convertXToNdc(), mouse::convertYToNdc(), 0.f))};

        if (mouse::getLmbClicked())
        {
            playerPtr->shoot(directionVec);
        }

        float angle{math::getRotationAngleFromDirectionVec(directionVec)};

        playerPtr->setRotation(angle, glm::vec3{0.0f, 0.0f, 1.0f});

        timing::currentFrame = static_cast<float>(glfwGetTime());

        timing::deltaTime = timing::currentFrame - timing::lastFrame;
        timing::lastFrame = timing::currentFrame;
    }

    glfwTerminate();
    return 0;
}
