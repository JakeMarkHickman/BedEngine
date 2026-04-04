#pragma once

#include <Duvet.h>

namespace Bed
{

    struct CameraSystems
    {
        Quilt::Duvet renderer;

        void OnCameraComponentAttached(Bed::World& world, uint64_t entity)
        {
            if(world.HasComponents<Pillow::Transform, Bed::Camera>(entity))
            {
                Bed::Camera* cam = world.GetComponent<Bed::Camera>(entity);        
                cam->Handle = renderer.CreateCamera(cam->Active, cam->XScreenPosition, cam->YScreenPosition, cam->XScreenSize, cam->YScreenSize);
            }
        }

        void OnCameraComponentRemoved(Bed::World& world, uint64_t entity)
        {
            if(world.HasComponents<Pillow::Transform, Bed::Camera>(entity))
            {
                Bed::Camera* cam = world.GetComponent<Bed::Camera>(entity);
                renderer.RemoveCamera(cam->Handle);
            }
        }

        void CameraSystem(Bed::World& world)
        {
            for(uint64_t entity : world.GetAllEntities())
            {
                if(world.HasComponents<Pillow::Transform, Bed::Camera>(entity))
                {
                    Bed::Camera* cam = world.GetComponent<Bed::Camera>(entity);
                    Pillow::Transform* transform = world.GetComponent<Pillow::Transform>(entity);

                    renderer.UpdateCamera(cam->Handle, *transform);
                }
            }
        }
    };
}