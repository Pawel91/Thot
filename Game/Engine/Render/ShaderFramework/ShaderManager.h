#if !defined(__RENDER_SHADER_MANAGER_H__)
#define __RENDER_SHADER_MANAGER_H__

#include "Render/RenderDef.h"
#include "Kernel/Singleton.h"
#include "Render/ShaderFramework/ShaderTypes.h"
#include "Kernel/DataStructures/Array/Vector.h"


class CString;
struct CShaderManagerPrivateData;

class RENDER_API CShaderManager: public CSingleton<CShaderManager>
{
    template<class T> friend class CSingleton;
private:
     CShaderManager();
    ~CShaderManager();

public:
    Bool                Init                ();

    ShaderID            GetShaderID         ( const CString& shaderName );
    void                BindShader          ( ShaderID shaderID );
    const CShader*      GetShaderFromID     ( ShaderID shaderID )const;
    CShader*            GetShaderFromID     ( ShaderID shaderID);

private:
    ShaderID            CompileShader       ( const CString& shaderName );

private:
    CShaderManagerPrivateData*      m_privateData;

#if defined(THOT_ENABLE_DEBUG)
    ShaderID                        m_currentActiveShaderID;
#endif

private:
    thVector<int>                   m_debugIntVector;
};





#endif