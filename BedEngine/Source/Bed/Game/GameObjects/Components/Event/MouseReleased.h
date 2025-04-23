#pragma once

namespace Bed
{
    struct MouseReleased
    {
        MouseReleased(uint64_t releasedEntity) : ReleasedEntity(releasedEntity) {}

        uint64_t ReleasedEntity;

        //TODO: store where released
        //TODO: store what button was Released e.g RMB LBM MMB
    };
}