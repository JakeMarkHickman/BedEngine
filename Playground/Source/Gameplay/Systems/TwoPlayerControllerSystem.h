#pragma once

#include <Vector/VectorMath.h>

namespace Playground
{
    void TwoPlayerControllerSystem(Bed::World& world)
    {
        for(uint64_t i : world.GetAllEntities())
        {
            if(world.HasComponents<Bed::Input, Playground::Player, Bed::PhysicsObject>(i))
            {
                Bed::Input* input = world.GetComponent<Bed::Input>(i);
                Bed::PhysicsObject* object = world.GetComponent<Bed::PhysicsObject>(i);
                Playground::Player* player = world.GetComponent<Playground::Player>(i);

                Pillow::Vector3f direction;
                float speed = player->Speed;

                //MOVEMENT
                if(player->ID == 0) //Player 1
                {
                    if(input->KeyData[GLFW_KEY_W] == Bed::KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(0.0f, 1.0f, 0.0f)) * speed;
                    if(input->KeyData[GLFW_KEY_A] == Bed::KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(-1.0f, 0.0f, 0.0f)) * speed;
                    if(input->KeyData[GLFW_KEY_S] == Bed::KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(0.0f, -1.0f, 0.0f)) * speed;
                    if(input->KeyData[GLFW_KEY_D] == Bed::KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(1.0f, 0.0f, 0.0f)) * speed;
                }

                if(player->ID == 1) //Player 2
                {
                    if(input->KeyData[GLFW_KEY_UP] == Bed::KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(0.0f, 1.0f, 0.0f)) * speed;
                    if(input->KeyData[GLFW_KEY_LEFT] == Bed::KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(-1.0f, 0.0f, 0.0f)) * speed;
                    if(input->KeyData[GLFW_KEY_DOWN] == Bed::KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(0.0f, -1.0f, 0.0f)) * speed;
                    if(input->KeyData[GLFW_KEY_RIGHT] == Bed::KeyState::Pressed) direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(1.0f, 0.0f, 0.0f)) * speed;
                }

                world.GetWorldPhysics().ApplyForce(object->Handle, direction);
            }
        }
    }
}