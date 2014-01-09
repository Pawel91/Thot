//  [11/9/2013 Radu]
#if !defined(__KERNEL_TERRAIN_H__)
#define __KERNEL_TERRAIN_H__

#include "Core/Components/RenderableComponent.h"
#include "Core/Components/UpdateComponent.h"



class CHeightMap;


class CORE_API CTerrainUpdateComponent: public CUpdateComponent
{
    virtual     void        OnUpdate ( float deltaTime)override;
};

class CORE_API CTerrainComponent: public CRenderableComponent
{
    friend class CTerrainUpdateComponent;
public:

    struct CORE_API SProperties
    {
        SProperties()
            : m_maxHeight   ( 0.f )
            , m_width       ( 0.f )
            , m_lenght      ( 0.f )
        {}

        float   m_maxHeight;
        float   m_width;
        float   m_lenght;
    };


//*********************************************
//            CONSTR/DESTR
//*********************************************
public:

     CTerrainComponent();
    ~CTerrainComponent();

//*********************************************
//            INTERFACE
//*********************************************
public:
    CHeightMap* GetHeightMap        () { return m_heightMap;}
    Bool        OnInit      ( );
    void        DebugUpdateVertices ();

//*********************************************
//            HELPERS
//*********************************************
protected:

    Bool        LoadHeightMap       ( );
    Bool        GenerateGeometry    ( );




//*********************************************
//            MEMBERS
//*********************************************
protected:
    CHeightMap*             m_heightMap;
    SProperties             m_properties;

};



#endif //__KERNEL_TERRAIN_H__