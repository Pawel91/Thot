#include "Render_PCH.h"
#include "TargaImg.h"


CTargaImg::CTargaImg()
:m_pImageData           (NULL)    
,m_colorDepth           ( 0 )
,m_ePixelType           ( E_PIXEL_TYPE_NONE )
,m_ePixelFormat         ( E_PIXEL_FORMAT_NONE )
,m_width                ( 0 )
,m_height               ( 0 )
,m_imageSize            ( 0 )
{
}

CTargaImg::~CTargaImg()
{
    Release();
}


Bool CTargaImg::Load ( const char* szFileName )
{
#ifndef _MSC_VER
    FILE* pFile = fopen( szFileName, "rb");
    if( !pFile )
    {
        THOT_TRACE("ERROR!    COULD NOD LOAD TARGA FILE\n");
        return false;
    }
#else
    FILE* pFile;
    if( fopen_s(&pFile, szFileName, "rb") !=0 )
    {
        THOT_TRACE("ERROR!    COULD NOT OPEN TARGA FILE: %s \n", szFileName);
        return false;
    }
#endif

    tTargaHeader tgaHeader;

    //read the targa header
    fread( &tgaHeader, 1, sizeof(tTargaHeader), pFile  );

    //check to see if the image type is one that we support
    if(    (    tgaHeader.m_imageTypeCode != E_TGA_TYPE_RGB
        &&    tgaHeader.m_imageTypeCode != E_TGA_TYPE_GRAYSCALE
        &&    tgaHeader.m_imageTypeCode != E_TGA_TYPE_RGB_RLE
        &&    tgaHeader.m_imageTypeCode != E_TGA_TYPE_GRAYSCALE_RLE
        )
        ||    tgaHeader.m_colorMapType != 0  
        )
    {
        fclose(pFile);
        THOT_TRACE("ERROR!    TARGA TYPE NOT SUPPORTED! FILE:[ %s ] COULD NOT BE LOADED\n", szFileName );
        return false;
    }


    m_width = tgaHeader.m_width;
    m_height = tgaHeader.m_height;

    // colormode -> 3 = BGR, 4 = BGRA
    int nColorMode = tgaHeader.m_bpp/8;

    //if( nColorMode < 3 )
    //{
    //    fclose(pFile);
    //    THOT_TRACE("ERROR!    TARGA TYPE NOT SUPPORTED DUE TO COLOR DEPTH = [%d]! FILE:[ %s ] COULD NOT BE LOADED\n", tgaHeader.m_bpp, szFileName );
    //    return false;
    //}

    m_imageSize = m_width * m_height * nColorMode;

    if( m_pImageData )
        Release();
    //allocate memory for TGA image data
    m_pImageData = THOT_MALLOC_TYPE( m_imageSize, byte);

    //skip past the id if there is one
    if( tgaHeader.m_idLength > 0  )
    {
        fseek( pFile, SEEK_CUR, tgaHeader.m_idLength );
    }

    if( tgaHeader.m_imageTypeCode == E_TGA_TYPE_RGB || tgaHeader.m_imageTypeCode == E_TGA_TYPE_GRAYSCALE )
    {
        ReadUncompressed(pFile);
    }
    else
    {
        ReadCompressed(pFile, nColorMode);    
    }

    fclose(pFile);
    
    switch(tgaHeader.m_imageTypeCode)
    {
    case E_TGA_TYPE_RGB:
    case E_TGA_TYPE_RGB_RLE:
        if ( nColorMode == 3)
        {
            m_ePixelFormat  = E_PIXEL_FORMAT_RGB;
            m_ePixelType    = E_PIXEL_TYPE_UNSIGNED_BYTE;
            m_colorDepth    = 24;
        }
        else
        {
            m_ePixelFormat  = E_PIXEL_FORMAT_RGBA;
            m_ePixelType    = E_PIXEL_TYPE_UNSIGNED_BYTE;
            m_colorDepth    = 32;
        }
        break;

    case E_TGA_TYPE_GRAYSCALE:
    case E_TGA_TYPE_GRAYSCALE_RLE:
    {
        m_ePixelFormat  = E_PIXEL_FORMAT_LUMINANCE;
        m_ePixelType    = E_PIXEL_TYPE_UNSIGNED_BYTE;
        m_colorDepth    = 8;
    }
    break;

    default:
        THOT_ASSERT(0);
    break;
    }

    if ((tgaHeader.m_imageDesc & E_TGA_ORIGIN_TOP_LEFT) == E_TGA_ORIGIN_TOP_LEFT)
        FlipVertical();

    // swap the red and blue components in the image data; if the color depth suports;
    SwapRedBlue();

    return true;
}

void CTargaImg::Release ( )
{
    if( m_pImageData )
    {
        //THOT_DELETE_ARR(m_pImageData);
        THOT_FREE(m_pImageData);
    }
}

byte* CTargaImg::GetImageData ( )
{
    return m_pImageData;
}

const byte* CTargaImg::GetImageData ( )const
{
    return m_pImageData;
}

int CTargaImg::GetWidth ()const
{
    return m_width;
}

int CTargaImg::GetHeight ()const
{
    return m_height;
}

int CTargaImg::GetColorDepth ( )const
{
    return (int)m_colorDepth;
}

Bool CTargaImg::FlipVertical ( )
{
    if (!m_pImageData)
        return false;

    if (m_colorDepth == 32)
    {
        tPixRGBA* tmpBits = THOT_NEW_ARR tPixRGBA[m_width];
    
        int lineWidth = m_width * 4;

        tPixRGB* top = (tPixRGB*)m_pImageData;
        tPixRGB* bottom = (tPixRGB*)(m_pImageData + lineWidth*(m_height-1));

        for (int i = 0; i < (m_height / 2); ++i)
        {
            memcpy(tmpBits, top, lineWidth); 
            memcpy(top, bottom, lineWidth);
            memcpy(bottom, tmpBits, lineWidth);

            top = (tPixRGB*)((byte*)top + lineWidth);
            bottom = (tPixRGB* )((byte*)bottom - lineWidth);
        }

        THOT_DELETE_ARR(tmpBits);
    }
    else if (m_colorDepth == 24)
    {
        tPixRGB* tmpBits = THOT_NEW_ARR tPixRGB[m_width];

        int lineWidth = m_width * 3;

        tPixRGB* top = (tPixRGB*)m_pImageData;
        tPixRGB* bottom = (tPixRGB*)(m_pImageData + lineWidth*(m_height-1));

        for (int i = 0; i < (m_height / 2); ++i)
        {
            memcpy(tmpBits, top, lineWidth); 
            memcpy(top, bottom, lineWidth);
            memcpy(bottom, tmpBits, lineWidth);

            top = (tPixRGB*)((byte*)top + lineWidth);
            bottom = (tPixRGB*)((byte*)bottom - lineWidth);
        }

        THOT_DELETE_ARR(tmpBits);
    }

    return true;
}

void CTargaImg::SwapRedBlue ( )
{
    switch (m_colorDepth)
    {
    case 32:
        {
            byte temp;
            tPixRGBA* source = (tPixRGBA*)m_pImageData;

            int nSize = (m_width * m_height);
            for (int pixel = 0; pixel < nSize; ++pixel)
            {
                temp = source[pixel].b;
                source[pixel].b = source[pixel].r;
                source[pixel].r = temp;
            }
        } break;
    case 24:
        {
            int nSizeOF = sizeof(tPixRGB);
            byte temp;
            tPixRGB* source = (tPixRGB*)m_pImageData;

            int nSize = (m_width * m_height);
            for (int pixel = 0; pixel < nSize; ++pixel)
            {
                temp = source[pixel].b;
                source[pixel].b = source[pixel].r;
                source[pixel].r = temp;
            }
        } break;
    default:
        // ignore other color depths
        break;
    }
}


void CTargaImg::ReadCompressed ( FILE* pFile, int nColorMode )
{
    // this is an RLE compressed image
    byte id;
    byte length;
    tPixRGBA color = { 0, 0, 0, 0 };
    unsigned int i = 0;

    while (i < m_imageSize)
    {
        id = fgetc(pFile);

        // see if this is run length data
        if (id >= 128)// & 0x80)
        {
            // find the run length
            length = (byte)(id - 127);

            // next 3 (or 4) bytes are the repeated values
            color.b = (byte)fgetc(pFile);
            color.g = (byte)fgetc(pFile);
            color.r = (byte)fgetc(pFile);

            if (nColorMode == 4)
                color.a = (byte)fgetc(pFile);

            // save everything in this run
            while (length > 0)
            {
                m_pImageData[i++] = color.b;
                m_pImageData[i++] = color.g;
                m_pImageData[i++] = color.r;

                if (nColorMode == 4)
                    m_pImageData[i++] = color.a;

                --length;
            }
        }
        else
        {
            // the number of non RLE pixels
            length = byte(id + 1);

            while (length > 0)
            {
                color.b = (byte)fgetc(pFile);
                color.g = (byte)fgetc(pFile);
                color.r = (byte)fgetc(pFile);

                if (nColorMode == 4)
                    color.a = (byte)fgetc(pFile);

                m_pImageData[i++] = color.b;
                m_pImageData[i++] = color.g;
                m_pImageData[i++] = color.r;

                if (nColorMode == 4)
                    m_pImageData[i++] = color.a;

                --length;
            }
        }
    }
}

void CTargaImg::ReadUncompressed ( FILE* pFile )
{
    //uncompressed targa; just read to image data;
    fread( m_pImageData, 1, m_imageSize, pFile  );
}


Bool CTargaImg::ConvertRGBAToRGB ()
{
    //if ((m_colorDepth == 32) && (m_imageDataFormat == IMAGE_RGBA))
    if ((m_colorDepth == 32) && (m_ePixelFormat == E_PIXEL_FORMAT_RGBA))
    {
        tPixRGB *newImage = THOT_NEW_ARR tPixRGB[m_width * m_height];

        if (!newImage)
            return false;

        tPixRGB *dest = newImage;
        tPixRGBA *src = (tPixRGBA*)m_pImageData;

        for (int x = 0; x < m_height; x++)
        {
            for (int y = 0; y < m_width; y++)
            {
                dest->r = src->r;
                dest->g = src->g;
                dest->b = src->b;

                ++src;
                ++dest;
            }
        }

        THOT_DELETE_ARR(m_pImageData);
        //delete [] m_pImageData;
        m_pImageData = (byte*)newImage;

        m_colorDepth = 24;
        m_ePixelType = E_PIXEL_TYPE_UNSIGNED_BYTE;
        m_ePixelFormat = E_PIXEL_FORMAT_RGB;

        return true;
    }

    return false;
}

Bool CTargaImg::ConvertRGBToRGBA ( byte alphaValue)
{
    /*if ((m_colorDepth == 24) && (m_imageDataFormat == IMAGE_RGB))*/
    if ((m_colorDepth == 24) && (m_ePixelFormat == E_PIXEL_FORMAT_RGB))
    {
        /*rgba_t *newImage = new rgba_t[m_width * m_height];*/
        tPixRGBA *newImage = THOT_NEW_ARR tPixRGBA[m_width * m_height];

        if (!newImage)
            return false;

        tPixRGBA *dest = newImage;
        tPixRGB *src = (tPixRGB*)m_pImageData;

        for (int x = 0; x < m_height; x++)
        {
            for (int y = 0; y < m_width; y++)
            {
                dest->r = src->r;
                dest->g = src->g;
                dest->b = src->b;
                dest->a = alphaValue;

                ++src;
                ++dest;
            }
        }

        THOT_DELETE_ARR( m_pImageData);
        m_pImageData = (byte*)newImage;

        m_colorDepth = 32;
    
        m_ePixelType = E_PIXEL_TYPE_UNSIGNED_BYTE;
        m_ePixelFormat = E_PIXEL_FORMAT_RGBA;
        return true;
    }

    return false;
}
