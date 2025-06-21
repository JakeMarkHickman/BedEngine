#include "PhysicsWorld.h"

#include <iostream>

void Mattress::PhysicsWorld::AddPhysicsObject( PhysicsObject* objectToAdd )
{
    std::cout << "Adding Physics Object\n";
    m_PhysicsObjects.push_back(objectToAdd);
}

void Mattress::PhysicsWorld::RemovePhysicsObject( PhysicsObject* objectToRemove )
{

}

void Mattress::PhysicsWorld::Step( float deltaTime )
{
    //TODO: Make friction better
    float friction = 0.99f;
    //Pillow::Vector3f gravity = Pillow::Vector3f(0.0f, -9.8f, 0.0f);

    //Broad Phase Collision
    //for(AABB* collision : m_CollisionObjects)
    //{

    //}

    for(PhysicsObject* phyObj : m_PhysicsObjects)
    {
        //External Forces
        //phyObj->Velocity += gravity;

        //Intergration
        m_IntergrationMethod.CalculatePhysics(deltaTime, phyObj);
    }

    //Narrow Phase Collision
    //for(AABB* collision : m_CollisionObjects)
    //{

    //}

    
    for(PhysicsObject* phyObj : m_PhysicsObjects)
    {
        //Post Processing
        phyObj->Velocity *= friction;

        //Clear All Acumulated Forces
        phyObj->Force = Pillow::Vector3f(0.0f);
    }
}