#pragma once

#include <vector>

namespace Bed
{
    struct CollisionStay
    {
        CollisionStay(std::vector<uint64_t> otherEntity) : collidedEntity(otherEntity) {};

        std::vector<uint64_t> collidedEntity;
    };
}