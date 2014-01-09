
template<u32 SIZE>
void CFixedString<SIZE>::ZeroInit()
{
    Memory::Set(m_string, SIZE+1, 0 );
}

//--------------------------------------------------------------------------------
template<u32 SIZE>
CFixedString<SIZE>::CFixedString()
    : m_realSize (0)
{
    ZeroInit();
}

//--------------------------------------------------------------------------------
template<u32 SIZE>
CFixedString<SIZE>::CFixedString( const char* str, thSize size )
    : m_realSize (0)
{
    ZeroInit();
    m_realSize = ThNumericCast<u32>( ThMin<thSize>( size, SIZE ) );
    Memory::Copy( m_string, str, m_realSize );
}

//--------------------------------------------------------------------------------
template<u32 SIZE>
CFixedString<SIZE>::CFixedString( const char* szBuffer )
    : m_realSize (0)
{
    ZeroInit();
    m_realSize = ThMin<u32>( ThNumericCast<u32>(strlen(szBuffer)), SIZE );
    for( u32 i=0; i<m_realSize; i++ )
    {
        m_string[i] = szBuffer[i];
    }
}


//--------------------------------------------------------------------------------
template<u32 SIZE>
template<u32 OTHER_SIZE>
Bool CFixedString<SIZE>::operator == ( const CFixedString<OTHER_SIZE>& otherString )
{
    if( m_realSize != otherString.m_realSize )
    {
        return false;
    }

    for( u32 i=0; i<m_realSize; i++ )
    {
        if( m_string[i] != otherString[i] )
        {
            return false;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------
template<u32 SIZE>
template<u32 OTHER_SIZE>
CFixedString<SIZE>::CFixedString( const CFixedString<OTHER_SIZE>& otherString )
    : m_realSize (0)
{
    ZeroInit();
    m_realSize = ThMin( otherString.m_realSize, SIZE );
    for( u32 i=0; i<m_realSize; i++ )
    {
        m_string[i] = otherString.m_string[i];
    }
}

//--------------------------------------------------------------------------------
template<u32 SIZE>
const char* CFixedString<SIZE>::c_str() const
{
    return m_string;
}

//--------------------------------------------------------------------------------
template<u32 SIZE>
const CFixedString<SIZE>& CFixedString<SIZE>::operator = ( const char* szBuffer )
{
    ZeroInit();
    m_realSize = ThMin<u32>( ThNumericCast<u32>(strlen(szBuffer)), SIZE );
    Memory::Copy( m_string, szBuffer, m_realSize );

    return *this;
}

//--------------------------------------------------------------------------------
template<u32 SIZE>
template<u32 OTHER_SIZE>
const CFixedString<SIZE>& CFixedString<SIZE>::operator = ( const CFixedString<OTHER_SIZE>& otherString )
{
    ZeroInit();
    m_realSize = ThMin<u32>( SIZE, otherString.m_realSize );
    if( m_realSize )
    {
        Memory::Copy(m_string, otherString.m_string, m_realSize );
    }

    return *this;
}

//--------------------------------------------------------------------------------
template<u32 SIZE>
const CFixedString<SIZE>& CFixedString<SIZE>::operator += ( const char* szBuffer )
{
    ZeroInit();
    m_realSize = ThMin<u32>( ThNumericCast<u32>( strlen(szBuffer)), SIZE );
    Memory::Copy( m_string, szBuffer, m_realSize );
    return *this;
}

//--------------------------------------------------------------------------------
template<u32 SIZE>
template<u32 OTHER_SIZE>
const CFixedString<SIZE>& CFixedString<SIZE>::operator += ( const CFixedString<OTHER_SIZE>& otherString )
{
    u32 index = 0;
    while( m_realSize < SIZE && index < otherString.m_realSize )
    {
        m_string[m_realSize] = otherString.m_string[index];
        index++;
        m_realSize++;
    }

    return *this;    
}

//--------------------------------------------------------------------------------
template<u32 SIZE>
template<u32 OTHER_SIZE>
CFixedString< OTHER_SIZE + SIZE > CFixedString<SIZE>::operator + ( const CFixedString<OTHER_SIZE>& otherString )
{
    CFixedString<OTHER_SIZE + SIZE> tempString;
    Memory::Copy( tempString.m_string, m_string, m_realSize );
    Memory::Copy( tempString.m_string + m_realSize, otherString.m_string, otherString.m_realSize );
    tempString.m_realSize = m_realSize + otherString.m_realSize;
    THOT_ASSERT( tempString.m_realSize == strlen(tempString.m_string));

    return tempString;
}

//--------------------------------------------------------------------------------
