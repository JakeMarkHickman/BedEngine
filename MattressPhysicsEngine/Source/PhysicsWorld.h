#pragma once

#include <vector>
#include <PhysicsObject.h>

namespace Mattress
{
    class PhysicsWorld
    {
    public:
        void AddPhysicsObject( PhysicsObject* objectToAdd );
        void RemovePhysicsObject( PhysicsObject* objectToRemove );

        void Step( float deltaTime );
    private:
        std::vector<PhysicsObject*> m_PhysicsObjects;
    };
}