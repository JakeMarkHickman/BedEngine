#pragma once

#include <Transform.h>
#include <vector>

namespace Quilt
{
    enum class ProjectionType
    {
        Orthographic,
        Perspective
    };

    struct Cameras
    {
        std::vector<bool> Active;
        std::vector<ProjectionType> ProjectionTypes;

        std::vector<const Pillow::Transform*> Transforms;

        std::vector<float> XSizes;
        std::vector<float> YSizes;
        std::vector<float> XPositions;
        std::vector<float> YPositions;
    };

    struct CameraScreenSizeBounds
    {
        float XSize;
        float YSize;
        float XPosition;
        float YPosition;
    };

    class CameraManager
    {
    public:
        unsigned int CreateCamera(const Pillow::Transform* cameraTransform);
        void RemoveCamera(unsigned int cameraID);

        void ToggleCamera(unsigned int cameraID, bool isActive);
        void SetCameraProjection(unsigned int cameraID, ProjectionType projectionType);
        void SetCameraScreenPosition(unsigned int cameraID, float xPosition, float yPosition);
        void SetCameraScreenSize(unsigned int cameraID, float xSize, float ySize);

        bool IsCameraActive(unsigned int cameraID) { return m_CameraStorage.Active[cameraID]; };
        ProjectionType GetCameraProjectionType(unsigned int cameraID) { return m_CameraStorage.ProjectionTypes[cameraID]; };
        const Pillow::Transform* GetCameraTransform(unsigned int cameraID) { return m_CameraStorage.Transforms[cameraID]; };
        CameraScreenSizeBounds GetCameraScreen(unsigned int cameraID);
        
        std::vector<unsigned int> GetAllCameras() { return m_Cameras; };
        unsigned int GetCameraCount() { return m_CameraCount; };

    private:
        Quilt::Cameras m_CameraStorage;
        unsigned int m_CameraCount = 0;
        std::vector<unsigned int> m_Cameras;
        std::vector<unsigned int> m_RemovedCameras;

        //TODO: Track the ammount of cameras currenctly active prefrably having a max of 10 cameras but having it toggleable would be nice
    };
}