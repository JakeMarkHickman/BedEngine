#pragma once

namespace Bed
{
    struct Child
    {
        Child(uint64_t parent) : Parent(parent) {};

        uint64_t Parent;
    };
}