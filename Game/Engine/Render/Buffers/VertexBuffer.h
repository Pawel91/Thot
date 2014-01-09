#ifndef __RENDER_VERTEX_BUFFER_H__
#define __RENDER_VERTEX_BUFFER_H__

#include "Kernel/Utils/RefCounter.h"
#include "Render/RenderGL.h"
#include "BufferTypes.h"
#include "VertexTypes.h"
#include "Vertex.h"



namespace RenderLowLevel
{


/*
    Wrapper class for a vertex buffer object;
    T must be a Vertex class;
*/
template <class T>  
class CVertexBufferObject
{

template<class T, class V> friend class CVertexArray;

public:
static const TVertexBufferHandle    ms_invalidVBOHandle = 0xFFFFFFFF;
static const TVertexBufferHandle    ms_defaultHandle = 0;

//Make construction protected:
public:
    CVertexBufferObject( );
    CVertexBufferObject( const CVertexBufferObject<T>& other );
    const CVertexBufferObject<T>& operator = ( const CVertexBufferObject<T>& other );

public:
    ~CVertexBufferObject( );

public:
    u32                     GetSize                 ( )const;
    Bool                    IsValid                 ( )const;
    TVertexBufferHandle     GetNativeHandle         (){ return m_handle;}

    /*
        RETURNS A BINDED VERTEX BUFFER OBJECT WITH ALL VERTEX ARRAY ATTRIBUTES ENABLED
    */
static CVertexBufferObject<T> Create( const thVector<T>& vertexBufferRaw, EBufferUsage usage = E_BUFFER_USAGE_STATIC_DRAW );

protected:

    void                Bind                    ( )const;
    void                Unbind                  ( )const;
    Bool                DrawArrays              ( eGeometricPrimitive primitive, u32 startIndex, u32 count )const;
    void                InitFromOther           ( const CVertexBufferObject<T>& other );
    void                Destroy                 ( );
    void                UpdateBuffer            ( const thVector<T>& newBuffer );

/*
    RETURNS A HANDLE TO A BINDED VERTEX BUFFER OBJECT
*/
static TVertexBufferHandle CreateVertexBufferObjectHandle( const thVector<T>& vertexBufferRaw, EBufferUsage usage );

private:
    CRefCounter*            m_refCounter;
    TVertexBufferHandle     m_handle;
};



} // namespace RenderLowLevel


#include "VertexBuffer.inl"


#endif /*__RENDER_VERTEX_BUFFER_H__*/