#pragma once

#include <vector>
#include "PhysicsObject.h"
#include "Collision/AABB.h"
#include "PhysicsIntergration.h"

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
        std::vector<AABB*> m_CollisionObjects;
        Mattress::PhysicsIntergration m_IntergrationMethod;
    };
}