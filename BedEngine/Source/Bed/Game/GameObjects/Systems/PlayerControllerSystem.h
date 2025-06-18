#pragma once

#include <Vector/VectorMath.h>

#include <Graphics/GraphicVariables.h>

namespace Bed
{
    void PlayerControllerSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::Input, Bed::PlayerTag, Mattress::PhysicsObject>(i))
            {

                Bed::Input* input = world.GetComponent<Bed::Input>(i);
                Mattress::PhysicsObject* physObj = world.GetComponent<Mattress::PhysicsObject>(i);

                //SHADER
                if(input->KeyData[GLFW_KEY_L] == KeyState::Pressed)
                {
                    shader3D->SetUniform1i("u_GlobalUnlit", true);
                }
                else if(input->KeyData[GLFW_KEY_L] == KeyState::Released)
                {
                    shader3D->SetUniform1i("u_GlobalUnlit", false);
                }

                //Pillow::Vector3f direction;

                //MOVEMENT
                if(input->KeyData[GLFW_KEY_W] == KeyState::Pressed)
                {
                    //direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(0.0f, 0.0f, 1.0f)) * 5.0f;
                    physObj->AddForce(Pillow::Vector3f(0.0f, 0.0f, 5.0f));
                }

                if(input->KeyData[GLFW_KEY_A] == KeyState::Pressed)
                {
                    //direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(-1.0f, 0.0f, 0.0f)) * 5.0f;
                    physObj->AddForce(Pillow::Vector3f(-5.0f, 0.0f, 0.0f));
                }

                if(input->KeyData[GLFW_KEY_S] == KeyState::Pressed)
                {
                    //direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(0.0f, 0.0f, -1.0f)) * 5.0f;
                    physObj->AddForce(Pillow::Vector3f(0.0f, 0.0f, -5.0f));
                }

                if(input->KeyData[GLFW_KEY_D] == KeyState::Pressed)
                {
                    //direction += Pillow::VectorMath::Normalise(Pillow::Vector3f(1.0f, 0.0f, 0.0f)) * 5.0f;
                    physObj->AddForce(Pillow::Vector3f(5.0f, 0.0f, 0.0f));
                }

                //physObj->Velocity = direction;
            }
        }
    }
}

    