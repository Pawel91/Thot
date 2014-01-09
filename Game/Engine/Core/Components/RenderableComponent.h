#if !defined (__CORE_RENDERABLE_COMPONENT_H__)
#define __CORE_RENDERABLE_COMPONENT_H__

#include "Kernel/DataStructures/Array/Vector.h"
#include "Core/Components/ComponentBase.h"
#include "Render/Mesh/MeshBase.h"
#include "Render/ShaderFramework/ShaderTypes.h"

THOT_DECLARE_TEMPLATE_API(CORE_TEMPLATE_API, thVector<IMesh*>);

class CORE_API CRenderableComponent:public CComponetBase<CRenderableComponent>
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CRenderableComponent();
    ~CRenderableComponent();


//*********************************************
//            INTERFACE
//*********************************************
public:
    void                InsertMesh( IMesh* mesh);
    void                SetShaderID( ShaderID shaderID);
    const CShader*      GetShader()const;
    ShaderID            GetShaderID()const{ return m_shaderID;}
    Bool                CopyMeshes( const CRenderableComponent* other );

//*********************************************
//            MEMBERS
//*********************************************
public:
    CShader*            m_shader;   // shader that will be used to draw this renderable
    ShaderID            m_shaderID; // we keep pointer to shader and shaderID to because we don`t want to stress the shader manager with get calls
    thVector<IMesh*>    m_meshes;
};


#endif //__CORE_RENDERABLE_COMPONENT_H__