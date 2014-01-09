
namespace RenderLowLevel
{

#ifndef DECLARE_DEFAULT_CONSTRUCTOR_LIST
#define DECLARE_DEFAULT_CONSTRUCTOR_LIST     \
:m_refCounter   (NULL)                      \
,m_handle       (ms_invalidVAOHandle)

#else
#   error DECLARE_DEFAULT_CONSTRUCTOR allready defined
#endif /*DECLARE_DEFAULT_CONSTRUCTOR_LIST*/


template < class TVertexType, class TIndexType>
 THOT_FORCE_INLINE CVertexArray< TVertexType, TIndexType >::CVertexArray()
     DECLARE_DEFAULT_CONSTRUCTOR_LIST
 {
     m_refCounter = THOT_NEW CRefCounter;
     m_refCounter->AddRef();
 }

 template < class TVertexType, class TIndexType>
 THOT_FORCE_INLINE CVertexArray< TVertexType, TIndexType >::CVertexArray( const CVertexArray<TVertexType, TIndexType>& other )
     DECLARE_DEFAULT_CONSTRUCTOR_LIST
 {
    InitFromOther(other);
 }

 template < class TVertexType, class TIndexType>
 THOT_FORCE_INLINE const CVertexArray<TVertexType, TIndexType>& CVertexArray< TVertexType, TIndexType >::operator = ( const CVertexArray<TVertexType, TIndexType>& other )
 {
    InitFromOther( other );
    return *this;
 }






#undef DECLARE_DEFAULT_CONSTRUCTOR_LIST

 template < class TVertexType, class TIndexType>
THOT_FORCE_INLINE CVertexArray< TVertexType, TIndexType >::~CVertexArray()
{
    Destroy();
}


template < class TVertexType, class TIndexType>
THOT_FORCE_INLINE void CVertexArray< TVertexType, TIndexType>::Bind( )const
{
RENDER_GUARD_BLOCK
    gl::BindVertexArray( m_handle );
}


template < class TVertexType, class TIndexType>
THOT_FORCE_INLINE void CVertexArray< TVertexType, TIndexType>::Unbind( )const
{
RENDER_GUARD_BLOCK
    gl::BindVertexArray( ms_defaultVAOHandle );
}

template < class TVertexType, class TIndexType>
THOT_FORCE_INLINE Bool CVertexArray< TVertexType, TIndexType>::IsValid( )const
{
    return m_handle != ms_invalidVAOHandle;
}

template < class TVertexType, class TIndexType>
THOT_FORCE_INLINE const CVertexBufferObject<TVertexType>& CVertexArray< TVertexType, TIndexType>::GetVertexBuffer( )const
{
    return m_vertexBuffer;
}


template < class TVertexType, class TIndexType>
THOT_FORCE_INLINE CVertexBufferObject<TVertexType>& CVertexArray< TVertexType, TIndexType>::GetVertexBuffer( )
{
    return m_vertexBuffer;
}

template < class TVertexType, class TIndexType>
THOT_FORCE_INLINE const CIndexBufferObject<TIndexType>& CVertexArray< TVertexType, TIndexType>::GetIndexBuffer( )const
{
    return m_indexBuffer;
}


template < class TVertexType, class TIndexType>
THOT_FORCE_INLINE CIndexBufferObject<TIndexType>& CVertexArray< TVertexType, TIndexType>::GetIndexBuffer( )
{
    return m_indexBuffer;
}


template < class TVertexType, class TIndexType>
THOT_FORCE_INLINE void  CVertexArray< TVertexType, TIndexType>::InitFromOther( const CVertexArray<TVertexType,TIndexType>& other )
{
    THOT_ASSERT(other.m_refCounter!=NULL);
    if( this == &other )
    {
        return;
    }

    Destroy();

    m_vertexBuffer = other.m_vertexBuffer;
    m_indexBuffer = other.m_indexBuffer;
    m_handle = other.m_handle;
    m_refCounter = other.m_refCounter;
    m_refCounter->AddRef();
}


template < class TVertexType, class TIndexType>
THOT_FORCE_INLINE void  CVertexArray< TVertexType, TIndexType>::Destroy( )
{
RENDER_GUARD_BLOCK

    if( m_refCounter && m_refCounter->Release() == 0 )
    {
        THOT_DELETE(m_refCounter);
        if( m_handle != ms_invalidVAOHandle )
        {
            gl::DeleteVertexArrays(1, &m_handle);
            m_handle = ms_invalidVAOHandle;
        }
    }
}


template < class TVertexType, class TIndexType>
THOT_FORCE_INLINE CVertexArray<TVertexType, TIndexType> CVertexArray< TVertexType, TIndexType>::Create(  const thVector<TVertexType>& vertices
                                                ,const thVector<TIndexType>& indices
                                                ,EBufferUsage usage = E_BUFFER_USAGE_STATIC_DRAW
                                                )
{
    // create a array buffer object
    TVertexArrayHandle handle;
    gl::GenVertexArrays( 1, &handle );
    gl::BindVertexArray( handle );

    // wrap array buffer handle;
    CVertexArray<TVertexType, TIndexType> vertexArrayObject;
    vertexArrayObject.m_handle = handle;

    // create vertex and index buffer which are now state of vertex array object;
    vertexArrayObject.m_vertexBuffer    = CVertexBufferObject<TVertexType>::Create( vertices, usage );
    vertexArrayObject.m_indexBuffer     = CIndexBufferObject<TIndexType>::Create( indices, usage );

    vertexArrayObject.Unbind();
    return vertexArrayObject;
}


template < class TVertexType, class TIndexType>
THOT_FORCE_INLINE Bool CVertexArray< TVertexType, TIndexType>::DrawElements( eGeometricPrimitive primitive, u32 count  )const
{
    Bind();
    m_vertexBuffer.Bind();
    m_indexBuffer.Bind();

    Bool rez = m_indexBuffer.DrawElements( primitive, count );
    THOT_ASSERT(rez);
    return rez;
    Unbind();
}


template < class TVertexType, class TIndexType>
THOT_FORCE_INLINE Bool CVertexArray< TVertexType, TIndexType>::DrawArrays ( eGeometricPrimitive primitive, u32 startIndex, u32 count )const
{
    Bind();
    return m_vertexBuffer.DrawArrays( primitive, startIndex, count );
    Unbind();
}



}//namespace RenderLowLevel