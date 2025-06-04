#include "PhysicsWorld.h"

void Mattress::PhysicsWorld::AddPhysicsObject( PhysicsObject* objectToAdd )
{
    m_PhysicsObjects.push_back(objectToAdd);
}

void Mattress::PhysicsWorld::RemovePhysicsObject( PhysicsObject* objectToRemove )
{

}

void Mattress::PhysicsWorld::Step( float deltaTime )
{
    //TODO: use Physics Step to simulate delta time at a constant rate

    for(PhysicsObject* phyObj : m_PhysicsObjects)
    {
        phyObj->Velocity += (phyObj->Force * phyObj->InverseMass()) * deltaTime;
        phyObj->Position += phyObj->Velocity * deltaTime;

        phyObj->Force = Pillow::Vector3f(0.0f);
    }
}