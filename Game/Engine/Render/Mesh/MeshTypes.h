#pragma once
#ifndef __RENDER_MESH_TYPES_H__
#define __RENDER_MESH_TYPES_H__

#include "../RenderTypes.h"




enum class EMeshPrimitive
{
    E_MESH_PRIMITIVE_NONE       = -1

    ,E_MESH_PRIMITIVE_POINTS    = eGeometricPrimitive::E_GEOMETRIC_PRIMITIVE_POINTS
    ,E_MESH_PRIMITIVE_LINES     = eGeometricPrimitive::E_GEOMETRIC_PRIMITIVE_LINES
    ,E_MESH_PRIMITIVE_TRIANGLES = eGeometricPrimitive::E_GEOMETRIC_PRIMITIVE_TRIANGLES

    ,E_MESH_PRIMITIVE_COUNT = 3
};




#endif /*__RENDER_MESH_TYPES_H__*/