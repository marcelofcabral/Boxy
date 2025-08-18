#pragma once
#include <string>
#include <vector>
#include <memory>

#include "../collision/BoundingBox.h"
#include "../rendering/Drawable.h"

class Camera;

class Object : public Drawable
{
protected:
    BoundingBox boundingBox;

public:
    explicit Object(const std::shared_ptr<Camera>& camera, const glm::vec3& worldPosition,
                    const std::vector<float>& vertices, const std::vector<float>& colors,
                    const std::vector<unsigned int>& indices,
                    const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

    ~Object() override = default;

    void render() override;

    void syncViewMatrixToCamera() override;
    
    bool shouldTick = true;

    void move(const glm::vec3& direction);
    void rotate(float angle, const glm::vec3& axis);
    void setRotation(float angle, const glm::vec3& axis);
    
    glm::vec3 getPosition();
    void printPosition();
};
