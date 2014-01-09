#pragma once
#ifndef __RENDER_MESH_BASE_H__
#define __RENDER_MESH_BASE_H__

#include "MeshTypes.h"
#include "..//Buffers/VertexBuffer.h"
#include "..//Buffers/VertexArray.h"
#include "Render/Materials/Material.h"

class IMesh;

namespace MeshFactory
{
    template< class TVertexType, class TIndexType>
    IMesh*      CreateMesh  ( const thVector<TVertexType>& vertices, const thVector<TIndexType>& indices );
}


class RENDER_API IMesh
{
template<class TVertexType,class TIndexType> 
friend IMesh* MeshFactory::CreateMesh<>( const thVector<TVertexType>& vertices, const thVector<TIndexType>& indices );
friend class CSceneRenderableNode;
//*********************************************
//            CONSTRUCTION/DESTRUCTION
//*********************************************
protected:
        IMesh   ();
public:
virtual ~IMesh  () =0;


//*********************************************
//            INTERFACE
//*********************************************
public:

    virtual     void                OnDraw              ()const                             = 0;
                void                SetPrimitiveType    ( EMeshPrimitive primitive );     
                void                SetMaterial         ( const CMaterial& material );
                const CMaterial&    GetMaterial         ( ){ return m_material;}



//*********************************************
//            HELPERS
//*********************************************
protected:
// vertices and indices must be cast to specific types in derivate class
virtual     Bool        CreateBuffers ( const void* vertices, const void* indices ) = 0;


//*********************************************
//            MEMBERS
//*********************************************
protected:
    EMeshPrimitive      m_ePrimitiveType;
    CMaterial           m_material;         
};


THOT_FORCE_INLINE IMesh::IMesh()
    :m_ePrimitiveType (EMeshPrimitive::E_MESH_PRIMITIVE_NONE)
{
    
}


inline IMesh::~IMesh(){}

THOT_FORCE_INLINE void IMesh::SetPrimitiveType    ( EMeshPrimitive primitive )
{
    m_ePrimitiveType = primitive;
}


THOT_FORCE_INLINE void IMesh::SetMaterial ( const CMaterial& material )
{
    m_material = material;
}

#endif /*__RENDER_MESH_BASE_H__*/