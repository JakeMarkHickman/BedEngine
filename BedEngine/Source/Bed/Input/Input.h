#pragma once

#include <Events/Event.h>

namespace Bed
{
    enum KeyState
    {
        Released,
        Press,
        Hold
    }

    struct InputData
    {
        int Player; // Player who used the event (local multiplayer)
        int Keycode; // Key that was pressed
        KeyState State; // The state which the key is in

        float MouseX;
        float MouseY;
    }

    class Input
    {
    public:
        virtual ~Input();

        //Keyboard
        virtual void KeyPressed(int playerId, int keycode) const {};
        virtual void KeyHeld(int playerId, int keycode) const {};
        virtual void KeyReleased(int playerId, int keycode) const {};

        //Mouse
        virtual void GetMousePosition() const {};

        Event<InputData> InputEvent;

    private:
    };
    
}