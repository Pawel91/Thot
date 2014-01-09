#include "Render_PCH.h"

#include "Vertex.h"
#include "Render/RenderGL.h"
#include "Kernel/Utils/StringUtils.h"
 
namespace RenderLowLevel
{

SVertex_PNTB4::SVertex_PNTB4()
{
    memset( m_boneWeights.GetData(), 0, ThNumericCast<size_t>( m_boneWeights.GetSize() * sizeof(m_boneWeights[0]) ) );
    memset( m_boneIndexes.GetData(), 0x0, ThNumericCast<size_t>( m_boneIndexes.GetSize() * sizeof(m_boneIndexes[0]) ) );
}

SVertex_PNTB4::SVertex_PNTB4( const SVertex_PNTB4& other )
{
    memcpy( this, &other, sizeof(SVertex_PNTB4) );
}

Bool SVertex_PNTB4::WeightsAreOk()const
{
    float weightSum = 0.f;
    for(u64 i=0; i<m_boneWeights.GetSize();i++)
    {
        weightSum += m_boneWeights[i];
    }

    if( fequals( weightSum, 1.f ) )
    {
        return true;
    }

    return false;
}

Bool SVertex_PNTB4::AddBoneData( u32 boneIndex, float weight )
{
    for( u64 i=0; i<m_boneWeights.GetSize(); i++ )
    {
        if( m_boneWeights[i] == 0.f )
        {
            m_boneWeights[i] = weight;
            m_boneIndexes[i] = (TBoneIdx)(boneIndex);
            return true;
        }
    }

    return false;
}

CString SVertex_PNTB4::ToString()const
{
    CString string;
    string += StringUtils::FormatString( "vertex        = [%f, %f, %f]\n", m_vertex.x, m_vertex.y, m_vertex.z );
    string += StringUtils::FormatString( "normal        = [%f, %f, %f]\n", m_normal.x, m_normal.y, m_normal.z );
    string += StringUtils::FormatString( "texcoord      = [%f, %f, %f]\n", m_textCoord3.x, m_textCoord3.y, m_textCoord3.z );
    string += StringUtils::FormatString( "boneIndices   = [%d, %d, %d, %d]\n", m_boneIndexes[0], m_boneIndexes[1], m_boneIndexes[2], m_boneIndexes[3] );
    string += StringUtils::FormatString( "boneWeight    = [%f, %f, %f, %f]\n", m_boneWeights[0], m_boneWeights[1], m_boneWeights[2], m_boneWeights[3] );

    return string;
}

}// namespace RenderLowLevel