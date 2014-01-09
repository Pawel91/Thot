#ifndef __RENDER_H__
#define __RENDER_H__

#include "Render/RenderDef.h"
#include "Kernel/Basics.h"
#include "Kernel/Singleton.h"
#include "RenderTypes.h"



class CLightBase;
class CRenderCamera;
class CLightModel;
class CRenderer;
//=============== RENDER INTERFACE =========================================

class RENDER_API CRender 
{
THOT_DECLARE_SINGLETON(CRender)
//*******CONSTRUCTORS
public:
            CRender     ( ) { }
virtual     ~CRender    ( ) { };


//******INTERFACE
virtual     void                    AddRenderer                 ( CRenderer* renderer)      = 0;
virtual     Bool                    Init                        ( )                         = 0;
virtual     Bool                    ShutDown                    ( )                         = 0;
virtual     void                    Render                      ( )                         = 0;
virtual     void                    SetupProjection             ( )                         = 0; 
virtual     CRenderCamera*          GetCamera                   ( )                         = 0;
virtual     int                     GetWidth                    ( )const                    = 0;
virtual     int                     GetHeight                   ( )const                    = 0;
virtual     void                    StartRender                 ( )                         = 0;
virtual     Bool                    EndRender                   ( )                         = 0; // return false if an error ocured durring rendering;
virtual     const char*             GetRenderErrMessage         ( )const                    = 0; // error message if an error ocured durring rendering;
virtual     void                    SetWidth                    ( u32 width )               = 0;
virtual     void                    SetHeight                   ( u32 height )              = 0;


            void                    DebugDraw                   ();

//************* Lighting ********

/**
    When the light is enabled the current light model is also set;
*/
virtual     void                SetupLights                 ( )const                                = 0;


/**
    Debug functios use to THOT_TRACE error in render
*/
virtual     void                DbgVerifyRenderState        ( )                                 = 0;


};






#if defined( THOT_ENABLE_DEBUG )
#define RENDER_VERIFY                                       \
do                                                          \
{                                                           \
    if( CRender::GetInstance() )                          \
    {                                                       \
        CRender::GetInstance()->DbgVerifyRenderState();   \
    }                                                       \
    else                                                    \
    {                                                       \
        THOT_TRACE_LINE("WARNING!!!! RENDER IS NULL.");           \
    }                                                       \
}while(false)
#else
#define RENDER_VERIFY
#endif /*_DEBUG*/


struct SRenderGLScopeVerifier
{
    SRenderGLScopeVerifier()
    {
        RENDER_VERIFY;
    }

    ~SRenderGLScopeVerifier()
    {
        RENDER_VERIFY;
    }
};


#ifdef _DEBUG
//[TODO] remove RENDER_GUARD from all function and overload gl function and guard them
#define RENDER_GUARD_BLOCK SRenderGLScopeVerifier _renderGLScopeVerifierObject;
//#define RENDER_GUARD_BLOCK
#else
#define RENDER_GUARD_BLOCK
#endif 

namespace Render
{
RENDER_API  Bool        Init();
RENDER_API  Bool        Shutdown();
}



#endif /*__RENDER_H__*/




