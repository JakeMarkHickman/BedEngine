#pragma once

#include <Bed/Game/GameObjects/Components/PlayerController.h>
#include <Bed/Input/Input.h>
#include <Bed/ContextRegistry/ContextRegistry.h>
#include <Components/Velocity.h>

namespace Bed
{
    void PlayerControllerSystem(Bed::World& world)
    {
        static bool DoOnce = false;

        if(DoOnce)
            return;

        DoOnce = true;

        Bed::ContextRegistry& instance = Bed::ContextRegistry::GetInstance();
        Bed::Input* input = instance.GetContext<Bed::Input>();

        input->InputEvent.Subscribe([&world](Bed::InputData data){

            for(int i = 0; world.GetAllEntities().size() > i; i++)
            {
                if(world.HasComponents<Bed::PlayerController>(i))
                {
                    if(!world.HasComponents<Bed::Velocity>(i))
                    {
                        world.AttachComponents(i, Bed::Velocity(0.0f));
                    }

                    Bed::Velocity* vel = world.GetComponent<Bed::Velocity>(i);

                    if (data.Keycode == GLFW_KEY_W)
                    {
                        if(data.State == KeyState::Press)
                        {
                            vel->Direction += Bed::Vector3(0.0f, 0.0f, 5.0f);
                        }
                        else if(data.State == KeyState::Released)
                        {
                            vel->Direction -= Bed::Vector3(0.0f, 0.0f, 5.0f);
                        }
                    }

                    if (data.Keycode == GLFW_KEY_A)
                    {
                        if(data.State == KeyState::Press)
                        {
                            vel->Direction += Bed::Vector3(-5.0f, 0.0f, 0.0f);
                        }
                        else if(data.State == KeyState::Released)
                        {
                            vel->Direction -= Bed::Vector3(-5.0f, 0.0f, 0.0f);
                        }
                    }

                    if (data.Keycode == GLFW_KEY_S)
                    {
                        if(data.State == KeyState::Press)
                        {
                            vel->Direction += Bed::Vector3(0.0f, 0.0f, -5.0f);
                        }
                        else if(data.State == KeyState::Released)
                        {
                            vel->Direction -= Bed::Vector3(0.0f, 0.0f, -5.0f);
                        }
                    }

                    if (data.Keycode == GLFW_KEY_D)
                    {
                        if(data.State == KeyState::Press)
                        {
                            vel->Direction += Bed::Vector3(5.0f, 0.0f, 0.0f);
                        }
                        else if(data.State == KeyState::Released)
                        {
                            vel->Direction -= Bed::Vector3(5.0f, 0.0f, 0.0f);
                        }
                    }
                }
            }
        });
    };
}