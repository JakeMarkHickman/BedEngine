#pragma once

namespace Bed
{
    struct Parent
    {
        Parent(uint64_t parentEntityID, Pillow::Vector3f localOffset = Pillow::Vector3f(0.0f, 0.0f, 0.0f)) : Entity(parentEntityID), LocalOffset(localOffset) {};

        uint64_t Entity;
        Pillow::Vector3f LocalOffset;
    };
}