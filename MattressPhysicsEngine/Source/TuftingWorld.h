#pragma once

#include <vector>

#include "PhysicsData/RigidBodyData.h" 
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
    
        uint64_t AddPhysicsHandle();
        void RemovePhysicsHandle(uint64_t handle);

        void PhysicsStep(float deltaTime);
        
    private:

        uint64_t m_NextPhysicsHandle = 0;
        std::vector<uint64_t> m_PhysicsHandles;
        std::vector<uint64_t> m_RecycledHandles;

        Mattress::RigidBodyData m_RigidBodyData;

        Mattress::PhysicsIntergration m_IntergrationMethod;

    };
}