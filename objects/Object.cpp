#include "Object.h"

#include <vector>
#include <iostream>
#include <glm/ext/matrix_transform.hpp>

#include "../camera/Camera.h"

Object::Object(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition, shapes::Cuboid& shape,
               const std::vector<float>& colors, const std::string& vertexShaderSource,
               const std::string& fragmentShaderSource)
    : Drawable(camera, worldPosition, shape.getVertices(), colors, shape.getIndices(), vertexShaderSource,
               fragmentShaderSource),
      boundingBox{camera, worldPosition, &modelMatrix, shape}
{
}

void Object::render()
{
    Drawable::render();
    
    if (shouldRenderBoundingBox)
        boundingBox.render();
}

void Object::move(const glm::vec3& movementVector, const bool isFighter)
{
    if (!isFighter)
        modelMatrix[3] += glm::vec4{movementVector, 0.0f};

    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::modelMatrixUniformName, modelMatrix);

    boundingBox.updatePositionToMatchOwner();
}

void Object::setPosition(const glm::vec3& position)
{
    modelMatrix[3] = glm::vec4{position, 1.0f};

    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::modelMatrixUniformName, modelMatrix);

    boundingBox.updatePositionToMatchOwner();
}

void Object::rotate(const float angle, const glm::vec3& axis)
{
    modelMatrix = glm::rotate(modelMatrix, angle, axis);

    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::modelMatrixUniformName, modelMatrix);

    boundingBox.recalculateMinMax();
}

void Object::setRotation(const float angle, const glm::vec3& axis)
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

void Object::syncViewMatrixToCamera()
{
    Drawable::syncViewMatrixToCamera();
    boundingBox.syncViewMatrixToCamera();
}

glm::vec3 Object::getPosition()
{
    return modelMatrix[3];
}

void Object::printPosition()
{
    std::cout << "Position: " << modelMatrix[3].x << " " << modelMatrix[3].y << " " << modelMatrix[3].z << '\n';
}

BoundingBox& Object::getBoundingBox()
{
    return boundingBox;
}
