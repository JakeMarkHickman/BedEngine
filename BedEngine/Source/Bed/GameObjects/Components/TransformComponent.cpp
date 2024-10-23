#include "TransformComponent.h"

Bed::Transform::Transform(Bed::Vector3 position, Bed::Vector3 rotation, Bed::Vector3 scale)
{
    m_Position = position;
    m_Rotation = rotation;
    m_Scale = scale;
}