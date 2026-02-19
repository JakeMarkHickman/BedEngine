#include "Camera.h"
#include <SleepTrace.h>

unsigned int Quilt::CameraManager::CreateCamera(const Pillow::Transform* cameraTransform)
{
    unsigned int cameraID;

    Quilt::Camera newCamera;
    newCamera.Transform = cameraTransform;

    if(!m_RemovedCameras.empty())
    {
        cameraID = m_RemovedCameras.back();
        m_RemovedCameras.pop_back();
    }
    else
    {
        cameraID = m_CameraCount;
        m_CameraCount++;
    }

    m_CameraStorage.Insert(cameraID, newCamera);
    
    return cameraID;
}

void Quilt::CameraManager::RemoveCamera(unsigned int cameraID)
{
    m_CameraStorage.Remove(cameraID);
    m_RemovedCameras.push_back(cameraID);
}

void Quilt::CameraManager::ToggleCamera(unsigned int cameraID, bool isActive)
{
    m_CameraStorage.GetData(cameraID).IsActive = isActive;
}

void Quilt::CameraManager::SetCameraProjection(unsigned int cameraID, Quilt::Projection projectionType)
{
    m_CameraStorage.GetData(cameraID).ProjectionType = projectionType;
}

void Quilt::CameraManager::SetCameraScreenPosition(unsigned int cameraID, float xPosition, float yPosition)
{
    CameraScreenSizeBounds& bounds = m_CameraStorage.GetData(cameraID).ScreenBounds;

    bounds.XPosition = xPosition;
    bounds.YPosition = yPosition;
}

void Quilt::CameraManager::SetCameraScreenSize(unsigned int cameraID, float xSize, float ySize)
{
    CameraScreenSizeBounds& bounds = m_CameraStorage.GetData(cameraID).ScreenBounds;

    bounds.XSize = xSize;
    bounds.YSize = ySize;
}

void Quilt::CameraManager::SetCameraFOV(unsigned int cameraID, float fov)
{
    m_CameraStorage.GetData(cameraID).FOV = fov;
}

void Quilt::CameraManager::SetCameraZoom(unsigned int cameraID, float zoom)
{
    m_CameraStorage.GetData(cameraID).Zoom = zoom;
}