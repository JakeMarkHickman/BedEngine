#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "Vector/Vector3.h"

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/quaternion.hpp"
#include "../Dependencies/glm/gtx/quaternion.hpp"
#include "../Dependencies/glm/gtx/euler_angles.hpp"

namespace Pillow
{
    struct Transform
    {
        Transform() {};
        Transform(float value) : Position(value), Rotation(value), Scale(value) {};
        Transform(float position, float rotation, float scale) : Position(position), Rotation(rotation), Scale(scale) {};
        Transform(Pillow::Vector3f value) : Position(value), Rotation(value), Scale(value) {};
        Transform(Pillow::Vector3f position, Pillow::Vector3f rotation, Pillow::Vector3f scale) : Position(position), Rotation(rotation), Scale(scale) {};

        // TODO: change rotation to a quarternion
        Pillow::Vector3f Position;
        Pillow::Vector3f Rotation;
        Pillow::Vector3f Scale;

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

        Transform& operator*=(const Transform& other)
        {
            Position *= other.Position;
            Rotation *= other.Rotation;
            Scale *= other.Scale;
            return *this;
        }
    };
}