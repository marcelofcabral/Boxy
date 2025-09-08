#pragma once
#include <memory>

#include "../scene/Scene.h"
#include "../objects/Enemy.h"
#include "../camera/Camera.h"

inline void setupEnemies(const std::shared_ptr<Scene>& mainScenePtr, const std::shared_ptr<Camera>& cameraPtr)
{
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

    const auto enemyObjectPtr6{
        std::static_pointer_cast<Object>(std::make_shared<Enemy>(cameraPtr, mainScenePtr, glm::vec3{25.f, 13.f, -2.3f}))
    };

    const auto enemyObjectPtr7{
        std::static_pointer_cast<Object>(std::make_shared<Enemy>(cameraPtr, mainScenePtr, glm::vec3{-25.f, 13.f, -2.3f}))
    };

    const auto enemyObjectPtr8{
        std::static_pointer_cast<Object>(std::make_shared<Enemy>(cameraPtr, mainScenePtr, glm::vec3{25.f, -13.f, -2.3f}))
    };

    const auto enemyObjectPtr9{
        std::static_pointer_cast<Object>(std::make_shared<Enemy>(cameraPtr, mainScenePtr, glm::vec3{-25.f, -13.f, -2.3f}))
    };

    mainScenePtr->add(enemyObjectPtr0);
    mainScenePtr->add(enemyObjectPtr1);
    mainScenePtr->add(enemyObjectPtr2);
    mainScenePtr->add(enemyObjectPtr3);
    mainScenePtr->add(enemyObjectPtr4);
    mainScenePtr->add(enemyObjectPtr5);
    mainScenePtr->add(enemyObjectPtr6);
    mainScenePtr->add(enemyObjectPtr7);
    mainScenePtr->add(enemyObjectPtr8);
    mainScenePtr->add(enemyObjectPtr9);
}

inline void setupObstacles(const std::shared_ptr<Scene>& mainScenePtr, const std::shared_ptr<Camera>& cameraPtr)
{
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
}