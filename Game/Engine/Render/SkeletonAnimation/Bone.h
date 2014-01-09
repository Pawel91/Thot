#ifndef __RENDER_BONE_H__
#define __RENDER_BONE_H__

#include "Render/RenderDef.h"
#include "BoneState.h"
#include "Kernel/DataStructures/CString.h"
#include "Kernel/DataStructures/Array/Vector.h"

class CBoneTrack;

class  CBone
{
    THOT_DECLARE_NOCOPY_CLASS(CBone);

friend class CSkeleton;
friend class CSceneAssimpConverter;
//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
    RENDER_API  CBone();
    RENDER_API ~CBone();


//*********************************************
//            INTERFACE
//*********************************************
public:
    typedef thVector<CBone*>             TBoneArray;

    typedef thVector<CBoneTrack*>        TAnimations;

        // Get functions;
        RENDER_API CString&                GetName         ( );
        RENDER_API const CString&          GetName         ( )const;
        RENDER_API const CBone*            GetParent       ( )const;
        RENDER_API CBone*                  GetParent       ( );

        RENDER_API const CBone*            GetChild        ( u32 index )const;
        RENDER_API CBone*                  GetChild        ( u32 index );
        RENDER_API const TBoneArray&       GetChilds       ( )const;
        RENDER_API TBoneArray&             GetChilds       ( );
        RENDER_API u32                     GetChildCount   ( )const;

        RENDER_API u32                     GetBoneIdx      ()const { return m_boneIdx; }

        RENDER_API u32                     AddChild        ( CBone* child );

        RENDER_API u32                     AddBoneTrack    ( CBoneTrack* boneTrack );

        RENDER_API void                    SetName         ( const CString& name );
        RENDER_API void                    SetParent       ( CBone* parent );

        RENDER_API void                    GetBoneAndLocalMatrix   ( u32 animationIdx, float fTimeRatio, const m4x4& parentModelMatrix, m4x4& outBoneMatrix, m4x4& outLocalMatrix)const;
        
        RENDER_API void                    GetModelTM              ( u32 animationIdx, float fTimeRatio, m4x4& outModelTM )const;
        RENDER_API void                    GetLocalTM              ( u32 animationIdx, float fTimeRatio, m4x4& outLocalTM )const;

        RENDER_API void                    GetDefaultLocalTM       ( m4x4& outTM )const;
        RENDER_API void                    GetDefaultModelTM       ( m4x4& outDefModelTM )const;

//*********************************************
//            HELPERS
//*********************************************


//*********************************************
//            MEMBERS
//*********************************************
protected:
    u32                 m_boneIdx;      // index in the skeleton array;
    CBone*              m_parent;       // parent bone
    CString             m_name;         // name of the bone
    TBoneArray          m_childs;       // childs of this bone
    m4x4                m_invDefaultModelTM;    // mesh to bone matrix
    m4x4                m_defaultLocalPos;       // default bone local TM
    TAnimations         m_animations;
};


#endif /*__RENDER_BONE_H__*/ 