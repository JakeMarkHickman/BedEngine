#pragma once

#include <Vector/Vector2.h>
#include <Vector/Vector3.h>
#include <Vector/Vector4.h>

namespace Quilt
{
    struct Vertex2D
    {
        Vertex2D() {};

        Pillow::Vector3f Position;
        Pillow::Vector2f TextureCoordinates;

        bool operator==(const Vertex2D& other) const {
            return Position == other.Position &&
                    TextureCoordinates == other.TextureCoordinates;
        };
    }

    struct Vertex
    {
        Vertex() {};

        Pillow::Vector3f Position;
        Pillow::Vector3f Normal;
        Pillow::Vector4f Colour; //TODO: Change this to Colour 4 when its implmented into Pillow
        Pillow::Vector2f TextureCoordinates;
        float TextureID = 0;

        bool operator==(const Vertex& other) const {
            return Position == other.Position &&
                    Normal == other.Normal &&
                    Colour == other.Colour &&
                    TextureCoordinates == other.TextureCoordinates &&
                    TextureID == other.TextureID;
        };
    };
}