#include "BoundingBox.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

// initial values
shapes::Cuboid BoundingBox::shape{
    1.f,
    1.f,
    3.f
};

std::vector<float> BoundingBox::colors{
    0.627f, 0.125f, 0.941f, 1.f,
    0.627f, 0.125f, 0.941f, 1.f,
    0.627f, 0.125f, 0.941f, 1.f,
    0.627f, 0.125f, 0.941f, 1.f,
    0.627f, 0.125f, 0.941f, 1.f,
    0.627f, 0.125f, 0.941f, 1.f,
    0.627f, 0.125f, 0.941f, 1.f,
    0.627f, 0.125f, 0.941f, 1.f,
};


BoundingBox::BoundingBox(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition)
    : Object(camera, worldPosition, shape.getVertices(), colors, shape.getIndices(),
             "./shaders/shader_sources/PlayerVertexShader.glsl",
             "./shaders/shader_sources/PlayerFragmentShader.glsl"),
      minX{-0.5f}, minY{-0.5f}, minZ{0.f},
      maxX{0.5f}, maxY{0.5f}, maxZ{3.f}
{
    vertices = shape.getVertices();
}

void BoundingBox::render()
{
    if (shouldRecalculateMinMax)
    {
        recalculateMinMax();
        
        shouldRecalculateMinMax = false;

        // update VBO with new vertex positions
    }

    // switch to wireframe mode
    
    Object::render();

    // switch back to fill mode
}

void BoundingBox::recalculateMinMax()
{
    if (!owningObjectModelMatrix) return;

    glm::vec3 targetScale, targetTranslation, targetSkew;
    glm::vec4 targetPerspective;
    glm::quat targetRotation;

    glm::decompose(modelMatrix, targetScale, targetRotation, targetTranslation, targetSkew, targetPerspective);

    glm::vec3 sourceScale, sourceTranslation, sourceSkew;
    glm::vec4 sourcePerspective;
    glm::quat sourceRotation;

    glm::decompose(*owningObjectModelMatrix, sourceScale, sourceRotation, sourceTranslation, sourceSkew, sourcePerspective);

    glm::mat4 rotatedModelMatrix = glm::translate(glm::mat4{1.f}, targetTranslation) * glm::toMat4(sourceRotation) * glm::scale(glm::mat4{1.f}, targetScale);

    // get each vertex pos, create a vec4 with the last row = 1.f and the coordinates of each vertex and multiply
    // by rotatedModelMatrix. Then iterate through this modified vertex array to find mins and maxes and store them
    // in the member variables
}
