#include "2DRenderComponent.h"

Bed::TwoDimensionalRender::TwoDimensionalRender(Bed::Texture* texture, int zOrder)
{
    m_Texture = texture;
    m_ZOrder = zOrder;
}