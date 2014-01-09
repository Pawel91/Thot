#pragma once
#ifndef __RANDOM_H__
#define __RANDOM_H__

//#include "MathCore\MathCoreDef.h"

struct tVect2;
namespace Random
{
MATHCORE_API    int             GetNumber       ( );
MATHCORE_API    int             GetNumber       ( int min, int max );
MATHCORE_API    float           GetFloat        ( float min, float max );
MATHCORE_API    tVect2          GetVect         ( const tVect2& min, const tVect2& max );
};


#endif /*__RANDOM_H__*/