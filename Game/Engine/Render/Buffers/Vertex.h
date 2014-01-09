#ifndef __RENDER_VERTEX_H__
#define __RENDER_VERTEX_H__
#include "BufferTypes.h"
#include "Render/RenderGL.h"
#include "VertexConstructionDefines.h"
#include "VertexTypes.h"
#include "VertexDescriptor.h"
#include "VertexBuffer.h"

namespace RenderLowLevel
{
    class SVertex_P
    {
    public:
        tVect3      m_vertex;
    };
    DECLARE_VERTEX_DESCRIPTOR( SVertex_P );

    class SVertex_PN
    {
    public:
        tVect3      m_vertex;
        tVect3      m_normal;

    };
    DECLARE_VERTEX_DESCRIPTOR(SVertex_PN);

    struct SVertex_PNT
    {
        tVect3      m_vertex;
        tVect3      m_normal;
        tVect3      m_textCoord;
        CColor      m_color;
    };

    DECLARE_VERTEX_DESCRIPTOR(SVertex_PNT)

    struct SVertex_PNC
    {
        tVect3      m_vertex;
        tVect3      m_normal;
        CColor      m_color;
    };

    DECLARE_VERTEX_DESCRIPTOR(SVertex_PNC)


    // vertex with normal, texture coords and 4 bones;
    struct SVertex_PNTB4
    {
        RENDER_API         SVertex_PNTB4   ();
        RENDER_API         SVertex_PNTB4   ( const SVertex_PNTB4& other );
        RENDER_API Bool    WeightsAreOk    ()const;
        RENDER_API Bool    AddBoneData     ( u32 boneIndex, float weight );

        tVect3  m_vertex;
        tVect3  m_normal;
        tVect3  m_textCoord3;

        typedef u32 TBoneIdx;

        // array with bone indexes;
        CStaticArray<TBoneIdx,4>  m_boneIndexes;
        CStaticArray<float,4>     m_boneWeights;
        
        CString ToString()const;
    };

    DECLARE_VERTEX_DESCRIPTOR(SVertex_PNTB4);


BEGIN_VERTEX_CLASS_DESCRIPTOR(SVertex_P)
    REGISTER_VERTEX_MEMBER( SVertex_P, m_vertex, "position", 0, float, 3, false )
END_VERTEX_CLASS_DESCRIPTOR(SVertex_P)

BEGIN_VERTEX_CLASS_DESCRIPTOR(SVertex_PNT)
    REGISTER_VERTEX_MEMBER( SVertex_PNT, m_vertex,      "position",     0,  float,  3,  false )
    REGISTER_VERTEX_MEMBER( SVertex_PNT, m_normal,      "normal",       1,  float,  3,  false )
    REGISTER_VERTEX_MEMBER( SVertex_PNT, m_textCoord,   "texCoord",     2,  float,  3,  false )
    REGISTER_VERTEX_MEMBER( SVertex_PNT, m_color,       "color",        3,  float,  4,  true )
END_VERTEX_CLASS_DESCRIPTOR(SVertex_PNT)

BEGIN_VERTEX_CLASS_DESCRIPTOR(SVertex_PN)
    REGISTER_VERTEX_MEMBER( SVertex_PN, m_vertex, "position",   0,      float, 3, false )
    REGISTER_VERTEX_MEMBER( SVertex_PN, m_normal, "normal",     1,      float, 3, false )
END_VERTEX_CLASS_DESCRIPTOR(SVertex_PN)

BEGIN_VERTEX_CLASS_DESCRIPTOR(SVertex_PNC)
    REGISTER_VERTEX_MEMBER( SVertex_PNC, m_vertex,  "vertex",   0,      float, 3, false )
    REGISTER_VERTEX_MEMBER( SVertex_PNC, m_normal,  "normal",   1,      float, 3, false )
    REGISTER_VERTEX_MEMBER( SVertex_PNC, m_color,   "color",    2,      float, 4, true )
END_VERTEX_CLASS_DESCRIPTOR(SVertex_PNC)

BEGIN_VERTEX_CLASS_DESCRIPTOR(SVertex_PNTB4)
    REGISTER_VERTEX_MEMBER( SVertex_PNTB4,  m_vertex,       "vertex",       0,      float,  3,  false )
    REGISTER_VERTEX_MEMBER( SVertex_PNTB4,  m_normal,       "normal",       1,      float,  3,  false )
    REGISTER_VERTEX_MEMBER( SVertex_PNTB4,  m_textCoord3,   "texCoord",     2,      float,  3,  false )
    REGISTER_VERTEX_MEMBER( SVertex_PNTB4,  m_boneIndexes,  "boneindexes",  3,      u32,    4,  false )
    REGISTER_VERTEX_MEMBER( SVertex_PNTB4,  m_boneWeights,  "boneWeight",   4,      float,  4,  false )
END_VERTEX_CLASS_DESCRIPTOR(SVertex_PNTB4)


}// namespace RenderLowLevel


#endif /*__RENDER_VERTEX_H__*/