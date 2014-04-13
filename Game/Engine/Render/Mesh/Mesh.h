#pragma once
#ifndef __RENDER_MESH_H__
#define __RENDER_MESH_H__

#include "Render/Mesh/MeshTypes.h"
#include "Render/Mesh/MeshBase.h"
#include "Render/Buffers/Vertex.h"
#include "Render/Buffers/VertexBuffer.h"
#include "Render/Buffers/IndexBuffer.h"
#include "Render/Buffers/VertexArray.h"

#if defined(THOT_PROFILER_ENABLE)
#   include "Kernel\Time\Timer.h"
#endif 

namespace MeshFactory
{
    template< class TVertexType, class TIndexType>
    IMesh*      CreateMesh  ( const thVector<TVertexType>& vertices, const thVector<TIndexType>& indices );
}



template<class TVertexType, class TIndexType>
class CMesh: public IMesh
{
friend IMesh* MeshFactory::CreateMesh<>( const thVector<TVertexType>& vertices, const thVector<TIndexType>& indices );
//*********************************************
//            CONSTR/DESTR
//*********************************************
protected:
     CMesh();
    ~CMesh();

//*********************************************
//            INTERFACE
//*********************************************
public:
    typedef RenderLowLevel::CVertexArray< TVertexType, TIndexType >    TVertexArray;

virtual     void            OnDraw              ( )const                                    override;
            TVertexArray    GetVertexArray      ( ){ return m_vertexArray;}


//*********************************************
//            HELPERS
//*********************************************
protected:
virtual     Bool        CreateBuffers       ( const void* vertices, const void* indices )           override;



//*********************************************
//            MEMBERS
//*********************************************
protected:
        
        TVertexArray        m_vertexArray;
};


namespace MeshFactory
{
    //factory functions
    template< class TVertexType, class TIndexType>
    THOT_NO_INLINE IMesh*      CreateMesh  ( const thVector<TVertexType>& vertices, const thVector<TIndexType>& indices )
    {
        typedef CMesh<TVertexType,TIndexType> TMesh; 
        IMesh* mesh = THOT_NEW TMesh;
        mesh->CreateBuffers( &vertices, & indices );    
        return mesh;
    }



#define DECLARE_INSTANTIATE_MESH_FACTORY_FUNC(__vertexType, __indexType)\
template RENDER_API IMesh* CreateMesh<__vertexType,__indexType>( const thVector<__vertexType>& vertices, const thVector<__indexType>& indices  )

    DECLARE_INSTANTIATE_MESH_FACTORY_FUNC(RenderLowLevel::SVertex_P,u8);
    DECLARE_INSTANTIATE_MESH_FACTORY_FUNC(RenderLowLevel::SVertex_P,u16);
    DECLARE_INSTANTIATE_MESH_FACTORY_FUNC(RenderLowLevel::SVertex_P,u32);
    
    DECLARE_INSTANTIATE_MESH_FACTORY_FUNC(RenderLowLevel::SVertex_PN,u8);
    DECLARE_INSTANTIATE_MESH_FACTORY_FUNC(RenderLowLevel::SVertex_PN,u16);
    DECLARE_INSTANTIATE_MESH_FACTORY_FUNC(RenderLowLevel::SVertex_PN,u32);

    DECLARE_INSTANTIATE_MESH_FACTORY_FUNC(RenderLowLevel::SVertex_PNC,u8);
    DECLARE_INSTANTIATE_MESH_FACTORY_FUNC(RenderLowLevel::SVertex_PNC,u16);
    DECLARE_INSTANTIATE_MESH_FACTORY_FUNC(RenderLowLevel::SVertex_PNC,u32);

    DECLARE_INSTANTIATE_MESH_FACTORY_FUNC(RenderLowLevel::SVertex_PNTB4,u8);
    DECLARE_INSTANTIATE_MESH_FACTORY_FUNC(RenderLowLevel::SVertex_PNTB4,u16);
    DECLARE_INSTANTIATE_MESH_FACTORY_FUNC(RenderLowLevel::SVertex_PNTB4,u32);

}

#include "Mesh.inl"


#endif /*__RENDER_MESH_H__*/