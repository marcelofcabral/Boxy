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
        // modelMatrix = glm::translate(modelMatrix, direction);

    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::modelMatrixUniformName, modelMatrix);

    boundingBox.updatePositionToMatchOwner();
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
