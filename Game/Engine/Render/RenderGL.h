#pragma once
#ifndef __RENDER_GL_H__
#define __RENDER_GL_H__

#include "GLExtension.h"

#include "Render.h"
#include "RenderCamera.h"
#include "Render\ShaderFramework\Shader.h"

class CSkybox;
class CTerrainBase;

//TODO: remove skybox from this class and move to terrain;
//TODO: remove terrain from this class and move it somewhere;
class CRenderGL:public CRender
{
//**********CONSTRUCTORS
public:
                CRenderGL        ( );
virtual        ~CRenderGL        ( );

//***********INTERFACE

virtual     void                AddRenderer             ( CRenderer* renderer )                             override;
virtual     Bool                Init                    ( )                             override;
virtual     Bool                ShutDown                ( )                             override;
virtual     void                Render                  ( )                             override;
virtual     void                SetupProjection         ( )                             override;
virtual     CRenderCamera*      GetCamera               ( )                             override;
virtual     int                 GetWidth                ( )const                        override; 
virtual     int                 GetHeight               ( )const                        override; 
virtual     void                StartRender             ( )                             override;
virtual     Bool                EndRender               ( )                             override; // return false if an error ocured durring rendering;
virtual     const char*         GetRenderErrMessage     ( )const                        override;
virtual     void                SetWidth                ( u32 width)                    override;
virtual     void                SetHeight               ( u32 height)                   override;
virtual     void                DbgVerifyRenderState    ( )                             override;


//***********Lighting ************
virtual     void                SetupLights             ( )const                            override;



//////BEGIN REFACTOR
            thVector<CRenderer*>     m_renderers;
/////END REFACTOR

protected:


            u32                     m_windowsWidth;
            u32                     m_windowsHeight;
            CRenderCamera*          m_pRenderCamera;
            CSkybox*                m_skybox;
mutable     CShader*                m_shader;
    

mutable GLenum                  m_glErr;
};



#endif /*__RENDER_GL_H__*/