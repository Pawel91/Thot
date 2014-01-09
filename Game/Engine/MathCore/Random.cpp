#include "MathCore_PCH.h"
#include "MathCore\Vector\Vector.h"
#include "MathCore\Random.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



class cMakeRand
{
public:
    cMakeRand(){ srand( (unsigned)time(NULL) ); }
    ~cMakeRand(){}
};
static cMakeRand makeRandobj;

int Random::GetNumber ( )
{
    return rand();
}

int Random::GetNumber ( int min, int max )
{
    return rand()%(max - min + 1 ) + min;
}

float Random::GetFloat ( float min, float max )
{
    return ((max-min)*((float)rand()/RAND_MAX))+min;
}

tVect2 Random::GetVect ( const tVect2& min, const tVect2& max )
{
    return tVect2( Random::GetFloat(min.x, max.x), Random::GetFloat(min.y, max.y) );
}

