#include "PhysicsWorld.h"

#include <iostream>

void Mattress::PhysicsWorld::AddPhysicsObject( PhysicsObject* objectToAdd )
{
    std::cout << "Adding Physics Object\n";
    m_PhysicsObjects.push_back(objectToAdd);

    m_PhysicsData.Positions.push_back();
    m_PhysicsData.Velocities.push_back();
    m_PhysicsData.Forces.push_back();
    m_PhysicsData.Masses.push_back();

}

void Mattress::PhysicsWorld::RemovePhysicsObject( PhysicsObject* objectToRemove )
{

}

void Mattress::PhysicsWorld::Step( float deltaTime )
{
    //TODO: use Physics Step to simulate delta time at a constant rate

    //TODO: Non Euclidean Physics

    /*
        Broad Phase Collision - Quickly find objects that might collide

        External forces - Wind, Gravity, Boyancy ect

        Intergration - Euler, Verlet, RK4

        Narrow Phase Collision - Check if objects actually touch

        Post Processing - Dampening, Clamping velocities

        Clear All Accumulated Forces
    */

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