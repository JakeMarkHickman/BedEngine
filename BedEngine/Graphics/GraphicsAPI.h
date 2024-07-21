#pragma once

namespace GraphicsAPI
{
    enum GraphicsAPIFlags
    {
        OpenGL = 1 << 0,
        Vulkan = 1 << 1,
        DirectX = 1 << 2,
        Metal = 1 << 3
    };
} // namespace GraphicsAPI
