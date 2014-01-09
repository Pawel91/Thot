#pragma once
#ifndef __TARGA_IMAGE_H__
#define __TARGA_IMAGE_H__


#include "Image.h"
#include "stdio.h"

enum eTargaType
{
     E_TGA_TYPE_NO_IMAGE_DATA
    
    ,E_TGA_TYPE_INDEXED                     = 1
    ,E_TGA_TYPE_RGB                         = 2
    ,E_TGA_TYPE_GRAYSCALE                   = 3
        
    ,E_TGA_TYPE_INDEXED_RLE                 = 9
    ,E_TGA_TYPE_RGB_RLE                     = 10
    ,E_TGA_TYPE_GRAYSCALE_RLE               = 11

    ,E_TGA_TYPE_FORCE_DWORD = FORCE_DWORD
};


enum eTgaImgOrigin
{
     E_TGA_ORIGIN_BOTTOM_LEFT       = 0x00
    ,E_TGA_ORIGIN_BOTTOM_RIGHT      = 0x10
    ,E_TGA_ORIGIN_TOP_LEFT          = 0x20
    ,E_TGA_ORIGIN_TOP_RIGHT         = 0x30
};

struct tTargaHeader
{
    byte            m_idLength;                 //!!    Lenght of an indentifier string located after the header.     
    byte            m_colorMapType;    
    byte            m_imageTypeCode;            //!!    Type of targa image that you are loading
    byte            m_colorMapSpec[5];        
    word            m_xOrigin;            
    word            m_yOrigin;            
    word            m_width;                    //!! width of image
    word            m_height;                   //!! height of image
    byte            m_bpp;                      //!! bits per pixel
    byte            m_imageDesc;                //!! byte whose bits specify the number of attribute per pixel and the order in with pixel data
                                                //    is transferred from a file to the screen;
                                                // bits 4-5 tels use where is the origin of the image;
};


//TODO: wrap image data into a safe array;
class CTargaImg:public CImage
{
friend class CImage;
//********CONSTRUCTORS
protected:
             CTargaImg();

public:
virtual     ~CTargaImg();

//*********INTERFACE
public:

virtual         Bool            Load                ( const char* szFileName )          override;
virtual         void            Release             ( )                                 override;
virtual         byte*           GetImageData        ( )                                 override;
virtual         const byte*     GetImageData        ( )const                            override;
virtual         int             GetWidth            ( )const                            override;
virtual         int             GetHeight           ( )const                            override;
virtual         Bool            FlipVertical        ( )                                 override;
virtual         int             GetColorDepth       ( )const                            override;

virtual         ePixelFormat    GetPixelFormat      ( )const override       { return m_ePixelFormat;}
virtual         ePixelType      GetPixelType        ( )const override       { return m_ePixelType;}


virtual        Bool             ConvertRGBAToRGB    ( );
virtual        Bool             ConvertRGBToRGBA    ( byte alphaValue);



//********HELPER FUNCTIONS
protected:

            void            ReadCompressed          ( FILE* pFile, int nColorMode );
            void            ReadUncompressed        ( FILE* pFile );
            void            SwapRedBlue             ( );


//*********MEMBERS
protected:
            byte*           m_pImageData;    
            byte            m_colorDepth;        // bits per pixel
            ePixelType      m_ePixelType;
            ePixelFormat    m_ePixelFormat;
            word            m_width;
            word            m_height;    
            dword           m_imageSize;        // size of imageData in bytes
};

#endif /*__TARGA_IMAGE_H__*/