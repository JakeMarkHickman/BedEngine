#include "BasicShapes.h"

Quilt::Plane::Plane()
{
    Pillow::Vector4f colour(1.0f, 1.0f, 1.0f, 1.0f);

    Quilt::Vertex v0;
        v0.Position = { -0.5f, -0.5f, 0.0f };
        v0.Normal = { 0.0f, 0.0f, 0.0f };
        v0.Colour = colour;
        v0.TextureCoordinates = { 0.0f,  0.0f };
        v0.TextureID = 0;

    Quilt::Vertex v1;
        v1.Position = { 0.5f, -0.5f, 0.0f };
        v1.Normal = { 0.0f, 0.0f, 0.0f };
        v1.Colour = colour;
        v1.TextureCoordinates = { 1.0f,  0.0f };
        v1.TextureID = 0;

    Quilt::Vertex v2;
        v2.Position = { 0.5f, 0.5f, 0.0f };
        v2.Normal = { 0.0f, 0.0f, 0.0f };
        v2.Colour = colour;
        v2.TextureCoordinates = { 1.0f,  1.0f };
        v2.TextureID = 0;

    Quilt::Vertex v3;
        v3.Position = { -0.5f, 0.5f, 0.0f };
        v3.Normal = { 0.0f, 0.0f, 0.0f };
        v3.Colour = colour;
        v3.TextureCoordinates = { 0.0f,  1.0f };
        v3.TextureID = 0;

    Vertices.insert(Vertices.end(), { v0, v1, v2, v3 });
    Indices.insert(Indices.end(), { 0, 1, 2, 2, 3, 0 });
}