#if !defined(__CORE_BINDING_COMPONENT_H__)
#define __CORE_BINDING_COMPONENT_H__

#include "Kernel/DataStructures/Array/Vector.h"
#include "Core/Components/ComponentBase.h"
#include "Core/EntitySystem/EntityHandle.h"

THOT_DECLARE_TEMPLATE_API(CORE_TEMPLATE_API, thVector<CEntityHandle>);

class CORE_API CBindingComponent: public CComponetBase<CBindingComponent>
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CBindingComponent();
    ~CBindingComponent();

//*********************************************
//            INTERFACE
//*********************************************
public:
        const m4x4&     GetLocalTM();
        const m4x4&     GetWorldTM( Bool force = false)const;
        void            SetLocalTM( const m4x4& tm );

        CEntityHandle&  GetParent() { return m_parent;}
        Bool            IsOrphan();
        void            UpdateChildrenMatrices();
        void            AddChild( CEntityHandle& handle );

private:
    void                SetDirty( Bool isDirty = true );


//*********************************************
//            MEMBERS
//*********************************************
protected:
    CEntityHandle                   m_parent;
    thVector<CEntityHandle>         m_children;
    m4x4                            m_localTM;
    mutable m4x4                    m_worldTM; THOT_TODO("HACK!! WE NEED THE MODEL TO WORLD MATRIX FROM CONST BINDABLE COMPONENT! TO REMOVE");
    Bool                            m_isDirty:1;
};

#endif //__CORE_BINDING_COMPONENT_H__