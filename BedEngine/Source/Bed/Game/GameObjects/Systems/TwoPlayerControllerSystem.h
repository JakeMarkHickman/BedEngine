#pragma once

#include <Vector/VectorMath.h>

namespace Bed
{
    void TwoPlayerControllerSystem(Bed::World& world)
    {
        for(uint64_t i : world.GetAllEntities())
        {
            if(world.HasComponents<Bed::Input, Bed::PlayerTag, Bed::PhysicsObject>(i))
            {
                Bed::Input* input = world.GetComponent<Bed::Input>(i);
                Bed::PhysicsObject* object = world.GetComponent<Bed::PhysicsObject>(i);
                Bed::PlayerTag* player = world.GetComponent<Bed::PlayerTag>(i);

                Pillow::Vector3f direction;
                float speed = player->Speed;

                //MOVEMENT
                if(player->ID == 0) //Player 1
                {
                    if(input->KeyData[GLFW_KEY_W] == KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(0.0f, 1.0f, 0.0f)) * speed;
                    if(input->KeyData[GLFW_KEY_A] == KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(-1.0f, 0.0f, 0.0f)) * speed;
                    if(input->KeyData[GLFW_KEY_S] == KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(0.0f, -1.0f, 0.0f)) * speed;
                    if(input->KeyData[GLFW_KEY_D] == KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(1.0f, 0.0f, 0.0f)) * speed;
                }

                if(player->ID == 1) //Player 2
                {
                    if(input->KeyData[GLFW_KEY_UP] == KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(0.0f, 1.0f, 0.0f)) * speed;
                    if(input->KeyData[GLFW_KEY_LEFT] == KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(-1.0f, 0.0f, 0.0f)) * speed;
                    if(input->KeyData[GLFW_KEY_DOWN] == KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(0.0f, -1.0f, 0.0f)) * speed;
                    if(input->KeyData[GLFW_KEY_RIGHT] == KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(1.0f, 0.0f, 0.0f)) * speed;
                }

                world.GetWorldPhysics().ApplyForce(object->Handle, direction);
            }
        }
    }
}