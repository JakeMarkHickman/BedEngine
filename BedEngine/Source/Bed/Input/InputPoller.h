#pragma once

#include <Events/Event.h>
#include <GLFW/glfw3.h>

namespace Bed
{
    enum KeyState
    {
        Released,
        Press,
        Hold
    };

    struct InputData
    {
        int Player; // Player who used the event (local multiplayer)
        int Keycode; // Key that was pressed
        KeyState State; // The state which the key is in

        float MouseX;
        float MouseY;
    };

    class InputPoller
    {
    public:
        void Init()
        {
            for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key)
            {
                m_LastKeyStates[key] = KeyState::Released;
            }
        }

        void PollInput(GLFWwindow* window, int playerID)
        {
            for(int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++)
            {
                KeyState state = GetKeyState(window, key);
                if(m_LastKeyStates[key] != state) // checks when the state changes
                {
                    InputData data;
                    data.Player = playerID;
                    data.Keycode = key;
                    data.State = state;
                    InputEvent.Broadcast(data);
                }
            }
        }

        Event<InputData> InputEvent;

    private:
        KeyState GetKeyState(GLFWwindow* window, int key)
        {
            int state = glfwGetKey(window, key);

            KeyState curState;
            switch(state)
            {
                case 0:
                    curState = KeyState::Released;
                    break;
                case 1:
                    curState = KeyState::Press;
                    break;
                case 2:
                    curState = KeyState::Hold;
                    break;
                default:
                    curState = KeyState::Released;
                    break;
            }
            
            return curState;
        }
        std::unordered_map<int, KeyState> m_LastKeyStates;
    };
    
}