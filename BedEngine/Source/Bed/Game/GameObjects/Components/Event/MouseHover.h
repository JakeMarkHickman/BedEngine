#pragma once

namespace Bed
{
    struct MouseHover
    {
        MouseHover(uint64_t hoveredEntity) : HoveredEntity(hoveredEntity) {};

        uint64_t HoveredEntity;

        //TODO: store where it is hovering
    };
}