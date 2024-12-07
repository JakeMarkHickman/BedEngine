#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "Vector/Vector3.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
namespace Bed
{
    struct BED_API Transform
    {
        Transform() {};

        Transform(float value) : Position(value), Rotation(value), Scale(value),
                                 LocalPosition(value), LocalRotation(value), LocalScale(value) {};

        Transform(float position, float rotation, float scale) : Position(position), Rotation(rotation), Scale(scale),
                                                                 LocalPosition(position), LocalRotation(rotation), LocalScale(scale) {};

        Transform(Bed::Vector3 value) : Position(value), Rotation(value), Scale(value), 
                                        LocalPosition(value), LocalRotation(value), LocalScale(value) {};

        Transform(Bed::Vector3 position, Bed::Vector3 rotation, Bed::Vector3 scale) : Position(position), Rotation(rotation), Scale(scale),
                                                                                      LocalPosition(position), LocalRotation(rotation), LocalScale(scale) {};

        // TODO: change rotation to a quarternion
        Bed::Vector3 Position;
        Bed::Vector3 Rotation;
        Bed::Vector3 Scale;

        Bed::Vector3 LocalPosition;
        Bed::Vector3 LocalRotation;
        Bed::Vector3 LocalScale;

        glm::mat4 GetMatrix() const
        {
            glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(Scale.x, Scale.y, Scale.z));

            glm::quat rotationQuat = glm::quat(glm::vec3(Rotation.x, Rotation.y, Rotation.z));
            glm::mat4 rotationMatrix = glm::toMat4(rotationQuat); 

            glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(Position.x, Position.y, Position.z));

            glm::mat4 transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;

            return transformMatrix;
        }

        Transform& operator+=(const Transform& other)
        {
            Position += other.Position;
            Rotation += other.Rotation;
            Scale += other.Scale;
            return *this;
        }
    };
}