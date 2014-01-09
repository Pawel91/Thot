#if !defined(__CORE_RENDER_SYSTEM_H__)
#define __CORE_RENDER_SYSTEM_H__

#include "Core/System/SystemBase.h"


struct SRenderableContainter;

class CORE_API CRenderSystem: public CSystemBase<CRenderSystem>
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CRenderSystem();
    ~CRenderSystem();


//*********************************************
//            INTERFACE
//*********************************************
public:

    virtual     void        OnInit() override;
    virtual     void        Execute( ) override;
    virtual     void        RegisterComponents() override;
    virtual     void        OnEntityComponentChange( const CEntityHandle& handle, IComponent* component, bool added ) override;


//*********************************************
//            MEMBERS
//*********************************************
protected:

    SRenderableContainter*              m_renderableContainer;
    thVector<CEntityHandle>              m_lightEntities;

    class CViewportParameterProvider*   m_viewportParameterProvider;

};



#endif //__CORE_RENDER_SYSTEM_H__