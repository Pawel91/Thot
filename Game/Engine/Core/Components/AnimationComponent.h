#if !defined(__CORE_ANIMATION_COMPONENT_H__)
#define __CORE_ANIMATION_COMPONENT_H__

#include "Core/Components/ComponentBase.h"

#include "Render/SkeletonAnimation/Skeleton.h"

class CORE_API CAnimationComponent: public CComponetBase<CAnimationComponent>
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CAnimationComponent();
    ~CAnimationComponent();


//*********************************************
//            INTERFACE
//*********************************************
public:


//*********************************************
//            MEMBERS
//*********************************************
protected:
    CSkeleton*          m_skeleton;
};


#endif //__CORE_ANIMATION_COMPONENT_H__