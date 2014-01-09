#pragma once
#ifndef __RENDER_VERTEX_ARRAY_H__
#define __RENDER_VERTEX_ARRAY_H__

#include "Render\RenderGL.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!QUESTION : buffer objects should have bind/unbind members PROTECTED..???
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


namespace RenderLowLevel
{

typedef u32 TVertexArrayHandle;

template<class TVertexType, class TIndexType>
class CVertexArray
{
//*********************************************
//            CONSTR/DESTR
//*********************************************
public:


    CVertexArray();
    ~CVertexArray();
    CVertexArray( const CVertexArray<TVertexType, TIndexType>& other );
    const CVertexArray<TVertexType, TIndexType>& operator = ( const CVertexArray<TVertexType, TIndexType>& other );


//*********************************************
//            INTERFACE
//*********************************************
public:
    typedef CVertexBufferObject<TVertexType>        TVBO; // vertex buffer object
    typedef CIndexBufferObject<TIndexType>          TIBO; // index buffer object


    //[TODO] make bind and unbind private and move here draw functions from vertex and index buffer 


    const TVBO&                 GetVertexBuffer             ( )const;
    TVBO&                       GetVertexBuffer             ( );

    const TIBO&                 GetIndexBuffer              ( )const;
    TIBO&                       GetIndexBuffer              ( );

    Bool                        IsValid                     ( )const;

    Bool                        DrawElements                ( eGeometricPrimitive primitive, u32 count  )const;
    Bool                        DrawArrays                  ( eGeometricPrimitive primitive, u32 startIndex, u32 count )const;

    
    // returns a binded vertex array; or maybe it shold be returned unbinded :-??
static    CVertexArray<TVertexType, TIndexType>       Create(   const thVector<TVertexType>& vertices
                                                                ,const thVector<TIndexType>& indices
                                                                ,EBufferUsage usage = E_BUFFER_USAGE_STATIC_DRAW
                                                                );

//*********************************************
//            HELPERS
//*********************************************
protected:
    void            Bind                ( )const;
    void            Unbind              ( )const;
    void            InitFromOther       ( const CVertexArray<TVertexType,TIndexType>& other );
    void            Destroy             ( );


//*********************************************
//            MEMBERS
//*********************************************
protected:
    static const TVertexArrayHandle ms_invalidVAOHandle = 0xFFFFFFFF;
    static const TVertexArrayHandle ms_defaultVAOHandle = 0;

    CRefCounter*                    m_refCounter;
    TVertexArrayHandle              m_handle;
    TVBO                            m_vertexBuffer;
    TIBO                            m_indexBuffer;
};
}// namaspace RenderLowLevel

#include "VertexArray.inl"



#endif /*__RENDER_VERTEX_ARRAY_H__*/