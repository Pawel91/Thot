#pragma once
#ifndef __RENDER_VERTEX_TYPES_H__
#define __RENDER_VERTEX_TYPES_H__

namespace RenderLowLevel
{

typedef u32 TVertexBufferHandle;
typedef u32 TIndexBufferHandle;


enum EVertexDescriptor
{
    E_VERTEX_ATTRIBUTE_NONE     =-1
    
    ,E_VERTEX_ATTRIBUTE_POSITION_3      = 1ull<<1
    ,E_VERTEX_ATTRIBUTE_POSITION_2      = 1ull<<2
    ,E_VERTEX_ATTRIBUTE_NORMAL          = 1ull<<3
    ,E_VERTEX_ATTRIBUTE_COLOR           = 1ull<<4
    ,E_VERTEX_ATTRIBUTE_TEXT_COORD1     = 1ull<<5
    ,E_VERTEX_ATTRIBUTE_TEXT_COORD2     = 1ull<<6
    ,E_VERTEX_ATTRIBUTE_TEXT_COORD3     = 1ull<<7
    ,E_VERTEX_ATTRIBUTE_TEXT_COORD4     = 1ull<<8

};





};



#endif /*__RENDER_VERTEX_TYPES_H__*/