#pragma once
#ifndef __RENDER_TYPES_H__
#define __RENDER_TYPES_H__

enum eGeometricPrimitive
{

     E_GEOMETRIC_PRIMITIVE_NONE            = -1
    ,E_GEOMETRIC_PRIMITIVE_POINTS
    
    //lines
    ,E_GEOMETRIC_PRIMITIVE_LINES
    ,E_GEOMETRIC_PRIMITIVE_LINE_STRIP
    ,E_GEOMETRIC_PRIMITIVE_LINE_LOOP


    //triangles
    ,E_GEOMETRIC_PRIMITIVE_TRIANGLES
    ,E_GEOMETRIC_PRIMITIVE_TRIANGLE_STRIP
    ,E_GEOMETRIC_PRIMITIVE_TRIANGLE_FAN

    //quads
    ,E_GEOMETRIC_PRIMITIVE_QUADS

    ,E_GEOMETRIC_PRIMITIVE_COUNT
    ,E_GEOMETRIC_PRIMITIVE_FORCE_DWORD = FORCE_DWORD
};

#endif /*__RENDER_TYPES_H__*/