#pragma once
#ifndef __TEHNICI_COMPILARE_PATTERN_MATCHER_H__
#define __TEHNICI_COMPILARE_PATTERN_MATCHER_H__




template< class T>
class IPatternMatcher
{
public:
            IPatternMatcher(){}
virtual    ~IPatternMatcher(){}

public:

virtual Bool            IsMatch             ( )                             = 0;
virtual Bool            IsBlocked           ( )                             = 0;    //when it cannot take input anymore
virtual Bool            TakeInput           ( const T& input )              = 0;
virtual Bool            TakeInput           ( const CVector<T>& inputs )    = 0;
virtual Bool            Match               ( const CVector<T>& inputs )    = 0;
virtual void            Reset               ( )                             = 0;
};


#endif /*__TEHNICI_COMPILARE_PATTERN_MATCHER_H__*/