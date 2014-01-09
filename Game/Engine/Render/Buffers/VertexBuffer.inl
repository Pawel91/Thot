
namespace RenderLowLevel
{

#ifndef DECLARE_DEFAULT_CONSTRUCTOR_LIST
#define DECLARE_DEFAULT_CONSTRUCTOR_LIST    \
:m_handle       ( ms_invalidVBOHandle )        \
,m_refCounter   ( NULL )
#else
#   error DECLARE_DEFAULT_CONSTRUCTOR_LIST is allready defined
#endif /*DECLARE_DEFAULT_CONSTRUCTOR_LIST*/



template<class T>
THOT_FORCE_INLINE CVertexBufferObject<T>::CVertexBufferObject()
    DECLARE_DEFAULT_CONSTRUCTOR_LIST
{
    m_refCounter = THOT_NEW CRefCounter;
    m_refCounter->AddRef();
}

template<class T>
THOT_FORCE_INLINE CVertexBufferObject<T>::CVertexBufferObject( const CVertexBufferObject<T>& other )
    DECLARE_DEFAULT_CONSTRUCTOR_LIST
{
    InitFromOther(other);
}

#undef DECLARE_DEFAULT_CONSTRUCTOR_LIST

template <class T>
THOT_FORCE_INLINE const CVertexBufferObject<T>& CVertexBufferObject<T>::operator = ( const CVertexBufferObject<T>& other )
{
    InitFromOther(other);
    return (*this);
}

template<class T>
THOT_FORCE_INLINE void CVertexBufferObject<T>::InitFromOther( const CVertexBufferObject<T>& other )
{
    THOT_ASSERT(other.m_refCounter!=NULL);
    if( this == &other )
    {
        return;
    }

    Destroy();

    m_handle = other.m_handle;
    m_refCounter = other.m_refCounter;
    m_refCounter->AddRef();
}


template<class T>
THOT_FORCE_INLINE CVertexBufferObject<T>::~CVertexBufferObject( )
{
    //THOT_COMPILE_ASSERT2( sizeof(CVertexBufferObject<T>) == (sizeof(TVertexBufferHandle) + sizeof(CRefCounter*) ), "Wrapper class must be same size as the wrapped type" );
    Destroy();
}

template<class T>
THOT_FORCE_INLINE void CVertexBufferObject<T>::Destroy( )
{
RENDER_GUARD_BLOCK

    if( m_refCounter && m_refCounter->Release() == 0 )
    {
        THOT_DELETE(m_refCounter);
        if( m_handle != ms_invalidVBOHandle )
        {
            gl::DeleteBuffers(1, &m_handle);
            m_handle = ms_invalidVBOHandle;
        }
    }
}


template <class T>
THOT_FORCE_INLINE void CVertexBufferObject<T>::Bind( )const
{
RENDER_GUARD_BLOCK

    gl::BindBuffer( gl::ARRAY_BUFFER, m_handle );
}

template<class T>
THOT_FORCE_INLINE void CVertexBufferObject<T>::Unbind( )const
{
RENDER_GUARD_BLOCK

    glBindBuffer( GL_ARRAY_BUFFER, ms_defaultHandle );
}


template<class T>
THOT_FORCE_INLINE Bool CVertexBufferObject<T>::DrawArrays ( eGeometricPrimitive primitive, u32 startIndex, u32 count )const
{
RENDER_GUARD_BLOCK
    //Bind();
    u32 size = GetSize();
    if( startIndex + count > size )
    {
        return false;
    }
    
    gl::DrawArrays( gl::GetEnum(primitive), startIndex, count );

    return true;
}


template <class T>
THOT_FORCE_INLINE u32 CVertexBufferObject<T>::GetSize ( )const
{
RENDER_GUARD_BLOCK
    Bind();
    GLint bufferSize = 0;
    gl::GetBufferParameteriv( gl::ARRAY_BUFFER, gl::BUFFER_SIZE, &bufferSize );
    u32 realSize = bufferSize/sizeof(T);
    return realSize;
}

template< class T >
THOT_FORCE_INLINE TVertexBufferHandle CVertexBufferObject<T>::CreateVertexBufferObjectHandle( const thVector<T>& vertexBufferRaw, EBufferUsage usage )
{
RENDER_GUARD_BLOCK

    TVertexBufferHandle handle = 0;
    gl::GenBuffers( 1, &handle );
    gl::BindBuffer( gl::ARRAY_BUFFER, handle);
    gl::BufferData( gl::ARRAY_BUFFER, ThNumericCast<GLsizeiptr>(vertexBufferRaw.Size() * sizeof(T)), vertexBufferRaw.GetData(), gl::GetEnum(usage) );
    CVertexDescriptor<T>::VertexAttributePointerAllMembers();

    return handle;  
}



template<class T>
THOT_FORCE_INLINE CVertexBufferObject<T> CVertexBufferObject<T>::Create( const thVector<T>& vertexBufferRaw, EBufferUsage usage = E_BUFFER_USAGE_STATIC_DRAW )
{
RENDER_GUARD_BLOCK

    CVertexBufferObject<T> vbo;
    vbo.m_handle = CreateVertexBufferObjectHandle( vertexBufferRaw, usage );
    return vbo;
}

template<class T>
THOT_FORCE_INLINE Bool CVertexBufferObject<T>::IsValid( )const
{
    return m_handle != ms_invalidVBOHandle;
}

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE void CVertexBufferObject<T>::UpdateBuffer( const thVector<T>& newBuffer )
{
    gl::BindBuffer(gl::ARRAY_BUFFER, handle);
    T* oldBuffer =  (T*) gl::MapBuffer( gl::ARRAY_BUFFER, gl::WRITE_ONLY);
    THOT_ASSERT(GetSize() == ThNumericCast<u32>(newBuffer.GetSize()));

    u32 size = ThNumericCast<u32>( newBuffer.GetSize() );
    memcpy(oldBuffer, newBuffer.GetData(), size * sizeof(T) );

    gl::UnmapBuffer(gl::ARRAY_BUFFER);
}


}// namespace RenderLowLevel
