#include "BoundingBox.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <ostream>
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

BoundingBox::BoundingBox(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition,
                         const glm::mat4* owningObjectModelMatrix)
    : Drawable(camera, worldPosition, shape.getVertices(), colors, shape.getIndices(),
               "./shaders/shader_sources/PlayerVertexShader.glsl",
               "./shaders/shader_sources/PlayerFragmentShader.glsl"),
      owningObjectModelMatrix{owningObjectModelMatrix}, minX{-0.5f}, minY{-0.5f},
      minZ{0.f}, maxX{0.5f}, maxY{0.5f}, maxZ{3.f}
{
    vertices = shape.getVertices();
}

void BoundingBox::render()
{
    /*
    if (shouldRecalculateMinMax)
    {
        recalculateMinMax();
        
        shouldRecalculateMinMax = false;

        // update VBO with new vertex positions
    }

    // switch to wireframe mode
    */
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Drawable::render();

    // switch back to fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void BoundingBox::recalculateMinMax()
{
    if (!owningObjectModelMatrix) return;

    // reset min and max values
    minX = std::numeric_limits<float>::max();
    minY = std::numeric_limits<float>::max();
    minZ = std::numeric_limits<float>::max();
    
    maxX = std::numeric_limits<float>::lowest();
    maxY = std::numeric_limits<float>::lowest();
    maxZ = std::numeric_limits<float>::lowest();
    
    glm::vec3 boxScale, boxTranslation, boxSkew;
    glm::vec4 boxPerspective;
    glm::quat boxRotation;

    glm::decompose(modelMatrix, boxScale, boxRotation, boxTranslation, boxSkew, boxPerspective);

    glm::vec3 ownerScale, ownerTranslation, ownerSkew;
    glm::vec4 ownerPerspective;
    glm::quat ownerRotation;

    glm::decompose(*owningObjectModelMatrix, ownerScale, ownerRotation, ownerTranslation, ownerSkew,
                   ownerPerspective);

    glm::mat4 rotatedModelMatrix = glm::translate(glm::mat4{1.f}, boxTranslation) * glm::toMat4(ownerRotation);

    // use original vertices coordinates since we're applying the full owner's rotation at every calculation
    // (we don't want to accumulate any previous rotation)
    const std::vector<float>& originalVertices = shape.getVertices();
    
    for (size_t i = 0; i < originalVertices.size(); i += 3)
    {
        glm::vec4 vertexPositions{originalVertices[i], originalVertices[i + 1], originalVertices[i + 2], 1.f};

        glm::vec4 rotatedVertexPositions = rotatedModelMatrix * vertexPositions;

        minX = glm::min(minX, rotatedVertexPositions.x);
        minY = glm::min(minY, rotatedVertexPositions.y);
        minZ = glm::min(minZ, rotatedVertexPositions.z);

        maxX = glm::max(maxX, rotatedVertexPositions.x);
        maxY = glm::max(maxY, rotatedVertexPositions.y);
        maxZ = glm::max(maxZ, rotatedVertexPositions.z);
    }

    vertices = {
        // bottom face
        minX, maxY, minZ, // 0
        maxX, maxY, minZ, // 1
        minX, minY, minZ, // 2
        maxX, minY, minZ, // 3

        // top face
        minX, maxY, maxZ, // 4
        maxX, maxY, maxZ, // 5
        minX, minY, maxZ, // 6
        maxX, minY, maxZ, // 7
    };
    
    std::vector<float> verticesAndColors{vertices};
    verticesAndColors.insert(verticesAndColors.end(), colors.begin(), colors.end());

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesAndColors.size() * sizeof(float), verticesAndColors.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BoundingBox::updatePositionToMatchOwner()
{
    if (!owningObjectModelMatrix) return;

    modelMatrix[3] = (*owningObjectModelMatrix)[3];

    shaderProgram.use();

    shaderProgram.setUniformMat4f(ShaderProgram::modelMatrixUniformName, modelMatrix);
}
