#pragma once

#include <Bed/Game/Game.h>

#include <Math/Transform.h>
#include <Components/Renderer/Sprite.h>
#include <Components/Material/Texture.h>
#include <Components/Material/SubTexture.h>
#include <Components/Camera.h>


#include <Systems/Material/TextureSystem.h>
#include <Systems/Renderer/SpriteSystem.h>
#include <Systems/CameraSystem.h>
#include <Systems/Material/SubTextureSystem.h>

#include "Systems/PlayerControllerSystem.h"

namespace Game
{
    class Overworld : public Bed::Game
    {
    protected:
        virtual void BeginPlay() override {
            uint64_t overworld = m_ecs.CreateWorld();

            /*uint64_t player = m_ecs.CreateEntity(overworld);
            m_ecs.AttachComponents(overworld, player, Bed::Transform(0.0f, 0.0f, 1.0f),
                                                        Bed::Sprite(),
                                                        Bed::Texture("Assets/Resources/Textures/LittleGuy.png", Bed::TextureFiltering::Nearest),
                                                        Bed::SubTexture());*/

            uint64_t camera = m_ecs.CreateEntity(overworld);
            m_ecs.AttachComponents(overworld, camera, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                                        Bed::Camera(Bed::ProjectionType::Orthographic));

            uint64_t logo = m_ecs.CreateEntity(overworld);
            m_ecs.AttachComponents(overworld, logo, Bed::Transform(0.0f, 0.0f, 5.0f),
                                                        Bed::Sprite(),
                                                        Bed::Texture("Assets/Resources/Textures/BedEngineLogo.png"));                                            

            m_ecs.AddSystem(overworld, Bed::TextureSystem);
            m_ecs.AddSystem(overworld, Bed::SpriteSystem);
            m_ecs.AddSystem(overworld, Bed::CameraSystem);
            m_ecs.AddSystem(overworld, Bed::SubTextureSystem);
            //m_ecs.AddSystem(overworld, PlayerControllerSystem);
        };
    };
}