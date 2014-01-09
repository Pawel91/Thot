#pragma once


class CTokenCharacterHelper
{
    THOT_DECLARE_SINGLETON(CTokenCharacterHelper);

public:
    typedef CVector<char>   TCharArray;

        void                    OnInit          ( );
        void                    ExcludeFromAll  ( const TCharArray& toExclude, TCharArray& out );
        void                    ExcludeFromAll  ( char ch, TCharArray& out );
        const CVector<char>&    GetAll          ( );
        Bool                    IsBlank         ( char c )const;
        

static  s32     CharactersCompareFunction( const char& op1, const char& op2 );

protected:
        u64     FindInAll( char ch );
        u64     Find( const TCharArray& array, char ch);

protected:
        
        CVector<char>           m_blanks;
        CVector<char>           m_allCharacters;

};