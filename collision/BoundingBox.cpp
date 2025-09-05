#include "BoundingBox.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <ostream>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
/*
// initial values
shapes::Cuboid BoundingBox::shape{
    1.f,
    1.f,
    3.f
};
*/
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

BoundingBox::BoundingBox(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition,
                         const glm::mat4* owningObjectModelMatrix, shapes::Cuboid& shape)
    : Drawable(camera, worldPosition, shape.getVertices(), colors, shape.getIndices(),
               "./shaders/shader_sources/PlayerVertexShader.glsl",
               "./shaders/shader_sources/PlayerFragmentShader.glsl"),
      owningObjectModelMatrix{owningObjectModelMatrix},
      minMaxes{-0.5f, -0.5f, 0.f, 0.5f, 0.5f, 3.f}
{
    vertices = shape.getVertices();
    originalVertices = shape.getVertices();
    recalculateMinMax();
}

void BoundingBox::render()
{
    // switch to wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Drawable::render();

    // switch back to fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void BoundingBox::recalculateMinMax()
{
    if (!owningObjectModelMatrix) return;

    // reset min and max values
    minMaxes.minX = std::numeric_limits<float>::max();
    minMaxes.minY = std::numeric_limits<float>::max();
    minMaxes.minZ = std::numeric_limits<float>::max();

    minMaxes.maxX = std::numeric_limits<float>::lowest();
    minMaxes.maxY = std::numeric_limits<float>::lowest();
    minMaxes.maxZ = std::numeric_limits<float>::lowest();

    glm::vec3 ownerScale, ownerTranslation, ownerSkew;
    glm::vec4 ownerPerspective;
    glm::quat ownerRotation;

    glm::decompose(*owningObjectModelMatrix, ownerScale, ownerRotation, ownerTranslation, ownerSkew,
                   ownerPerspective);

    // use original vertices coordinates since we're applying the full owner's rotation at every calculation
    // (we don't want to accumulate any previous rotation)
    for (size_t i = 0; i < originalVertices.size(); i += 3)
    {
        glm::vec4 vertexPositions{originalVertices[i], originalVertices[i + 1], originalVertices[i + 2], 1.f};

        glm::vec4 rotatedVertexPositions = glm::toMat4(ownerRotation) * vertexPositions;

        minMaxes.minX = glm::min(minMaxes.minX, rotatedVertexPositions.x);
        minMaxes.minY = glm::min(minMaxes.minY, rotatedVertexPositions.y);
        minMaxes.minZ = glm::min(minMaxes.minZ, rotatedVertexPositions.z);

        minMaxes.maxX = glm::max(minMaxes.maxX, rotatedVertexPositions.x);
        minMaxes.maxY = glm::max(minMaxes.maxY, rotatedVertexPositions.y);
        minMaxes.maxZ = glm::max(minMaxes.maxZ, rotatedVertexPositions.z);
    }

    vertices = {
        // bottom face
        minMaxes.minX, minMaxes.maxY, minMaxes.minZ, // 0
        minMaxes.maxX, minMaxes.maxY, minMaxes.minZ, // 1
        minMaxes.minX, minMaxes.minY, minMaxes.minZ, // 2
        minMaxes.maxX, minMaxes.minY, minMaxes.minZ, // 3

        // top face
        minMaxes.minX, minMaxes.maxY, minMaxes.maxZ, // 4
        minMaxes.maxX, minMaxes.maxY, minMaxes.maxZ, // 5
        minMaxes.minX, minMaxes.minY, minMaxes.maxZ, // 6
        minMaxes.maxX, minMaxes.minY, minMaxes.maxZ, // 7
    };

    std::vector<float> verticesAndColors{vertices};
    verticesAndColors.insert(verticesAndColors.end(), colors.begin(), colors.end());

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesAndColors.size() * sizeof(float), verticesAndColors.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BoundingBox::updatePositionToMatchOwner()
{
    if (!owningObjectModelMatrix) return;

    modelMatrix[3] = (*owningObjectModelMatrix)[3];

    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::modelMatrixUniformName, modelMatrix);
}
