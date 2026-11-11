#include "CollisionCheck.h"

#include <Vector/Vector3.h>

bool Mattress::CollisionChecks::AABBOverlap(const Pillow::Vector3f& bodyPositionA, const Pillow::Vector3f& halfExtentA, const Pillow::Vector3f& bodyPositionB, const Pillow::Vector3f& halfExtentB, Mattress::ContactData& outContact)
{
    Pillow::Vector3f delta = bodyPositionB - bodyPositionA;

    float overlapX = (halfExtentA.x + halfExtentB.x) - std::abs(delta.x);
    float overlapY = (halfExtentA.y + halfExtentB.y) - std::abs(delta.y);
    float overlapZ = (halfExtentA.z + halfExtentB.z) - std::abs(delta.z);

    if(overlapX <= 0.0f || overlapY <= 0.0f || overlapZ <= 0.0f)
        return false;

    if(overlapX < overlapY)
    {
        outContact.Normal = Pillow::Vector3f(delta.x < 0.0f ? -1.0f : 1.0f, 0.0f, 0.0f);
        outContact.Penetration = overlapX;
    }
    else if(overlapY < overlapX)
    {
        outContact.Normal = Pillow::Vector3f( 0.0f, delta.y < 0.0f ? -1.0f : 1.0f, 0.0f);
        outContact.Penetration = overlapY;
    }
    else
    {
        outContact.Normal = Pillow::Vector3f( 0.0f, 0.0f, delta.z < 0.0f ? -1.0f : 1.0f);
        outContact.Penetration = overlapZ;
    }

    return true;
}