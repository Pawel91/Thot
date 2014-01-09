#include "Core_PCH.h"
#include "SceneRenderableNode.h"

#include "Kernel/Profiler/Profiler.h"
#include "Render/Mesh/MeshBase.h"
#include "Render/ShaderFramework/Shader.h"
#include "Render/SkeletonAnimation/Skeleton.h"
#include "Render/Textures/Texture.h"
#include "Kernel/Time/Timer.h"


//#define TEST_SHADER_TEXTURE

#if defined(TEST_SHADER_TEXTURE)
#include "SOIL.h"
//u32     g_textureHandle = -1;

#endif //TEST_SHADER_TEXTURE

//--------------------------------------------------------------------------
CSceneRenderableNode::CSceneRenderableNode()
{

#if defined(TEST_SHADER_TEXTURE)
    //static bool once = true;
    //if(once)
    //{
    //u32 g_textureHandle = SOIL_load_OGL_texture( "e:\\Programming\\Workspace GameDev\\Workspace Licenta\\Game\\Data\\textures\\caramide.png", 0, 0, SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MIPMAPS );
    //gl::BindTexture( gl::TEXTURE_2D, g_textureHandle );
    //}
    //once = false;
#endif //TEST_SHADER_TEXTURE
}

//--------------------------------------------------------------------------
CSceneRenderableNode::~CSceneRenderableNode()
{
}

//--------------------------------------------------------------------------
//void CSceneRenderableNode::OnDraw ( const CSceneGraph* sceneGraph )const
//{
//
//RENDER_GUARD_BLOCK
//
//
//
//    if(!m_skeleton)
//    {
//        return;
//    }
//    
//    DECLARE_PROFILE_SCOPED("CSceneRenderableNode::OnDraw");
//
//#if defined(TEST_SHADER_TEXTURE)
//    Soil_TextureHeader header;
//    ThZeroMemoryTmpl( header );
//
//    static u32 specTextureUniformLocation = gl::GetUniformLocation( CShader::GetCurrentShader()->GetID(), "specTexture");
//    static u32 textureUniformLocation = gl::GetUniformLocation( CShader::GetCurrentShader()->GetID(), "myTexture" );
//    static u32 greenTextureUniform = gl::GetUniformLocation( CShader::GetCurrentShader()->GetID(), "greenTexture" );
//    
//    
//    gl::ActiveTexture(gl::TEXTURE0 + 2);
//    //static u32 g_textureHandle = DebugLoadTexture( "e:\\Programming\\Workspace GameDev\\Workspace Licenta\\Game\\Data\\textures\\caramide.tres");
//    static u32 g_textureHandle = SOIL_load_OGL_texture( "e:\\Programming\\Workspace GameDev\\Workspace Licenta\\Game\\Data\\textures\\caramide.png", 0, 0, /*SOIL_FLAG_COMPRESS_TO_DXT |*/ SOIL_FLAG_MIPMAPS, &header );
//
//
//    //static const CString greenPath = "e:\\Programming\\Workspace GameDev\\Workspace Licenta\\Game\\Data\\textures\\verde.jpg";
//    gl::ActiveTexture(gl::TEXTURE0 +3);
//    static const CString greenPath = "e:\\Programming\\Workspace GameDev\\Workspace Licenta\\Game\\Data\\textures\\verde.tres";
//    
//    //static u32 g_greenTexture = SOIL_load_OGL_texture( greenPath, 0, 0, SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MIPMAPS, &header );
//    static u32 g_greenTexture = DebugLoadTexture( greenPath );
//    
//
//    static const CString specPath = "e:\\Programming\\Workspace GameDev\\Workspace Licenta\\Game\\Data\\textures\\spec.tres";
//    //static u32 g_specTexture = SOIL_load_OGL_texture( specPath, 0, 0, SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MIPMAPS, &header );
//    gl::ActiveTexture( gl::TEXTURE0 + 4);
//    static u32 g_specTexture = DebugLoadTexture( specPath );
//
//    //for( u32 i=0; i < 30; i++ )
//    //{
//    //    u32 textureUnit = i;
//    //    gl::ActiveTexture(gl::TEXTURE0 + textureUnit);
//    //    gl::BindTexture( gl::TEXTURE_2D, g_textureHandle );
//    //    //gl::BindSampler( textureUnit, textureUniformLocation );
//    //    //gl::Uniform1i(textureUniformLocation, textureUnit );
//    //}
//    static Bool once = true;
//    if( once )
//    {
//        u32 textureUnit = 2;
//        gl::ActiveTexture(gl::TEXTURE0 + textureUnit);
//        gl::BindTexture( gl::TEXTURE_2D, g_textureHandle );
//        //gl::BindSampler( textureUnit, textureUniformLocation );
//        gl::Uniform1i(textureUniformLocation, textureUnit );
//
//        textureUnit++;
//        gl::ActiveTexture(gl::TEXTURE0 + textureUnit);
//        gl::BindTexture( gl::TEXTURE_2D, g_greenTexture );
//        //gl::BindSampler( textureUnit, textureUniformLocation );
//        gl::Uniform1i(greenTextureUniform, textureUnit );
//
//        textureUnit++;
//        gl::ActiveTexture(gl::TEXTURE0 + textureUnit);
//        gl::BindTexture( gl::TEXTURE_2D, g_specTexture );
//        //gl::BindSampler( textureUnit, textureUniformLocation );
//        gl::Uniform1i(specTextureUniformLocation, textureUnit );
//    }
//    once = false;
//#endif 
//
//
//    if( m_skeleton )
//    {
//        RENDER_GUARD_BLOCK
//
//        DECLARE_PROFILE_SCOPED("Skeleton shader matrices update");
//
//        // const thVector<m4x4>& boneMatrices = m_skeleton->GetBoneMatrices();
//        //CShader::GetCurrentShader()->SetBoneMatrices(boneMatrices);
//
//        m_skeleton->BindGPU();
//
//        CShader::GetCurrentShader()->EnableSkinning(true);
//    }
//
//    u64 size = m_meshes.GetSize();
//    
//    /*gl::PolygonMode( gl::FRONT_AND_BACK, gl::LINE );*/
//
//    for( u64 i=0; i<size; i++  )
//    {
//        THOT_ASSERT(m_meshes[i]);// mesh list must not contain null objectecs because there is no sense to do this;
//        m_meshes[i]->OnDraw();
//    }
//   
//    if( m_skeleton )
//    {
//        CShader::GetCurrentShader()->EnableSkinning(false);
//    }
//
//#ifdef _DEBUG
//    if( m_skeleton )
//    {
//        //m_skeleton->DebugDraw();        
//    }
//#endif /*_DEBUG*/
//
//}

//--------------------------------------------------------------------------
void CSceneRenderableNode::OnInit()
{
    //[TODO]
}

//--------------------------------------------------------------------------
void CSceneRenderableNode::OnUpdateThis( float fDeltaTime )
{
    DECLARE_PROFILE_SCOPED("CSceneRenderableNode::OnUpdate");

    //if( m_skeleton )
    //{

    //    m_skeleton->Update( fDeltaTime );

    //}

    // the draw calls are not actually made here; the drawing is deferred and made on another step
    //m_graphicComponent.OnDraw( );
}

////--------------------------------------------------------------------------
//u32 CSceneRenderableNode::GetMeshCount( )const
//{
//    return (u32)m_meshes.GetSize();
//}
//
////--------------------------------------------------------------------------
//IMesh* CSceneRenderableNode::GetMesh ( u32 index )
//{
//    return m_meshes[index];
//}
//
////--------------------------------------------------------------------------
//const IMesh* CSceneRenderableNode::GetMesh( u32 index )const
//{
//    return m_meshes[index];
//}

//-----------------------------------------------------------------------------
void CSceneRenderableDemo::OnInit()
{
}

//-----------------------------------------------------------------------------
void CSceneRenderableDemo::OnUpdateThis( float fDeltaTime )
{
}