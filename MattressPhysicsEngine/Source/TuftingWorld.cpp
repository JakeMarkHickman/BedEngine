#include "TuftingWorld.h"
#include "SleepTrace.h"

#include <Vector/Vector2.h>
#include <Vector/Vector4.h>
#include <Vector/VectorMath.h>

uint64_t Mattress::TuftingWorld::AddPhysicsBody(Pillow::Vector3f& position, float mass)
{
    /*
        TODO: Need a utilityLib that has a sparse set for all physics assets
        This will then allow for unordered access to data while keeping data access quick
    */

    //TODO: need to recycle Physics Handles

    uint64_t currentPhysicsHandle = m_NextPhysicsHandle;
    m_NextPhysicsHandle++;

    m_BodyData.Positions.push_back(position);
    m_BodyData.Masses.push_back(mass);
    m_BodyData.Velocities.push_back(Pillow::Vector3f(0.0f, 0.0f, 0.0f));
    m_BodyData.Forces.push_back(Pillow::Vector3f(0.0f, 0.0f, 0.0f));

    return currentPhysicsHandle;
}

Pillow::Vector3f Mattress::TuftingWorld::GetPhysicsBodyLocation(uint64_t physicsBodyHandle)
{
    return m_BodyData.Positions[physicsBodyHandle];
}

void Mattress::TuftingWorld::RemovePhysicsHandle(uint64_t physicsBodyHandle)
{
    LOG_WARN("~~ !!REMOVING PHYSICS BODY NEEDS TO BE IMPLEMENTED!! ~~");
}

uint64_t Mattress::TuftingWorld::AddCollider(Mattress::CollisionType collisionType, uint64_t physicsBodyHandle, Pillow::Vector3f halfExtent)
{
    //TODO: need to recycle collision Handles

    uint64_t handle;

    switch (collisionType)
    {
    case Mattress::CollisionType::Box:
        {
            uint64_t currentAABBColliderHandle = m_NextAABBCollisionHandle;
            m_NextAABBCollisionHandle++;

            m_AABBColliders.HalfExents.push_back(halfExtent);
            m_AABBColliders.BodyHandles.push_back(physicsBodyHandle);

            handle = currentAABBColliderHandle;
            break;
        }
    case Mattress::CollisionType::Sphere:
            LOG_WARN("~~ !!SPHERE COLLISION NEEDS TO BE IMPLEMENTED!! ~~");
        break;

    default:
            LOG_ERROR("UNDEFINED COLLISION TYPE");
        break;
    }

    return handle;
}

void Mattress::TuftingWorld::RemoveCollisionHandle(uint64_t CollisionHandle)
{
    LOG_WARN("~~ !!REMOVING COLLISION NEEDS TO BE IMPLEMENTED!! ~~");
}

void Mattress::TuftingWorld::FindContacts()
{
    m_Contacts.clear();

    for(size_t a = 0; a<  m_AABBColliders.BodyHandles.size(); a++)
    {
        for(size_t b = a + 1; b < m_AABBColliders.BodyHandles.size(); b++)
        {
            uint64_t bodyA = m_AABBColliders.BodyHandles[a];
            uint64_t bodyB = m_AABBColliders.BodyHandles[b];

            if(InverseMass(m_BodyData.Masses[bodyA]) == 0.0f && InverseMass(m_BodyData.Masses[bodyB]) == 0.0f)
                continue;
            
            ContactData contact { bodyA, bodyB };
            if(CollisionChecks::AABBOverlap(m_BodyData.Positions[bodyA], m_AABBColliders.HalfExents[a], m_BodyData.Positions[bodyB], m_AABBColliders.HalfExents[b], contact))
                m_Contacts.push_back(contact);
        }
    }
}

void Mattress::TuftingWorld::ResolveContacts()
{
    for(const Mattress::ContactData& contact : m_Contacts)
    {
        float invA = InverseMass(m_BodyData.Masses[contact.BodyA]);
        float invB = InverseMass(m_BodyData.Masses[contact.BodyB]);
        float invSum = invA + invB;

        //Push the collisions apart
        Pillow::Vector3f push = contact.Normal * (contact.Penetration / invSum);
        m_BodyData.Positions[contact.BodyA] -= push * invA;
        m_BodyData.Positions[contact.BodyB] += push * invB;

        //stop collisions moving into eachother
        Pillow::Vector3f relativeVel = m_BodyData.Velocities[contact.BodyB] - m_BodyData.Velocities[contact.BodyA];
        float closingSpeed = Pillow::VectorMath::Dot(relativeVel, contact.Normal);
        if(closingSpeed >= 0.0f)
            continue;

        Pillow::Vector3f impulse = contact.Normal * (-closingSpeed / invSum);
        m_BodyData.Velocities[contact.BodyA] -= impulse * invA;
        m_BodyData.Velocities[contact.BodyB] += impulse * invA;
    }
}

void Mattress::TuftingWorld::ApplyForce(uint64_t physicsBodyHandle, Pillow::Vector3f forceToAdd)
{
    m_BodyData.Forces[physicsBodyHandle] += forceToAdd;
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

    FindContacts();
    ResolveContacts();

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