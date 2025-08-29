#include "Fighter.h"

#include "../collision/CollisionManager.h"
#include "../scene/Scene.h"
#include "../utils/Timing.h"

float Fighter::speed = 15.f;

shapes::Cuboid Fighter::shape{
    1.f,
    1.f,
    3.f
};

Fighter::Fighter(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Scene>& scene,
                 const std::vector<float>& colors, const glm::vec3& worldPosition) : Object(camera,
        worldPosition, shape, colors,
        "./shaders/shader_sources/PlayerVertexShader.glsl",
        "./shaders/shader_sources/PlayerFragmentShader.glsl"), scene{scene}, health{5}
{
}

void Fighter::move(const glm::vec3& direction)
{
    const glm::vec3 movementVector = direction * speed * timing::deltaTime;

    // modelMatrix = glm::translate(modelMatrix, movementVector);
    modelMatrix[3] += glm::vec4{movementVector, 0.0f};

    if (!scene->isColliding(shared_from_this()))
    {
        Object::move(movementVector, true);
    }
    else
    {
        modelMatrix[3] -= glm::vec4{movementVector, 0.0f};
    }
}

void Fighter::takeDamage()
{
    --health;

    if (health == 0)
    {
        scene->markForRemoval(shared_from_this());
    }
}

void Fighter::rotate(const float angle, const glm::vec3& axis)
{
    modelMatrix = glm::rotate(modelMatrix, angle, axis);

    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::modelMatrixUniformName, modelMatrix);

    boundingBox.recalculateMinMax();
}

void Fighter::setRotation(const float angle, const glm::vec3& axis)
{
    if (std::abs(angle - this->rotationAngle) <= 0.0001f)
    {
        return;
    }

    glm::vec3 translation = glm::vec3(modelMatrix[3]);

    modelMatrix = glm::mat4{1.f};
    modelMatrix = glm::translate(modelMatrix, translation);
    modelMatrix = glm::rotate(modelMatrix, angle, axis);

    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::modelMatrixUniformName, modelMatrix);

    // boundingBox.updatePositionToMatchOwner();
    boundingBox.recalculateMinMax();

    rotationAngle = angle;
}
