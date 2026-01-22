#pragma once

#include <Vector/VectorMath.h>

namespace Bed
{
    void TwoPlayerControllerSystem(Bed::World& world)
    {
        for(uint64_t i : world.GetAllEntities())
        {
            //TODO: * by delta time shouldnt be done here and needs to just work out of the box with physics

            //Player One
            if(world.HasComponents<Bed::Input, Bed::PlayerOneTag, Mattress::PhysicsObject>(i))
            {
                Bed::Input* input = world.GetComponent<Bed::Input>(i);
                Mattress::PhysicsObject* physObj = world.GetComponent<Mattress::PhysicsObject>(i);

                //MOVEMENT
                if(input->KeyData[GLFW_KEY_W] == KeyState::Pressed)
                {
                    //direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(0.0f, 0.0f, 1.0f)) * 5.0f;
                    physObj->AddForce(Pillow::Vector3f(0.0f, 10.0f, 0.0f) * Time::GetDeltaTime());
                }

                if(input->KeyData[GLFW_KEY_A] == KeyState::Pressed)
                {
                    //direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(-1.0f, 0.0f, 0.0f)) * 5.0f;
                    physObj->AddForce(Pillow::Vector3f(-10.0f, 0.0f, 0.0f) * Time::GetDeltaTime());
                }

                if(input->KeyData[GLFW_KEY_S] == KeyState::Pressed)
                {
                    //direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(0.0f, 0.0f, -1.0f)) * 5.0f;
                    physObj->AddForce(Pillow::Vector3f(0.0f, -10.0f, 0.0f) * Time::GetDeltaTime());
                }

                if(input->KeyData[GLFW_KEY_D] == KeyState::Pressed)
                {
                    //direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(1.0f, 0.0f, 0.0f)) * 5.0f;
                    physObj->AddForce(Pillow::Vector3f(10.0f, 0.0f, 0.0f) * Time::GetDeltaTime());
                }
            }

            //Player2
            if(world.HasComponents<Bed::Input, Bed::PlayerTwoTag, Mattress::PhysicsObject>(i))
            {
                Bed::Input* input = world.GetComponent<Bed::Input>(i);
                Mattress::PhysicsObject* physObj = world.GetComponent<Mattress::PhysicsObject>(i);

                //MOVEMENT
                if(input->KeyData[GLFW_KEY_UP] == KeyState::Pressed)
                {
                    //direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(0.0f, 0.0f, 1.0f)) * 5.0f;
                    physObj->AddForce(Pillow::Vector3f(0.0f, 10.0f, 0.0f) * Time::GetDeltaTime());
                }

                if(input->KeyData[GLFW_KEY_LEFT] == KeyState::Pressed)
                {
                    //direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(-1.0f, 0.0f, 0.0f)) * 5.0f;
                    physObj->AddForce(Pillow::Vector3f(-10.0f, 0.0f, 0.0f) * Time::GetDeltaTime());
                }

                if(input->KeyData[GLFW_KEY_DOWN] == KeyState::Pressed)
                {
                    //direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(0.0f, 0.0f, -1.0f)) * 5.0f;
                    physObj->AddForce(Pillow::Vector3f(0.0f, -10.0f, 0.0f) * Time::GetDeltaTime());
                }

                if(input->KeyData[GLFW_KEY_RIGHT] == KeyState::Pressed)
                {
                    //direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(1.0f, 0.0f, 0.0f)) * 5.0f;
                    physObj->AddForce(Pillow::Vector3f(10.0f, 0.0f, 0.0f) * Time::GetDeltaTime());
                }
            }
        }
    }
}