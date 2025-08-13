#pragma once

class CollisionManager
{
public:
    static bool checkForBoxCollision();
    // create BoundingBox class
    // store BoundingBox instance, rotation angle around z-axis and world position in Object object and store its minX, maxX, minY, maxY, minZ, maxZ
    // check if rotation or position have changed in relation to the last frame and if so, (can check if model matrix has changed)
    // apply transformation to the BoundingBox
    // obtain new minX, maxX, minY, maxY, minZ, maxZ from transformed BoundingBox and update its vertices accordingly

    // use BoundingBox to perform AABB collision check
};
