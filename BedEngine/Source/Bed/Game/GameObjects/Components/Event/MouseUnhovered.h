#pragma once

namespace Bed
{
    struct MouseUnhovered
    {
        MouseUnhovered(uint64_t unhoveredEntity) : UnhoveredEntity(unhoveredEntity) {};

        uint64_t UnhoveredEntity;

        //TODO: store where it is unhovered
    };
}

