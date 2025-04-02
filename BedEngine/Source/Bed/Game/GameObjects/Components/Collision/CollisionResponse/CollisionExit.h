#pragma once

#include <vector>

namespace Bed
{
    struct CollisionExit
    {
        CollisionExit(std::vector<uint64_t> otherEntity) : collidedEntity(otherEntity) {};

        std::vector<uint64_t> collidedEntity;
    };
}