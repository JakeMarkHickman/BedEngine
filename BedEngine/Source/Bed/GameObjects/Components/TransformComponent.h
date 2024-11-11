#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <Bed/Math/Vector.h>
#include <Bed/Core.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>

namespace Bed
{
    struct BED_API Transform
    {
        Transform(Bed::Vector3 position, Bed::Vector3 rotation, Bed::Vector3 scale);

        Bed::Vector3 m_Position;
        Bed::Vector3 m_Rotation;
        Bed::Vector3 m_Scale;

        glm::mat4 GetMatrix() const
        {
            glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale.x, m_Scale.y, m_Scale.z));

            glm::quat rotationQuat = glm::quat(glm::vec3(m_Rotation.x, m_Rotation.y, m_Rotation.z));
            glm::mat4 rotationMatrix = glm::toMat4(rotationQuat); 

            glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x, m_Position.y, m_Position.z));

            glm::mat4 transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;

            return transformMatrix;
        }

    };
}