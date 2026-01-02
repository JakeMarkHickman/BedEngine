#include "Camera.h"

unsigned int Quilt::CameraManager::CreateCamera(const Pillow::Transform* cameraTransform)
{
    unsigned int cameraID;

    if(!m_RemovedCameras.empty())
    {
        cameraID = m_RemovedCameras.back();
        m_Cameras.push_back(cameraID);
        m_RemovedCameras.pop_back();

        return cameraID;
    }

    cameraID = m_CameraCount;
    m_CameraCount++;

    m_Cameras.push_back(cameraID);

    m_CameraStorage.Active.resize(m_CameraCount);
    m_CameraStorage.ProjectionTypes.resize(m_CameraCount);
    m_CameraStorage.Transforms.resize(m_CameraCount);
    m_CameraStorage.XSizes.resize(m_CameraCount);
    m_CameraStorage.YSizes.resize(m_CameraCount);
    m_CameraStorage.XPositions.resize(m_CameraCount);
    m_CameraStorage.YPositions.resize(m_CameraCount);

    m_CameraStorage.Transforms[cameraID] = cameraTransform;
    
    return cameraID;
}

void Quilt::CameraManager::ToggleCamera(unsigned int cameraID, bool isActive)
{
    m_CameraStorage.Active[cameraID] = isActive;
}

void Quilt::CameraManager::SetCameraProjection(unsigned int cameraID, Quilt::ProjectionType projectionType)
{
    m_CameraStorage.ProjectionTypes[cameraID] = projectionType;
}

void Quilt::CameraManager::SetCameraScreenPosition(unsigned int cameraID, float xPosition, float yPosition)
{
    m_CameraStorage.XPositions[cameraID] = xPosition;
    m_CameraStorage.YPositions[cameraID] = yPosition;
}

void Quilt::CameraManager::SetCameraScreenSize(unsigned int cameraID, float xSize, float ySize)
{
    m_CameraStorage.XSizes[cameraID] = xSize;
    m_CameraStorage.YSizes[cameraID] = ySize;
}

Quilt::CameraScreenSizeBounds Quilt::CameraManager::GetCameraScreen(unsigned int cameraID)
{
    CameraScreenSizeBounds cameraScreen;

    cameraScreen.XSize = m_CameraStorage.XSizes[cameraID];
    cameraScreen.YSize = m_CameraStorage.YSizes[cameraID];

    cameraScreen.XPosition = m_CameraStorage.XPositions[cameraID];
    cameraScreen.YPosition = m_CameraStorage.YPositions[cameraID];

    return cameraScreen;
}