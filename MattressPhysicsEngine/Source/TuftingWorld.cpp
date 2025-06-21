#include "TuftingWorld.h"

uint64_t Mattress::TuftingWorld::AddPhysicsHandle()
{
    /*
        TODO: Need a utilityLib that has a sparse set for all physics assets
        This will then allow for unordered access to data while keeping data access quick
    */

    uint64_t currentPhysicsHandle = m_NextPhysicsHandle;
    m_NextPhysicsHandle++;

    m_RigidBodyData.Positions[currentPhysicsHandle] = Pillow::Vector3f(0.0f, 0.0f, 0.0f);
    m_RigidBodyData.Masses[currentPhysicsHandle] = 1.0f;
    m_RigidBodyData.Velocities[currentPhysicsHandle] = Pillow::Vector3f(0.0f, 0.0f, 0.0f);
    m_RigidBodyData.Forces[currentPhysicsHandle] = Pillow::Vector3f(0.0f, 0.0f, 0.0f);

    return m_NextPhysicsHandle;
}

/*
    run the physics simulation for the time that has passed
*/
void Mattress::TuftingWorld::PhysicsStep(float deltaTime)
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


}