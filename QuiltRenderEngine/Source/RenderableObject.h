#pragma once

#include <vector>
#include <SparseSet.h>

//TODO: This will be outside the lib in Quilts SDK
namespace Quilt
{
    //TODO: information that is used on how to find and update something is used in here
    struct RenderableObject
    {
        unsigned int BatchID;
        uint64_t DrawInfoOffset;

        uint64_t VertexOffset;
        uint64_t IndexOffset;
        uint64_t VertexCount;
        uint64_t IndexCount;

        unsigned int MeshHandle;
    };

    class RenderableManager
    {
    public:
        void CreateRenderableObject(uint64_t entityID, RenderableObject object);
        Quilt::RenderableObject& GetRenderableObject(uint64_t entityID);

    private:
        Frame::SparseSet<Quilt::RenderableObject> m_EntityLink;

    };
}