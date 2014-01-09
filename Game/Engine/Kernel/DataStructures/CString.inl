

//================================================================================================
//                            THOT_INLINE DEFINITIONS
//================================================================================================

#ifndef DECLARE_CONSTRUCTOR_LIST
#define DECLARE_CONSTRUCTOR_LIST \
:m_pString      ( NULL )    \
,m_nSize        ( 0 )       \
,m_nMaxSize     ( 0 )       \
,m_ownBuffer    (true)      \
,m_allocator    (this)
#else
#   error DECLARE_CONSTRUCTOR_LIST already defined. 
#endif /*DECLARE_CONSTRUCTOR_LIST*/

inline CString::CString ( )
DECLARE_CONSTRUCTOR_LIST
{
}

#ifdef THOT_ENABLE_MOVE_CONSTRUCTOR
inline CString::CString (  CString&& otherTemp )
DECLARE_CONSTRUCTOR_LIST
{
    InitFromOtherTemp( otherTemp );
}
#endif /*THOT_ENABLE_MOVE_CONSTRUCTOR*/


inline CString::CString ( char* pBuff, Bool ownThisBuffer )
DECLARE_CONSTRUCTOR_LIST
{
    if( ownThisBuffer )
    {
        OwnBuffer( pBuff );
    }
    else
    {
        InitFromBuff(pBuff);
    }
}

inline CString::CString ( const char* pBuff )
DECLARE_CONSTRUCTOR_LIST
{
    InitFromBuff( pBuff );
}

inline CString::CString ( const CString& other )
DECLARE_CONSTRUCTOR_LIST
{
    InitFromOther( other );
}

inline CString::~CString( )
{
    Destroy();
}


#undef DECLARE_CONSTRUCTOR_LIST


THOT_FORCE_INLINE CString operator+( const char* pBuffer, const CString& rightOp )
{
    CString leftOp(pBuffer);
    return leftOp + rightOp;
}

inline void CString::OwnBuffer( char* pBuff )
{
    if( m_pString )
    {
        THOT_DELETE( m_pString );
    }

    size_t nLenght = strlen( pBuff );
    m_nMaxSize = m_nSize = nLenght;
    m_pString = pBuff;
}


inline void CString::InitFromBuff    ( const char* pBuff )
{
    if( pBuff != NULL )
    {
        size_t nBuffSize = strlen( pBuff );
        Resize(nBuffSize);
        memcpy( m_pString, pBuff, (size_t)(m_nSize+1) * sizeof(char) );
    }
    else
    {
        Empty();
    }
}

u64 CString::Find( char ch )
{
    for( int i=0; i<m_nSize; i++ )
    {
        if( m_pString[i]==ch )
        {
            return i;
        }
    }

    return ms_invalidIndex;
}


//--------------------------------------------------------------------------------
inline void CString::InitFromOther( const CString& other )
{
    if( other.m_nSize == 0 )
    {
        Empty();
        return;
    }

    Resize(other.m_nSize);
    memcpy( m_pString, other.m_pString, (size_t)(m_nSize+1) * sizeof(char) );
}


inline void CString::s_Concat ( const CString& a, const CString& b, CString& out )
{
    if( a.IsEmpty() && b.IsEmpty() )
    {
        out.Empty();
        return;
    }

    out.Resize( a.m_nSize + b.m_nSize );

    memcpy( out.m_pString, a.m_pString, (size_t)a.m_nSize * sizeof(char) );
    memcpy( out.m_pString + a.m_nSize, b.m_pString, (size_t)b.m_nSize * sizeof(char) );
}

inline s32 CString::Compare( const CString& a, const CString& b)
{

    const char* left = a.GetBuffer();
    const char* right = b.GetBuffer();

    return strcmp( left, right );
}

inline void CString::ToUpper( )
{
    for( register int i=0; i< m_nSize; i++ )
        m_pString[i] = S_TO_UPPER( m_pString[i] );

}

inline void CString::ToLower ( )
{
    for( register int i=0; i<m_nSize; i++ )
        m_pString[i] = S_TO_LOWER( m_pString[i] );
}




inline char CString::operator[] ( u64 nIdx )const
{
    THOT_ASSERT( nIdx >=0 && nIdx < m_nSize );
    return m_pString[nIdx];
}

inline char& CString::operator[] ( u64 nIdx )
{
    THOT_ASSERT( nIdx >=0 && nIdx < m_nSize );
    return m_pString[nIdx];
}

//--------------------------------------------------------------------------------
inline const CString&    CString::operator = ( const CString& other )
{
    InitFromOther(other);
    return *this;
}

//--------------------------------------------------------------------------------
inline const CString& CString::operator = ( CString&& otherTemp )
{
    InitFromOtherTemp( otherTemp );
    return *this;
}

//--------------------------------------------------------------------------------
inline const CString&    CString::operator = ( const char* pBuff )
{
    InitFromBuff( pBuff );
    return *this;
}

inline CString CString::operator + ( const CString& other )const
{
    CString toRet;
    s_Concat( *this, other, toRet );
    return toRet;
}

inline const CString& CString::operator +=    ( const CString& other )
{
    if( other.IsEmpty() )
        return *this;

    //u64 nFirstSize = m_nSize;
    u64 nNewSize = m_nSize + other.m_nSize;
    u64 oldSize = m_nSize;
    Resize(nNewSize);
    memcpy( m_pString + oldSize, other.m_pString, (size_t)other.m_nSize * sizeof(char) );
    return *this;
}

inline const CString&    CString::operator += ( const char* pBuff )
{
    if( pBuff == NULL )
        return *this;

    u64 nBuffSize = strlen(pBuff);
    u64 nOldSize = m_nSize;
    u64 nNewSize = m_nSize + nBuffSize;

    Resize( nNewSize );

    memcpy( m_pString + nOldSize, pBuff, (size_t)nBuffSize * sizeof(char) );

    return *this;
}

inline    CString::operator const char* ( )const
{
    return m_pString;
}

inline    CString::operator char* ( )
{
    return m_pString;
}


inline void CString::Empty( )
{
    m_nSize = 0;
    if( m_pString )
    {
        m_pString[0] = 0;
    }
}

inline void CString::Destroy()
{
    if( m_pString && m_ownBuffer )
    {
        m_allocator.Free(m_pString);
    }
}

inline void CString::Resize ( u64 nNewNeededSize )
{
    u64 oldSize = m_nSize;
    m_nSize = nNewNeededSize;
    if( nNewNeededSize < m_nMaxSize )
    {
        if( m_pString )
        {
            m_pString[m_nSize] = 0;
        }
        return;
    }
    //else we need to grow the string;

    char* pOldBuffer = m_pString;

    u64 nGrowBy = ThMax( 16, (u64)( ms_growFactor * nNewNeededSize ) );
    m_nMaxSize = nNewNeededSize + nGrowBy;

    m_pString = (char*)m_allocator.Alloc( (size_t)m_nMaxSize);
    memset( m_pString, 0, ThNumericCast<size_t>( m_nMaxSize * sizeof(char) ) );
   
    if( pOldBuffer )
    {
        memcpy( m_pString, pOldBuffer, ThNumericCast<size_t>(oldSize) );
        m_allocator.Free( pOldBuffer );
    }
}

inline  Bool CString::operator==( const CString& other)const
{
    if( other.GetLenght() != GetLenght() )
        return false;

    if( memcmp( GetBuffer(), other.GetBuffer(), ThNumericCast<size_t>(GetLenght()) )==0 )
    {
        return true;
    }
    else
    {
        return false;
    }

}

inline Bool CString::SubStr( u64 from, u64 lenght, CString& out )
{
    if( from + lenght > GetLenght() )
    {
        return false;
    }

    out.Resize(lenght);
    memcpy( out.GetBuffer(), GetBuffer() + from, ThNumericCast<size_t>(lenght) );
    out.m_pString[out.GetLenght()] = 0;

    return true;
}


inline  Bool CString::operator==( const char* pBuff )const
{
    if( pBuff == NULL )
        return false;

    size_t lenght = strlen(pBuff);
    if( lenght != GetLenght() )
        return false;

    if( memcmp( GetBuffer(), pBuff, ThNumericCast<size_t>(GetLenght()) )==0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

THOT_FORCE_INLINE void CString::Append( const char ch )
{
    char ar[2] = {0,0};
    ar[0] = ch;

    *this += ar;
}

inline  CString::operator std::string( )
{
    return std::string(GetBuffer());
}

inline  CString::operator const std::string( )const
{
    return std::string(GetBuffer());
}

inline void CString::SetInternalBufferOwnership ( Bool own )
{
    m_ownBuffer = own;
}

inline Bool CString::operator <          ( const CString& other )
{
    return Compare(*this, other) < 0;
}

inline Bool CString::operator <= ( const CString& other )
{
    return Compare(*this, other) <= 0;
}

inline      Bool CString::operator >  ( const CString& other )
{
    return !  this->operator<(other);
}
inline      Bool CString::operator >= ( const CString& other )
{
    return Compare( *this, other) >= 0;
}
