#pragma once

#include "PhysicsObject.h"

namespace Mattress
{
    enum class Intergration
    {
        SemiImplicitEuler,
        Verlet,
        RungeKuttaMethods,
        ImplicitIntergration
    };

    class PhysicsIntergration
    {
    public:
        void CalculatePhysics(float deltaTime, PhysicsObject* physObject);

        void SetIntergrationStyle(Intergration intergrationStyle) { m_IntergrationStyle = intergrationStyle;};
        Intergration GetIntergrationStyle() { return m_IntergrationStyle; };

    private:
        void SemiImplicitEulerCalculation(float deltaTime, PhysicsObject* physObject);
        
        Intergration m_IntergrationStyle = Intergration::SemiImplicitEuler;
    };
}