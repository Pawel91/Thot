#include "Render_PCH.h"
#include "RenderGL.h"

//#include "gl/gl.h"
//#include "gl/glu.h"
#include "math.h"
#include "Render/RenderCamera.h"
#include "Render/Lights/LightBase.h"
#include "Render/Lights/LightManager.h"
#include "Render/Textures/Texture.h"
#include "Render/ShaderFramework/Shader.h"
#include "Render/ShaderFramework/ShaderManager.h"
#include "Input/Input.h"


#if defined(NO_ERROR)
#   error NO_ERROR is defined
#endif

#include "Render\GLWrapper\OpenGL.h"

#include "Terrain\Skybox.h"


const char*    glGetErrorType( GLenum err );

const float    LIGHT_AS_POS    = 1.f;
const float    LIGHT_AS_DIR    = 0.f;

//--------------------------------------------------------------------------
CRenderGL::CRenderGL ( )
:m_windowsWidth     ( 0 )
,m_windowsHeight    ( 0 )
,m_shader           (NULL)

{
    m_pRenderCamera = THOT_NEW CRenderCamera;
}

//--------------------------------------------------------------------------
CRenderGL::~CRenderGL ( )
{
    THOT_DELETE( m_pRenderCamera );
    THOT_DELETE(m_skybox);
}

//--------------------------------------------------------------------------
Bool CRenderGL::Init ( )
{
    if( !gl::Init() )
    {
        THOT_ASSERT(false, "Unable to init OpenGL!");
        return false;
    }

    if( !CShaderManager::GetInstance() )
    {
        CShaderManager::CreateInstance()->Init();
    }

    gl::ClearColor( 0.f, 0.f, 0.f, 1.f );

    //TODO: remove skybox and terrain from here
    m_skybox = THOT_NEW CSkybox;
    m_skybox->SetSize( 0.5f * m_pRenderCamera->GetZFar() );
    m_skybox->Load( "Data//ft.tga", "Data//bk.tga", "Data//lt.tga", "Data//rt.tga", "Data//up.tga",  "Data//dn.tga"  );

    gl::Enable( gl::DEPTH_TEST );
    gl::DepthFunc( gl::LEQUAL );
    
    //gl::PolygonMode(gl::FRONT_AND_BACK, gl::LINE);
    gl::Enable( gl::BLEND );
    gl::BlendFunc( gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);
//    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_DST_ALPHA);

    gl::Enable( gl::TEXTURE_2D );
    
    return true;
}

//--------------------------------------------------------------------------
Bool CRenderGL::ShutDown ( )
{
    return true;
}

//--------------------------------------------------------------------------
void CRenderGL::SetupProjection    ( )
{
    THOT_ASSERT(m_pRenderCamera!=NULL);

    gl::Viewport( 0, 0, m_windowsWidth, m_windowsHeight );    // reset the viewport to new dimensions

    m_pRenderCamera->SetScreenRatio( (float)m_windowsWidth/(float)m_windowsHeight );
}

//--------------------------------------------------------------------------
void CRenderGL::SetWidth ( u32 width)
{
    m_windowsWidth = width;
}

//--------------------------------------------------------------------------
void CRenderGL::SetHeight( u32 height)
{
    m_windowsHeight = height;
}

//--------------------------------------------------------------------------
CRenderCamera* CRenderGL::GetCamera ( )
{
    return m_pRenderCamera;
}

//--------------------------------------------------------------------------
int CRenderGL::GetWidth ( )const 
{
    return m_windowsWidth;
}

//--------------------------------------------------------------------------
int CRenderGL::GetHeight ( )const
{ 
    return m_windowsHeight;
}

//--------------------------------------------------------------------------
void CRenderGL::StartRender ( )
{   
    //gl::PolygonMode( gl::FRONT_AND_BACK, gl::LINE);

    CInput& input =  *CInput::GetInstance();
    const CKeyInputInterface* keyboard = input.GetDeviceInputT<CKeyInputInterface>(InputDevices::E_INPUT_DEVICE_KEYBOARD);
    if(keyboard->ButtonDown(InputKey::E_KEY_L))
    {
        gl::PolygonMode(gl::FRONT_AND_BACK, gl::LINE);
    }

    if(keyboard->ButtonDown(InputKey::E_KEY_K))
    {
        gl::PolygonMode(gl::FRONT_AND_BACK, gl::FILL);
    }



    SetupProjection( );
    gl::Clear( gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT | gl::STENCIL_BUFFER_BIT );        // clear screen and depth buffer
    gl::ClearColor( 0.7f, 0.7f, 0.7f, 0.f );
}

//--------------------------------------------------------------------------
void CRenderGL::Render ( )
{
    StartRender();
    
    //for( u64 i=0; i< m_renderers.GetSize(); i++ )
    //{
    //    THOT_ASSERT( m_renderers[i], "CANNOT DRAW WITH A NULL RENDERER");
    //    m_renderers[i]->OnDraw();
    //}

    Bool bEndSucces = EndRender( );
    if( !bEndSucces )
    {   
        THOT_TRACE( GetRenderErrMessage() );
        THOT_ASSERT( 0 );
    }

}


//--------------------------------------------------------------------------
Bool CRenderGL::EndRender ( )
{
    m_glErr = gl::GetError();
    if( m_glErr != gl::NO_ERROR )
    {
        return false;
    }

    //// clear renderers when end rendering
    //for( u64 i=0; i<m_renderers.GetSize(); i++  )
    //{
    //    m_renderers[i]->Clear( );
    //}

    return true;
}

const char* CRenderGL::GetRenderErrMessage ( )const
{
    return glGetErrorType( m_glErr );
}


void CRenderGL::DbgVerifyRenderState    ( )
{
    m_glErr = gl::GetError();
    if( m_glErr != gl::NO_ERROR )
    {
        THOT_ASSERT( false, "CRenderGL ERROR:[%s]", GetRenderErrMessage() );
    }
}





void CRenderGL::SetupLights ( )const
{
    CLightManager* lightManager = CLightManager::GetInstance();
    lightManager->ApplyLights();
}


const char*    glGetErrorType( GLenum err )
{
    static const int nBufferSize = 64;
    static char szString[nBufferSize];
    memset(szString, 0, nBufferSize);//clear buffer;
    switch(err)
    {
    case gl::NO_ERROR:
    { 
        //No error has been recorded. The value of this symbolic constant is guaranteed to be 0. 
        strcpy_s(szString, "GL_NO_ERROR");
        break;
    }

    case gl::INVALID_ENUM:
    {
        //An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.     
        strcpy_s(szString, "GL_INVALID_ENUM");
        break;
    }

    case gl::INVALID_VALUE:
    {
        // numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag. 
        strcpy_s(szString, "GL_INVALID_VALUE");
        break;
    }

    case gl::INVALID_OPERATION:
    {
        //The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag. 
        strcpy_s(szString, "GL_INVALID_OPERATION");
        break;
    }


    //case GL_INVALID_FRAMEBUFFER_OPERATION:
    //{
    //    //he framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.
    //    strcpy_s(szString, "GL_INVALID_FRAMEBUFFER_OPERATION");
    //    break;
    //}

    case gl::OUT_OF_MEMORY:
    {
        //There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded. 
        strcpy_s(szString, "GL_OUT_OF_MEMORY");
        break;
    }

    default:
        strcpy_s(szString, "GL_ERROR_UNKNOWN");
    }

    return szString;
}

//-----------------------------------------------------------------------------------
void CRenderGL::AddRenderer( CRenderer* renderer )
{
    m_renderers.PushBack( renderer );
}