

namespace RenderLowLevel
{

#ifndef DECLARE_DEFAULT_CONSTRUCTOR_LIST

#   define DECLARE_DEFAULT_CONSTRUCTOR_LIST \
    :m_handle       (ms_invalidIBHandle)    \
    ,m_refCounter   ( NULL )

#else
#   error DECLARE_DEFAULT_CONSTRUCTOR_LIST is allready defined
#endif /*DECLARE_DEFAULT_CONSTRUCTOR_LIST*/


template<class TIndexType> 
THOT_FORCE_INLINE CIndexBufferObject<TIndexType>::CIndexBufferObject( )
    DECLARE_DEFAULT_CONSTRUCTOR_LIST
{
    m_refCounter = THOT_NEW CRefCounter ;
    m_refCounter->AddRef();
}


template<class TIndexType>
THOT_FORCE_INLINE CIndexBufferObject<TIndexType>::CIndexBufferObject( const CIndexBufferObject<TIndexType>& other )
    DECLARE_DEFAULT_CONSTRUCTOR_LIST
{
    THOT_COMPILE_ASSERT2( sizeof(TIndexType) == 1 || sizeof(TIndexType) == 2 || sizeof(TIndexType) == 4, "CIndexBufferObject must be specialized only with u8, u16 or u32" );
    InitFromOther( other );
}

#undef DECLARE_DEFAULT_CONSTRUCTOR_LIST

template< class TIndexType>
THOT_FORCE_INLINE const CIndexBufferObject<TIndexType>& CIndexBufferObject<TIndexType>::operator = ( const CIndexBufferObject<TIndexType>& other )
{
    InitFromOther(other);
    return *this;
}


template<class TIndexType> 
THOT_FORCE_INLINE CIndexBufferObject<TIndexType>::~CIndexBufferObject()
{
    Destroy();
}

template< class TIndexType>
void CIndexBufferObject<TIndexType>::Destroy( )
{
RENDER_GUARD_BLOCK

    if( m_refCounter && m_refCounter->Release() == 0 )
    {
        THOT_DELETE(m_refCounter);
        if( m_handle != ms_invalidIBHandle  )
        {
            gl::DeleteBuffers(1, &m_handle);
            m_handle = ms_invalidIBHandle;
        }
    }
}

template<class TIndexType>
u32 CIndexBufferObject<TIndexType>::GetSize( )const
{
RENDER_GUARD_BLOCK
    Bind();
    GLint bytes = 0;
    gl::GetBufferParameteriv( gl::ELEMENT_ARRAY_BUFFER, gl::BUFFER_SIZE, &bytes );
    u32 realSize = bytes/sizeof(TIndexType);
    return realSize;
}

template<class TIndexType>
Bool CIndexBufferObject<TIndexType>::IsValid( )const
{
    return m_handle != ms_invalidIBHandle;
}

template<class TIndexType> 
void CIndexBufferObject<TIndexType>::Bind  ( )const
{
RENDER_GUARD_BLOCK
    gl::BindBuffer( gl::ELEMENT_ARRAY_BUFFER, m_handle);
}

template<class TIndexType>
void CIndexBufferObject<TIndexType>::Unbind( )const
{
RENDER_GUARD_BLOCK
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ms_defaultIBHandle);
}

template < class TIndexType>
void CIndexBufferObject<TIndexType>::InitFromOther( const CIndexBufferObject<TIndexType>& other )
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


template < class TIndexType >
TIndexBufferHandle CIndexBufferObject<TIndexType>::CreateIndexBufferObjectHandle( const thVector<TIndexType>& bufferData, EBufferUsage usage )
{
RENDER_GUARD_BLOCK
    TIndexBufferHandle handle = 0;
    gl::GenBuffers( 1, &handle );
    gl::BindBuffer( gl::ELEMENT_ARRAY_BUFFER, handle );
    gl::BufferData( gl::ELEMENT_ARRAY_BUFFER, ThNumericCast<GLsizeiptr>(bufferData.Size() * sizeof( TIndexType) ), bufferData.GetData(), gl::GetEnum(usage) );
    return handle;
}

template<class TIndexType>
CIndexBufferObject<TIndexType> CIndexBufferObject<TIndexType>::Create( const thVector<TIndexType>& bufferData, EBufferUsage usage )
{
RENDER_GUARD_BLOCK
    CIndexBufferObject<TIndexType> ibo;
    ibo.m_handle = CreateIndexBufferObjectHandle(bufferData,  usage);
    return ibo;
}

template<class TIndexType>
Bool CIndexBufferObject<TIndexType>::DrawElements( eGeometricPrimitive primitive, u32 count  )const
{
RENDER_GUARD_BLOCK
    u32 size = GetSize();
    if( count > size )
    {
        return false;
    }
    gl::DrawElements( gl::GetEnum(primitive), count, GetGlTypeID(ms_dummyIndexType), (void*)0 );

    return true;
}

template<class TIndexType>
TIndexType* CIndexBufferObject<TIndexType>::MapBuffer( EBufferAcces acces )
{
RENDER_GUARD_BLOCK
    Bind();
    return (TIndexType*)glMapBuffer( GL_ELEMENT_ARRAY_BUFFER, glGetEnum(acces) );
}




}// namespace RenderLowLevel