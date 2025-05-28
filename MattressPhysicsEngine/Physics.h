#pragma once

namespace Mattress
{
    class Physics
    {
    public:
        Physics();

        void Step(float deltaTime);

        void SetTimeStep(float timeStep);
        float GetTimeStep();

    private:

    };    
}