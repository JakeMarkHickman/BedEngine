#pragma once

#include <Components/Velocity.h>

#include <Graphics/GraphicVariables.h>

namespace Bed
{
    void PlayerControllerSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::Input, Bed::PlayerTag>(i))
            {
                if(!world.HasComponents<Bed::Velocity>(i))
                {
                    world.AttachComponents(i, Bed::Velocity(0.0f, 5.0f));
                }

                Bed::Input* input = world.GetComponent<Bed::Input>(i);
                Bed::Velocity* vel = world.GetComponent<Bed::Velocity>(i);


                //SHADER
                if(input->KeyData[GLFW_KEY_L] == KeyState::Pressed)
                {
                    shader3D->SetUniform1i("u_GlobalUnlit", true);
                }
                else if(input->KeyData[GLFW_KEY_L] == KeyState::Released)
                {
                    shader3D->SetUniform1i("u_GlobalUnlit", false);
                }

                Pillow::Vector3f Direction(0.0f, 0.0f, 0.0f);

                //MOVEMENT
                if(input->KeyData[GLFW_KEY_W] == KeyState::Pressed)
                {
                    Direction += Pillow::Vector3f(0.0f, 0.0f, 5.0f);
                }

                if(input->KeyData[GLFW_KEY_A] == KeyState::Pressed)
                {
                    Direction += Pillow::Vector3f(-5.0f, 0.0f, 0.0f);
                }

                if(input->KeyData[GLFW_KEY_S] == KeyState::Pressed)
                {
                    Direction += Pillow::Vector3f(0.0f, 0.0f, -5.0f);
                }

                if(input->KeyData[GLFW_KEY_D] == KeyState::Pressed)
                {
                    Direction += Pillow::Vector3f(5.0f, 0.0f, 0.0f);
                }

                vel->Direction = Direction;
            }
        }
    }
}

    