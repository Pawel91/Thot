#pragma once
#ifndef __RENDER_INDEX_BUFFER_H__
#define __RENDER_INDEX_BUFFER_H__

#include "Render\RenderGL.h"
#include "VertexTypes.h"
#include "BufferTypes.h"

/*
    
*/
namespace RenderLowLevel
{

template< class TIndexType >
class CIndexBufferObject
{
//vertex array is our friend ;))
template<class U, class TIndexType> friend class CVertexArray; 

public:
    CIndexBufferObject( );
    CIndexBufferObject( const CIndexBufferObject<TIndexType>& other );
    ~CIndexBufferObject( );
    const CIndexBufferObject<TIndexType>& operator = ( const CIndexBufferObject<TIndexType>& other );
public:
        void                            Bind            ( )const;
        void                            Unbind          ( )const;
        u32                             GetSize         ( )const;
        Bool                            IsValid         ( )const;
        TIndexType*                     MapBuffer       ( EBufferAcces acces = E_BUFFER_ACCES_READ_ONLY );
        

static  CIndexBufferObject<TIndexType>  Create          ( const thVector<TIndexType>& bufferData, EBufferUsage usage = E_BUFFER_USAGE_STATIC_DRAW );

protected:
    Bool                DrawElements    ( eGeometricPrimitive primitive, u32 count  )const;

    void                InitFromOther   ( const CIndexBufferObject<TIndexType>& other );
    void                Destroy         ( );
    
static    TIndexBufferHandle  CreateIndexBufferObjectHandle( const thVector<TIndexType>& bufferData, EBufferUsage usage );

private:
static const TIndexBufferHandle ms_invalidIBHandle = 0xFFFFFFFF;
static const TIndexBufferHandle ms_defaultIBHandle = 0;
static const TIndexType ms_dummyIndexType = 0;
        TIndexBufferHandle          m_handle;
        CRefCounter*                m_refCounter;
};


}// namespace RenderLowLevel

#include "IndexBuffer.inl"


#endif /*__RENDER_INDEX_BUFFER_H__*/