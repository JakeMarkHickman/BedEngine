#pragma once

namespace GraphicsAPI
{
    enum EGraphicsAPIFlags
    {
        OpenGL = 1 << 0,
        Vulkan = 1 << 1,
        DirectX = 1 << 2,
        Metal = 1 << 3
    };

    struct SGraphicAPIFlags
    {
        uint8_t m_AvailableFlags = 0;

        void SetFlag(EGraphicsAPIFlags Flag)
        {
            m_AvailableFlags |= (int)Flag;
        }

        bool HasFlag(EGraphicsAPIFlags Flag)
        {
            return (m_AvailableFlags & (int)Flag) == (int)Flag;
        }
    };
} // namespace GraphicsAPI
