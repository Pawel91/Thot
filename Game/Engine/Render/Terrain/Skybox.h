#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "Kernel/DataStructures/Array/Array.h"
#include "Kernel/Kernel.h"

enum eSkyboxFace
{
    E_SKYBOX_FACE_NONE        = -1
    ,E_SKYBOX_FACE_FRONT
    ,E_SKYBOX_FACE_BACK
    ,E_SKYBOX_FACE_LEFT
    ,E_SKYBOX_FACE_RIGHT
    ,E_SKYBOX_FACE_TOP
    ,E_SKYBOX_FACE_BOTTOM

    ,E_SKYBOX_FACE_COUNT

    ,E_SKYBOX_FORCE_DWORD = FORCE_DWORD
};


class CTexture;

template class RENDER_API CStaticArray<CTexture*,E_SKYBOX_FACE_COUNT>;
typedef CStaticArray<CTexture*,E_SKYBOX_FACE_COUNT> tSkyTextureArray;



class RENDER_API CSkybox
{
public:

            CSkybox();
virtual     ~CSkybox();


virtual        void        Load                 ( const char* front, const char* back, const char* left, const char* right, const char* top, const char* bottom );            
virtual        void        OnDraw               ( )const;
virtual        void        SetSize              ( float fSize);

protected:
virtual        void        OnDrawTop            ( )const;
virtual        void        OnDrawBottom         ( )const;
virtual        void        OnDrawFront          ( )const;
virtual        void        OnDrawBack           ( )const;
virtual        void        OnDrawLeft           ( )const;
virtual        void        OnDrawRight          ( )const;

    tSkyTextureArray        m_aTextures;    
    float                   m_fSize;
};


#endif /*__SKYBOX_H__*/