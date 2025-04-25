#pragma once

//TODO: THIS IS FUCKING BAD CHANGE WHEN REFACTORING PLATFORMS
#include <Platforms/Win32.h>

#include <unordered_map>
#include <GLFW/glfw3.h>

namespace Bed
{
    void InputSystem(Bed::World& world)
    {
        GLFWwindow* window = Bed::Win32::GetWindow();

        std::unordered_map<int, Bed::KeyState> keys;
        std::unordered_map<int, Bed::KeyState> mice;
        double curx, cury;

        //TODO: GLFW inputs must only be called from the main THREAD AKA cant go in a system

        glfwGetCursorPos(window, &curx, &cury);

        for(int mouse = GLFW_MOUSE_BUTTON_1; mouse <= GLFW_MOUSE_BUTTON_LAST; mouse++)
        {
            int state = glfwGetMouseButton(window, mouse);

            Bed::KeyState mouseState;

            switch (state)
            {
                case GLFW_RELEASE:
                    mouseState = Bed::KeyState::Released;
                    break;

                case GLFW_PRESS:
                    mouseState = Bed::KeyState::Pressed;
                    break;

                case GLFW_REPEAT:
                    mouseState = Bed::KeyState::Hold;
                    break;
            
                default:
                    mouseState = Bed::KeyState::Released;
                    break;
            }

            mice[mouse] = mouseState;
        }

        for(int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++)
        {
            //Test Key state
            int state = glfwGetKey(window, key);
            Bed::KeyState keyState;

            switch (state)
            {
                case GLFW_RELEASE:
                    keyState = Bed::KeyState::Released;
                    break;

                case GLFW_PRESS:
                    keyState = Bed::KeyState::Pressed;
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

                //Store old input events
                input->PreviousKeyData = input->KeyData;
                input->PreviousMouseData = input->MouseData;

                input->KeyData = keys;
                input->MouseData = mice;
                input->CursorX = curx;
                input->CursorY = cury;
            }
        }
    };
}