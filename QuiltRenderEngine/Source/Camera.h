#pragma once

#include <SparseSet.h>
#include <Transform.h>
#include <vector>

namespace Quilt
{
    enum class Projection
    {
        Orthographic,
        Perspective
    };

    struct Cameras
    {
        std::vector<bool> Active;
        std::vector<Projection> ProjectionTypes;

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

    struct CameraScreenPosition
    {
        float XPositionPercent;
        float YPositionPercent;
        float XSizePercent;
        float YSizePercent;
    };

    struct Camera
    {
        bool IsActive;
        Projection ProjectionType;

        glm::mat4 ViewMatrix;
        glm::mat4 ProjectionMatrix;
        float AspectRatio;

        CameraScreenSizeBounds ScreenBounds;
        CameraScreenPosition ScreenPosition;

        float FOV;
        float Zoom;
    };


    class CameraManager
    {
    public:
        unsigned int CreateCamera();
        void RemoveCamera(unsigned int cameraID);

        void ToggleCamera(unsigned int cameraID, bool isActive);
        void SetCameraProjection(unsigned int cameraID, Projection projectionType);
        void SetCameraScreenPosition(unsigned int cameraID, float xPosition, float yPosition);
        void SetCameraScreenSize(unsigned int cameraID, float xSize, float ySize);
        void SetCameraFOV(unsigned int cameraID, float fov);
        void SetCameraZoom(unsigned int cameraID, float zoom);

        void UpdateCameraTransform(unsigned int cameraID, Pillow::Transform& transform);
        void UpdateAspectRatio(unsigned int cameraID);

        void SetWindowWidth(int width);
        void SetWindowHeight(int height);

        bool IsCameraActive(unsigned int cameraID) { return m_CameraStorage.GetData(cameraID).IsActive; };
        Projection GetCameraProjectionType(unsigned int cameraID) { return m_CameraStorage.GetData(cameraID).ProjectionType; };
        CameraScreenSizeBounds GetCameraScreen(unsigned int cameraID) { return m_CameraStorage.GetData(cameraID).ScreenBounds; };
        
        const std::vector<Quilt::Camera>& GetAllCameras() { return m_CameraStorage.GetAllData(); };
        unsigned int GetCameraCount() { return m_CameraCount; };

    private:
        Frame::SparseSet<Quilt::Camera> m_CameraStorage;

        unsigned int m_CameraCount = 0;
        std::vector<unsigned int> m_RemovedCameras;

        int m_WindowWidth = 0;
        int m_WindowHeight = 0;
        float m_Aspect = 0;

        //TODO: Track the ammount of cameras currenctly active prefrably having a max of 10 cameras but having it toggleable would be nice
    };
}