#include "Render_PCH.h"
#include "Image.h"
#include "TargaImg.h"
CImage::~CImage ( )
{
    this->Release();
}

int CImage::GetByteCount ( )const
{
    THOT_ASSERT(GetColorDepth()%8 == 0);
    return GetWidth() * GetHeight() * ( GetColorDepth()/8 );
}

CImage* CImage::s_CreateImage ( eImageExtension imgExt )
{
    switch( imgExt )
    {
    case E_IMAGE_EXTENSION_TGA:
        {
            return THOT_NEW CTargaImg;
        break;
        }

    default:
        THOT_ASSERT(0);//unsuported extension
        return NULL;
    break;
    }

}
