#if !defined(__CORE_LIGHT_COMPONENT_H__)
#define __CORE_LIGHT_COMPONENT_H__

#include "Core/Components/ComponentBase.h"
#include "Render/Color.h"


enum ELightType
{
     ELightType_Directional
    ,ELightType_Positional
    ,ELightType_Spot
};


class CORE_API CLightComponent: public CComponetBase<CLightComponent>
{
//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
            CLightComponent();
virtual    ~CLightComponent();


//*********************************************
//            INTERFACE
//*********************************************
public:
        void            SetType             ( ELightType lightType );
        void            SetAmbient          ( const CColor& color );
        void            SetDiffuse          ( const CColor& color );
        void            SetSpecular         ( const CColor& color );
        void            SetAttenuation      ( const tVect3& attenuation );
        void            SetExponent         ( float exponent );
        void            SetCutoff           ( float cutoff );
        void            SetDirectionToLight ( const tVect3& dir );

        const CColor&   GetAmbient      () const;
        const CColor&   GetDiffuse      () const;
        const CColor&   GetSpecular     () const;
        const tVect3&   GetAttenuation  () const;
        float           GetExponent     () const;
        float           GetCutoff       () const;
        ELightType      GetLightType    () const;

//*********************************************
//            MEMBERS
//*********************************************
protected:
    // direction and position for lights are found in CBindingComponent;
    CColor          m_ambient;
    CColor          m_diffuse;
    CColor          m_specular;
    ELightType      m_lightType;

    /**
    Attenuation factor for a positional light = 1.f/ ( c + l * d + q * d *d  ) where d is the distance from surface to the light
    clqOut.x = c; clqOut.y = l; clqOut.z = q;
    */
    tVect3      m_attenuation;  // only for positional light
    float       m_fCutoff;      // only for spot lights
    float       m_fExponent;    // only for spot lights
};




#endif //__CORE_LIGHT_COMPONENT_H__