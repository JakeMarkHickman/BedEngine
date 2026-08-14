#include "TuftingWorld.h"
#include "SleepTrace.h"


uint64_t Mattress::TuftingWorld::AddPhysicsBody(Pillow::Vector3f& position, float mass)
{
    /*
        TODO: Need a utilityLib that has a sparse set for all physics assets
        This will then allow for unordered access to data while keeping data access quick
    */

    uint64_t currentPhysicsHandle = m_NextPhysicsHandle;
    m_NextPhysicsHandle++;

    m_BodyData.Positions.push_back(position);
    m_BodyData.Masses.push_back(mass);
    m_BodyData.Velocities.push_back(Pillow::Vector3f(0.0f, 0.0f, 0.0f));
    m_BodyData.Forces.push_back(Pillow::Vector3f(0.0f, 0.0f, 0.0f));

    return currentPhysicsHandle;
}

Pillow::Vector3f Mattress::TuftingWorld::GetPhysicsBodyLocation(uint64_t handle)
{
    return m_BodyData.Positions[handle];
}

void Mattress::TuftingWorld::ApplyForce(uint64_t handle, Pillow::Vector3f forceToAdd)
{
    m_BodyData.Forces[handle] += forceToAdd;
}

/*
    run the physics simulation for the time that has passed
*/
void Mattress::TuftingWorld::PhysicsStep(float deltaTime)
{
    //TODO: use Physics Step to simulate delta time at a constant rate

    //TODO: Non Euclidean Physics

    float friction = 0.5f;

    /*
        Broad Phase Collision - Quickly find objects that might collide

        External forces - Wind, Gravity, Boyancy ect

        Intergration - Euler, Verlet, RK4

        Narrow Phase Collision - Check if objects actually touch

        Post Processing - Dampening, Clamping velocities

        Clear All Accumulated Forces
    */

    for(int bodyHandle = 0; bodyHandle < m_NextPhysicsHandle; bodyHandle++)
    {
        Pillow::Vector3f acceleration = m_BodyData.Forces[bodyHandle] / m_BodyData.Masses[bodyHandle];
        m_BodyData.Velocities[bodyHandle] += acceleration * deltaTime;
        m_BodyData.Positions[bodyHandle] += m_BodyData.Velocities[bodyHandle] * deltaTime;
    }

    //Post Processing
    for(Pillow::Vector3f& velocity : m_BodyData.Velocities)
    {
        velocity *= friction;
    }

    for(Pillow::Vector3f& force : m_BodyData.Forces)
    {
        force = Pillow::Vector3f(0.0f);
    }
}