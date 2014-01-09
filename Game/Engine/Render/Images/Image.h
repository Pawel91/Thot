#pragma once
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Kernel\Kernel.h"
#include "Render\Images\ImageTypes.h"

struct tPixRGBA
{
    byte r,g,b,a;
};

struct tPixRGB
{
    byte r,g,b;
};



class CImage
{
//******CONSTRUCTORS
protected:
         CImage        ( ){}

public:
virtual ~CImage        ( );



//******INTERFACE
public:
virtual         Bool                Load                ( const char* szFileName )      = 0;
virtual         void                Release             ( ){}
virtual         byte*               GetImageData        ( )                             = 0;
virtual         const byte*         GetImageData        ( )const                        = 0;
virtual         int                 GetWidth            ( )const                        = 0;
virtual         int                 GetHeight           ( )const                        = 0;
virtual         int                 GetColorDepth       ( )const                        = 0;
virtual         int                 GetByteCount        ( )const;
virtual         ePixelFormat        GetPixelFormat      ( )const                        = 0;
virtual         ePixelType          GetPixelType        ( )const                        = 0;


virtual        Bool                 FlipVertical        ( )        { return false;}

//*******STATIC FUNCTIONS
public:


//Factory:
static         CImage*             s_CreateImage       ( eImageExtension imgExt );

};



#endif /*__IMAGE_H__*/