#include "PhysicsIntergration.h"
#include <Vector/Vector3.h>

void Mattress::PhysicsIntergration::CalculatePhysics(float deltaTime, PhysicsObject* physObject)
{
    switch (m_IntergrationStyle)
    {
    case Mattress::Intergration::SemiImplicitEuler:
        SemiImplicitEulerCalculation(deltaTime, physObject);
        break;
    
    default:
        break;
    }
}

void Mattress::PhysicsIntergration::SemiImplicitEulerCalculation(float deltaTime, PhysicsObject* physObject)
{
    Pillow::Vector3f Acceleration = physObject->Force * physObject->InverseMass();
    
    physObject->Velocity += Acceleration * deltaTime;
    physObject->Position += physObject->Velocity * deltaTime;
}

