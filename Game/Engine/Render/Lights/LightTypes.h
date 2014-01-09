#pragma once
#ifndef __RENDER_LIGHT_TYPES_H__
#define __RENDER_LIGHT_TYPES_H__

#include "Kernel/DataStructures/Array/Array.h"
#include "Render/Color.h"


enum eLightComponents
{
    E_LIGHT_COMP_NONE        = -1
    ,E_LIGHT_COMP_AMBIENT
    ,E_LIGHT_COMP_DIFFUSE
    ,E_LIGHT_COMP_SPECULAR


    ,E_LIGHT_COMP_COUNT
};


enum eLightType
{
    E_LIGHT_TYPE_NONE            = -1
    ,E_LIGHT_TYPE_DIRECTIONAL
    ,E_LIGHT_TYPE_POSITIONAL
    ,E_LIGHT_TYPE_SPOTLIGHT

    ,E_LIGHT_TYPE_COUNT
};

typedef CStaticArray<CColor,E_LIGHT_COMP_COUNT>    tColorCompArray;



#endif /*__RENDER_LIGHT_TYPES_H__*/

