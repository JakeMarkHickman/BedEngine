#pragma once

#include <vector>
#include "Vertex.h"
#include <Vector/Vector4.h>

namespace Quilt
{
    struct Plane
    {
        Plane();
        Plane(float x, float y);
        Plane(float size);

        std::vector<Quilt::Vertex> Vertices;
        std::vector<unsigned int> Indices;
    };

    struct Circle
    {
        Circle() {};
    };

    struct Triangle
    {
        Triangle() {};
    };

    struct Cube
    {
        Cube() {};
    };

    struct Sphere
    {
        Sphere() {};
    };

    struct Pyramid
    {
        Pyramid() {};
    };
    
}