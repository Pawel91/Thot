#pragma once
#ifndef __RENDER_TARGET_H__
#define __RENDER_TARGET_H__


#include "Kernel\Kernel.h"
#include "Render\Textures\TextureTypes.h"
//#include "Render\RenderDef.h"

class CTexture;

class IRenderTarget
{
//*************CONSTRUCTORS
public:

virtual     ~IRenderTarget()                = 0;



//*************INTERFACE
public:

virtual         CTexture*           GetTexture      ( ) const                               = 0;    
virtual         Bool                IsValid         ( ) const                               = 0;
virtual         u32                 GetWidth        ( ) const                               = 0;
virtual         u32                 GetHeight       ( ) const                               = 0;


//*************MEMBERS
protected:

};



#endif /*__RENDER_TARGET_H__*/