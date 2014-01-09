#if !defined(__CORE_TRANSFORMATION_COMPONENT_H__)
#define __CORE_TRANSFORMATION_COMPONENT_H__

class CORE_API CTransformationComponent
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CTransformationComponent();
    ~CTransformationComponent();


//*********************************************
//            INTERFACE
//*********************************************
public:
    void                SetLocalTM          ( const m4x4& localTM );
    void                UpdateWorldTM       ( const m4x4& parentTM );

    const m4x4&         GetLocalTM          ()const;
    const m4x4&         GetWorldTM          ()const;

//*********************************************
//            MEMBERS
//*********************************************
protected:
    m4x4                m_localTM;
    m4x4                m_worldTM;

};

#endif //__CORE_TRANSFORMATION_COMPONENT_H__