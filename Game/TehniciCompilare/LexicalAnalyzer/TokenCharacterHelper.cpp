#include "TokenCharacterHelper.h"

THOT_IMPLEMENT_SINGLETON(CTokenCharacterHelper);

s32 CTokenCharacterHelper::CharactersCompareFunction( const char& op1, const char& op2 )
{
    return op1 - op2;
}

u64 CTokenCharacterHelper::FindInAll( char ch )
{
    return m_allCharacters.Find( ch, CharactersCompareFunction );
}

u64 CTokenCharacterHelper::Find( const TCharArray& array, char ch)
{
    return array.Find( ch, CharactersCompareFunction );
}


const CVector<char>& CTokenCharacterHelper::GetAll( )
{
    return m_allCharacters;
}

void CTokenCharacterHelper::OnInit( )
{
    const u64 nbCharacters = 128;
    m_allCharacters.Resize(nbCharacters);

    for( u64 i=0; i<m_allCharacters.GetSize(); i++ )
    {
        m_allCharacters[i] = (char)i;
    }

    char _blanks[] = "\n \t\r";
    for( u64 i=0; i<THOT_ARRAY_SIZE(_blanks); i++ )
    {
        m_blanks.Add(_blanks[i]);
    }
}

void CTokenCharacterHelper::ExcludeFromAll( const TCharArray& toExclude, TCharArray& out )
{
    const u64 newSize = m_allCharacters.GetSize() - toExclude.GetSize();
    THOT_ASSERT( newSize >= 0, "Exclude array is bigger");

    out.Resize(0);

    for( u64 i=0; i<m_allCharacters.GetSize(); i++ )
    {
        if( Find(toExclude, m_allCharacters[i]) == TCharArray::ms_invalidIndex )
        {
            out.Add( m_allCharacters[i] );
        }

    }

    THOT_ASSERT( out.GetSize() == newSize );
}

void CTokenCharacterHelper::ExcludeFromAll( char ch, TCharArray& out )
{
    CVector<char> temp;
    temp.Add(ch);

    ExcludeFromAll(temp, out);
}

Bool CTokenCharacterHelper::IsBlank( char c )const
{
    for( u64 i=0; i<m_blanks.GetSize(); i++ )
    {
        if( m_blanks[i] ==  c )
        {
            return true;
        }
    }

    return false;
}