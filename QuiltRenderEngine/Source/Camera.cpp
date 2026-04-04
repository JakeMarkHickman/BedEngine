#include "Camera.h"
#include <SleepTrace.h>

unsigned int Quilt::CameraManager::CreateCamera()
{
    unsigned int cameraID;

    Quilt::Camera newCamera;

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

void Quilt::CameraManager::UpdateCameraTransform(unsigned int cameraID, Pillow::Transform& transform)
{
    float left = -m_CameraStorage.GetData(cameraID).Zoom * m_CameraStorage.GetData(cameraID).AspectRatio;
    float right = m_CameraStorage.GetData(cameraID).Zoom * m_CameraStorage.GetData(cameraID).AspectRatio;
    float bottom = -m_CameraStorage.GetData(cameraID).Zoom;
    float top = m_CameraStorage.GetData(cameraID).Zoom;

    glm::vec3 camPos = glm::vec3(transform.Position.x, transform.Position.y, transform.Position.z);
    glm::vec3 targetPos = camPos + glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 upVec = glm::vec3(0.0f, 1.0f, 0.0f);

    m_CameraStorage.GetData(cameraID).ProjectionMatrix = glm::orthoLH(left, right, bottom, top, -1.0f, 500.0f);
    m_CameraStorage.GetData(cameraID).ViewMatrix = glm::lookAtLH(camPos, targetPos, upVec);
}

void Quilt::CameraManager::UpdateAspectRatio(unsigned int cameraID)
{
    m_CameraStorage.GetData(cameraID).ScreenPosition.XSizePercent = m_CameraStorage.GetData(cameraID).ScreenBounds.XSize * m_WindowWidth;
    m_CameraStorage.GetData(cameraID).ScreenPosition.YSizePercent = m_CameraStorage.GetData(cameraID).ScreenBounds.YSize * m_WindowHeight;

    m_CameraStorage.GetData(cameraID).ScreenPosition.XPositionPercent = m_CameraStorage.GetData(cameraID).ScreenBounds.XPosition * m_WindowWidth;
    m_CameraStorage.GetData(cameraID).ScreenPosition.YPositionPercent = m_CameraStorage.GetData(cameraID).ScreenBounds.YPosition * m_WindowHeight;

    m_CameraStorage.GetData(cameraID).AspectRatio = m_CameraStorage.GetData(cameraID).ScreenPosition.XSizePercent / m_CameraStorage.GetData(cameraID).ScreenPosition.YSizePercent;
}

void Quilt::CameraManager::SetWindowWidth(int width)
{
    m_WindowWidth = width;
}

void Quilt::CameraManager::SetWindowHeight(int height)
{
    m_WindowHeight = height;
}