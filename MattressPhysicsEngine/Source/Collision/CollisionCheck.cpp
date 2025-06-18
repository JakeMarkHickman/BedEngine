#include "CollisionCheck.h"

bool Mattress::CollisionChecks::AABBOverlap(Mattress::AABB& a, Mattress::AABB& b)
{
    return (a.Min.x <= b.Max.x && a.Max.x >= b.Min.x) && //Check for X axis overlap
           (a.Min.y <= b.Max.y && a.Max.y >= b.Min.y) && //Check for Y axis overlap
           (a.Min.z <= b.Max.z && a.Max.z >= b.Min.z); //Check for Z axis overlap
}