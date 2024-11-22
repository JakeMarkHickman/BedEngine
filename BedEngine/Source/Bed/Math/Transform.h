#pragma once

#include "Vector/Vector3.h"

namespace Bed
{
    struct BED_API Transform
    {
        Transform() {};
        Transform(float value) : Position(value), Rotation(value), Scale(value) {};
        Transform(float position, float rotation, float scale) : Position(position), Rotation(rotation), Scale(scale) {};
        Transform(Bed::Vector3 value) : Position(value), Rotation(value), Scale(value) {};
        Transform(Bed::Vector3 position, Bed::Vector3 rotation, Bed::Vector3 scale) : Position(position), Rotation(rotation), Scale(scale) {};

        // TODO: change rotation to a quarternion
        Bed::Vector3 Position;
        Bed::Vector3 Rotation;
        Bed::Vector3 Scale;

        /*glm::mat4 GetMatrix() const
        {
            glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale.x, m_Scale.y, m_Scale.z));

            glm::quat rotationQuat = glm::quat(glm::vec3(m_Rotation.x, m_Rotation.y, m_Rotation.z));
            glm::mat4 rotationMatrix = glm::toMat4(rotationQuat); 

            glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x, m_Position.y, m_Position.z));

            glm::mat4 transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;

            return transformMatrix;
        }*/
    };
}