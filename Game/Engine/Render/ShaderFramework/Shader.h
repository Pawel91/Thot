#pragma once
#ifndef __RENDER_SHADER_FRAMEWORK_H__
#define __RENDER_SHADER_FRAMEWORK_H__

#include "../RenderTypes.h"
#include "Render/Lights/LightBase.h"
#include "ShaderTypes.h"
#include "Render/ShaderFramework/ShaderLayout/ShaderData.h"


class CMaterial;
class IShaderParameterProvider;

struct SShaderProvidersPrivateData;
class IShaderParameterProvider;


struct SShaderCompileContext
{
public:
    const SShaderCompileContext& operator = ( const SShaderCompileContext& other )
    {
        m_shaderName            = other.m_shaderName;
        m_vertexShaderPath      = other.m_vertexShaderPath;
        m_fragmentShaderPath    = other.m_fragmentShaderPath;

        return *this;
    }

    CString     m_shaderName;
    CString     m_vertexShaderPath;
    CString     m_fragmentShaderPath;
};

class  CShader
{
    friend class CShaderManager;

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
    RENDER_API  CShader ();
    RENDER_API ~CShader();


//*********************************************
//            INTERFACE
//*********************************************
public:

    RENDER_API ShaderID         GetID                   ( );
    RENDER_API CRenderer*       GetRenderer             ( );           
    RENDER_API Bool             IsValid                 ( );
    RENDER_API void             SetupProviders          ( const IShaderParameterProvider* providers, u32 count )const;
    RENDER_API void             SetupParameterProvider  ( const IShaderParameterProvider& parameterProvider )const;

//*********************************************
//            HELPERS
//*********************************************
protected:
        Bool                Compile                 ( const SShaderCompileContext& compileContext );
        Bool                OnPostCompile           ( );
        Bool                ReadShaderSource        ( const CString& vertexShaderPath, const CString& fragmentShaderPath, CString& outVertexSource, CString& outFragSource );
        Bool                ReadShaderSource        ( const CString& path, CString& outSource );

static  Bool                ValidateShader      ( ShaderID shaderID, const CString& fileName );
static  Bool                ValidateProgram     ( ShaderID shaderID );
static  Bool                HasCompileErrors    ( ShaderID shaderID);
static  Bool                HasLinkErrors       ( ShaderID shaderID );

//*********************************************
//            MEMBERS
//*********************************************
private:
        Bool                            m_isValid;
        CShaderData                     m_shaderData;

#if defined(THOT_ENABLE_DEBUG)
        SShaderCompileContext           m_debugCompileContext;
#endif

static  const u32       ms_invalidUniformLocation = -1;
};

#endif /*__RENDER_SHADER_FRAMEWORK_H__*/