#pragma once

#include <vector>

#include "PhysicsData/BodyData.h" 
#include "PhysicsIntergration.h"

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
        Pillow::Vector3f GetPhysicsBodyLocation(uint64_t handle);
        void RemovePhysicsHandle(uint64_t handle);

        void ApplyForce(uint64_t handle, Pillow::Vector3f forceToAdd);

        void PhysicsStep(float deltaTime);
        
    private:

        uint64_t m_NextPhysicsHandle = 0;
        std::vector<uint64_t> m_PhysicsHandles;
        std::vector<uint64_t> m_RecycledHandles;

        Mattress::BodyData m_BodyData;

        Mattress::PhysicsIntergration m_IntergrationMethod;
    };
}