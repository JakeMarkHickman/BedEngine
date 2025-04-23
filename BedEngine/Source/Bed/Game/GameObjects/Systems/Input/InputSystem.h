#pragma once

//TODO: THIS IS FUCKING BAD CHANGE WHEN REFACTORING PLATFORMS
#include <Platforms/Win32.h>

#include <unordered_map>
#include <GLFW/glfw3.h>

#include <Components/Input/Input.h>

namespace Bed
{
    void InputSystem(Bed::World& world)
    {
        std::unordered_map<int, Bed::KeyState> keys;

        for(int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++)
        {
            //Test Key state
            int state = glfwGetKey(Bed::Win32::GetWindow(), key);
            Bed::KeyState keyState;

            switch (state)
            {
                case GLFW_RELEASE:
                    keyState = Bed::KeyState::Released;
                    break;

                case GLFW_PRESS:
                    keyState = Bed::KeyState::Press;
                    break;

                case GLFW_REPEAT:
                    keyState = Bed::KeyState::Hold;
                    break;
            
                default:
                    keyState = Bed::KeyState::Released;
                    break;
            }

            keys[key] = keyState;
        }

        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::Input>(i))
            {
                Bed::Input* input = world.GetComponent<Bed::Input>(i);

                input->KeyData = keys;
            }
        }
    };
}