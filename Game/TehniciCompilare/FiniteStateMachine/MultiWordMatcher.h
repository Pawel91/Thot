#pragma once
#ifndef __TEHNICI_COMPILARE_MULTI_WORD_MATCHER_H__
#define __TEHNICI_COMPILARE_MULTI_WORD_MATCHER_H__


#include "PatternMatcher.h"


template<class T>
class CMultiWordMatcher: public IPatternMatcher<T>
{
public:

             CMultiWordMatcher();
virtual     ~CMultiWordMatcher();


public:
    typedef CVector<T>          TWord;
    typedef CVector<TWord*>     TWordArray;


        Bool            AddNewWord          ( const TWord& newWord );

virtual Bool            IsMatch             ( )                             override;
virtual Bool            IsBlocked           ( )                             override;    //when it cannot take input anymore
virtual Bool            TakeInput           ( const T& input )              override;
virtual Bool            TakeInput           ( const CVector<T>& inputs )    override;
virtual Bool            Match               ( const CVector<T>& inputs )    override;
virtual void            Reset               ( )                             override;


protected:
        Bool            CurrentWordIsPrefix ( );
        
        u64             FindWord    ( const TWord& word );

static  Bool            IsPrefix    ( const TWord& word, const TWord& prefix );
static  Bool            WordEquals ( const TWord& w1, const TWord& w2 );


protected:
    static  u64     ms_invalidWordIndex;
    TWord           m_currentWord;
    TWordArray      m_wordArray;

};




#include "MultiWordMatcher.inl"







#endif