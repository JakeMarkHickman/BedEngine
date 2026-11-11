#pragma once

#include <vector>

#include <SleepTrace.h>

#include <SparseSet.h>

#include "PhysicsData/BodyData.h"
#include "PhysicsData/CollisionData.h"
#include "PhysicsIntergration.h"

#include "Collision/CollisionCheck.h"

namespace Mattress
{
    /*
        Tufting World is a physics simulation class

        This runs all the math that will be used within a physics space
    */
    class TuftingWorld
    {
    public:
    
        uint64_t AddPhysicsBody(Pillow::Vector3f& position, float mass);
        Pillow::Vector3f GetPhysicsBodyLocation(uint64_t physicsBodyHandle);
        void RemovePhysicsHandle(uint64_t physicsBodyHandle);

        uint64_t AddCollider(Mattress::CollisionType collisionType, uint64_t physicsBodyHandle, Pillow::Vector3f halfExtent);
        void RemoveCollisionHandle(uint64_t CollisionHandle);

        void FindContacts();
        void ResolveContacts();

        void ApplyForce(uint64_t physicsBodyHandle, Pillow::Vector3f forceToAdd);

        void PhysicsStep(float deltaTime);

        inline float InverseMass(float mass)
        {
            return mass > 0.0f ? 1.0f / mass : 0.0f;
        }
        
    private:

        Frame::SparseSet<uint64_t> m_EntityPhysicsObjectLink;

        uint64_t m_NextPhysicsHandle = 0;
        std::vector<uint64_t> m_PhysicsHandles;
        std::vector<uint64_t> m_RecycledPhysicsHandles;

        uint64_t m_NextAABBCollisionHandle = 0;
        std::vector<uint64_t> m_AABBHandles;
        std::vector<uint64_t> m_RecycledAABBHandles;

        std::vector<Mattress::ContactData> m_Contacts;

        Mattress::BodyData m_BodyData;
        Mattress::AABBCollisionData m_AABBColliders;

        Mattress::PhysicsIntergration m_IntergrationMethod;
    };

    using PhysicsWorld = TuftingWorld;
}