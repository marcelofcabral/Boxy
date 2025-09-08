#define GLM_ENABLE_EXPERIMENTAL

#include "Player.h"

#include <thread>
#include <glm/gtx/string_cast.hpp>

#include "Projectile.h"
#include "../camera/Camera.h"
#include "../scene/Scene.h"

std::vector<float> Player::colors{
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
};

Player::Player(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Scene>& scene) : Fighter(camera,
    scene, colors, glm::vec3{0.f, 0.f, -2.3f})
{
    id = std::string("Player ") + std::to_string(std::rand());

    health = 8;
}

void Player::shoot(const glm::vec3& direction)
{
    if (health == 0) return;
    
    Fighter::shoot(direction, ProjectileOrigin::Player);
}

void Player::takeDamage()
{
    Fighter::takeDamage();

    if (health == 0)
    {
        camera->isLocked = true;

        std::thread([this]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));

            health = 8;
            
            setPosition(glm::vec3{
                0, 0, 0
            });

            camera->isLocked = false;
            camera->move(shared_from_this());
            syncViewMatrixToCamera();
            
            scene->add(shared_from_this());
            
        }).detach();
    }
}
