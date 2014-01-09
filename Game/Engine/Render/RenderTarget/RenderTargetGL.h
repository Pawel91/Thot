#pragma once
#ifndef __RENDER_TARGET_GL_H__
#define __RENDER_TARGET_GL_H__

#include "RenderTarget.h"


class CRenderTargetGL: public IRenderTarget
{

//***************************************
//*************CONSTRUCTORS**************
//***************************************
public:
                CRenderTargetGL( );
virtual        ~CRenderTargetGL( );


//***************************************
//*************INTERFACE*****************
//***************************************
public:


virtual         CTexture*           GetTexture      ( ) const               override;    
virtual         Bool                IsValid         ( ) const               override;
virtual         u32                 GetWidth        ( ) const               override;
virtual         u32                 GetHeight       ( ) const               override;



//***************************************
//*************MEMBERS*******************
//***************************************
protected:
    CTexture*               m_pTargetTexture;
    u32                     m_nFrameBufferID;  
    
};


#endif /*__RENDER_TARGET_GL_H__*/