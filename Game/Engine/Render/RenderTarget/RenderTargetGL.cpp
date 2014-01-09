#include "Render_PCH.h"
#include "RenderTargetGL.h"
#include "Render\RenderGL.h"


CRenderTargetGL::CRenderTargetGL( )
:m_pTargetTexture       ( NULL )
,m_nFrameBufferID       ( 0 )
{
    gl::GenFramebuffers( 1, &m_nFrameBufferID );
    gl::BindFramebuffer( gl::FRAMEBUFFER, m_nFrameBufferID );
}

CRenderTargetGL::~CRenderTargetGL( )
{

}

CTexture* CRenderTargetGL::GetTexture( ) const
{
    return NULL;
}

Bool CRenderTargetGL::IsValid( ) const
{
    return false;
}

u32  CRenderTargetGL::GetWidth( ) const
{
    return 0;
}

u32  CRenderTargetGL::GetHeight( ) const
{
    return 0;
}


