#include "Render_PCH.h"
#include "Skybox.h"
#include "Render\Textures\Texture.h"
#include "Render\RenderGL.h"
CSkybox::CSkybox()
:m_fSize        ( 0.f )
{
    for( int i=0; i<m_aTextures.GetSize(); i++ )
    { 

        //m_aTextures[i] = CTexture::s_CreateTexture(E_TEXTURE_TYPE_2D);
        if( m_aTextures[i] )
        {
            //m_aTextures[i]->SetWrapModeAll( E_WRAP_MODE_CLAMP_TO_EDGE );
        }
    }
}

CSkybox::~CSkybox()
{
    //for( int i=0; i<m_aTextures.GetSize();  i++ )
    //{
    //    THOT_DELETE(m_aTextures[i]);
    //}
}


void CSkybox::Load ( const char* front, const char* back, const char* left, const char* right, const char* top, const char* bottom )
{
    //m_aTextures[E_SKYBOX_FACE_FRONT]->  LoadFromImage(front);
    //m_aTextures[E_SKYBOX_FACE_BACK]->   LoadFromImage(back);
    //m_aTextures[E_SKYBOX_FACE_LEFT]->   LoadFromImage(left);
    //m_aTextures[E_SKYBOX_FACE_RIGHT]->  LoadFromImage(right);
    //m_aTextures[E_SKYBOX_FACE_TOP]->    LoadFromImage(top);
    //m_aTextures[E_SKYBOX_FACE_BOTTOM]-> LoadFromImage(bottom);

}

void CSkybox::OnDraw ()const
{
    return;

    static CRenderCamera* cam = CRender::GetInstance()->GetCamera();
    tVect3 vCamPos;
    cam->GetPos(vCamPos);

    OnDrawTop   ( );
    OnDrawBottom( );
    OnDrawFront ( );
    OnDrawBack  ( );
    OnDrawLeft  ( );
    OnDrawRight ( );
    
}

//#define WRAP_INSIDE
void CSkybox::OnDrawTop ( )const
{
    CTexture* pTexture = m_aTextures[E_SKYBOX_FACE_TOP];
    //m_aTextures[E_SKYBOX_FACE_TOP]->Bind();

    //CRender::s_BeginRenderPrimitive(E_GEOMETRIC_PRIMITIVE_QUADS);
    //    gl::TexCoord2f(1.0f, 1.0f); gl::Vertex3f(-m_fSize, m_fSize, -m_fSize);
    //    gl::TexCoord2f(0.0f, 1.0f); gl::Vertex3f(m_fSize, m_fSize, -m_fSize);
    //    gl::TexCoord2f(0.0f, 0.0f); gl::Vertex3f(m_fSize, m_fSize, m_fSize);
    //    gl::TexCoord2f(1.0f, 0.0f); gl::Vertex3f(-m_fSize, m_fSize, m_fSize);
    //CRender::s_EndRenderPrimitive();
    //m_aTextures[E_SKYBOX_FACE_TOP]->Unbind();
}

void CSkybox::OnDrawBottom ( )const
{
    // Bottom
    //gl::BindTexture(*m_aTextures[E_SKYBOX_FACE_BOTTOM]); 


    //gl::Begin(gl::QUADS);
    //    gl::TexCoord2f(1.0f, 1.0f); gl::Vertex3f(m_fSize, -m_fSize, -m_fSize);
    //    gl::TexCoord2f(0.0f, 1.0f); gl::Vertex3f(-m_fSize, -m_fSize, -m_fSize);
    //    gl::TexCoord2f(0.0f, 0.0f); gl::Vertex3f(-m_fSize, -m_fSize, m_fSize);
    //    gl::TexCoord2f(1.0f, 0.0f); gl::Vertex3f(m_fSize, -m_fSize, m_fSize);
    //gl::End();

    //gl::UnbindTexture(*m_aTextures[E_SKYBOX_FACE_RIGHT]);
}

void CSkybox::OnDrawFront ( )const
{
    // Front
    //gl::BindTexture(*m_aTextures[E_SKYBOX_FACE_FRONT]);

    //gl::Begin(gl::QUADS);
    //gl::TexCoord2f(0.0f, 0.0f); gl::Vertex3f(-m_fSize, -m_fSize, -m_fSize);
    //gl::TexCoord2f(1.0f, 0.0f); gl::Vertex3f(m_fSize, -m_fSize, -m_fSize);
    //gl::TexCoord2f(1.0f, 1.0f); gl::Vertex3f(m_fSize, m_fSize, -m_fSize);
    //gl::TexCoord2f(0.0f, 1.0f); gl::Vertex3f(-m_fSize, m_fSize, -m_fSize);
    //gl::End();

    //gl::UnbindTexture(*m_aTextures[E_SKYBOX_FACE_RIGHT]);
}

void CSkybox::OnDrawBack ( )const
{
    // Back
    //gl::BindTexture(*m_aTextures[E_SKYBOX_FACE_BACK]);

    //gl::Begin( gl::QUADS );
    //    gl::TexCoord2f(0.0f, 0.0f); gl::Vertex3f(m_fSize, -m_fSize, m_fSize);
    //    gl::TexCoord2f(1.0f, 0.0f); gl::Vertex3f(-m_fSize, -m_fSize, m_fSize);
    //    gl::TexCoord2f(1.0f, 1.0f); gl::Vertex3f(-m_fSize, m_fSize, m_fSize);
    //    gl::TexCoord2f(0.0f, 1.0f); gl::Vertex3f(m_fSize, m_fSize, m_fSize);
    //gl::End();
    //gl::UnbindTexture(*m_aTextures[E_SKYBOX_FACE_RIGHT]);
}

void CSkybox::OnDrawLeft ( )const
{
    // Left
    //gl::BindTexture(*m_aTextures[E_SKYBOX_FACE_LEFT] );

    //gl::Begin(gl::QUADS);
    //    gl::TexCoord2f(1.0f, 0.0f); gl::Vertex3f(-m_fSize, -m_fSize, -m_fSize);
    //    gl::TexCoord2f(1.0f, 1.0f); gl::Vertex3f(-m_fSize, m_fSize, -m_fSize); 
    //    gl::TexCoord2f(0.0f, 1.0f); gl::Vertex3f(-m_fSize, m_fSize, m_fSize);
    //    gl::TexCoord2f(0.0f, 0.0f); gl::Vertex3f(-m_fSize, -m_fSize, m_fSize);
    //gl::End();
    //gl::UnbindTexture(*m_aTextures[E_SKYBOX_FACE_RIGHT]);
}

void CSkybox::OnDrawRight ( )const
{
    // Right
    //gl::BindTexture( *m_aTextures[E_SKYBOX_FACE_RIGHT]);

    //gl::Begin( gl::QUADS );
    //    gl::TexCoord2f(1.0f, 0.0f); gl::Vertex3f(m_fSize, -m_fSize, m_fSize);
    //    gl::TexCoord2f(1.0f, 1.0f); gl::Vertex3f(m_fSize, m_fSize, m_fSize);
    //    gl::TexCoord2f(0.0f, 1.0f); gl::Vertex3f(m_fSize, m_fSize, -m_fSize);
    //    gl::TexCoord2f(0.0f, 0.0f); gl::Vertex3f(m_fSize, -m_fSize, -m_fSize);
    //gl::End();
    //gl::UnbindTexture(*m_aTextures[E_SKYBOX_FACE_RIGHT]);
}


void CSkybox::SetSize (float fSize)
{
    m_fSize = fSize;
}