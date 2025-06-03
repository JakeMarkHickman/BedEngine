#pragma once

namespace Mattress
{
    class PhysicsWorld
    {
    public:
        void AddPhysicsObject();
        void RemovePhysicsObject();

        void Step(float deltaTime);
    private:
    }
}