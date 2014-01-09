// ToolFramework_TextureExporter.cpp : Defines the entry point for the console application.
//

#include "Render/Textures/Texture.h"
#include "Kernel/FileSystem/FileSystem.h"
#include "SOIL.h"
#include "SoilBase.h"
#include "Kernel\ThotWindows.h"

HGLRC g_handleRenderContext;
HDC g_handleDeviceContext;
void Init( HINSTANCE hInstance);
void Shutdown();
void ConvertSoilToNativeTextureHeader( const Soil_TextureHeader& soilHeader, SGLTextureHeader& nativeHeader );

HWND CreateNewWindow( HINSTANCE hInstance );
LRESULT CALLBACK  MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void SetupPixelFormat(HDC hDC);


bool Verify( const Soil_TextureHeader* soilHeader, const SGLTextureHeader* header );

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    Init( hInstance);

    //CString source = "e:\\Programming\\Workspace GameDev\\Workspace Licenta\\Game\\Data\\textures\\caramide.png";
    //CString targetPath = "e:\\Programming\\Workspace GameDev\\Workspace Licenta\\Game\\Data\\textures\\caramide.tres";
    CString source = "e:\\Programming\\Workspace GameDev\\Workspace Licenta\\Game\\Data\\textures\\spec.jpg";
    CString targetPath = "e:\\Programming\\Workspace GameDev\\Workspace Licenta\\Game\\Data\\textures\\spec.tres";
    //verde.jpg

    // make texture compression and generate mipmaps
    u32 soilFlags = SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MIPMAPS;

    Soil_TextureHeader soilHeader;
    
    SOIL_load_OGL_texture( source, 0, 0, soilFlags, &soilHeader);

    u32 totalMipSize = 0;
    for( u32 i = 0; i <= (u32)soilHeader.m_levels; i++ )
    {
        totalMipSize += ThNumericCast<u32>( soilHeader.m_mipSizes[i] );
    }

    void* nativeBuffer = THOT_MALLOC(totalMipSize + sizeof(SGLTextureHeader) );
    SGLTextureHeader* nativeTextureHeader = (SGLTextureHeader*)nativeBuffer;
    ThZeroMemoryTmpl( *nativeTextureHeader);
    nativeTextureHeader->m_magicNumber = SGLTextureHeader::MAGIC_NUMBER;
    nativeTextureHeader->m_totalSize = totalMipSize; 
    ConvertSoilToNativeTextureHeader( soilHeader, *nativeTextureHeader);

    nativeBuffer = (char*)nativeBuffer + sizeof(SGLTextureHeader);

    // copy every mip level from soil header to one big native buffer
    
    // first we copy mip level 0
    memcpy(nativeBuffer, (void*)(soilHeader.m_mipOffsets[0]), soilHeader.m_mipSizes[0]);
    nativeTextureHeader->m_mipOffsets[0] = sizeof(SGLTextureHeader);

    // scopped block
    {
        u32 currentOffset = ThNumericCast<u32>( soilHeader.m_mipSizes[0] );
        for( u32 i=1; i <= ThNumericCast<u32>(soilHeader.m_levels); i++)
        {
            nativeTextureHeader->m_mipOffsets[i] = currentOffset + sizeof(SGLTextureHeader);
           
            memcpy( ((char*)nativeBuffer) + currentOffset, (void*)(soilHeader.m_mipOffsets[i]), soilHeader.m_mipSizes[i]);

            currentOffset += ThNumericCast<u32>( soilHeader.m_mipSizes[i] );
            
        }
    }

    if( !Verify( &soilHeader, nativeTextureHeader) )
    {
        return -1;
    }

    // write the buffer to file
    FileSystem::FileHandle targetFile = FileSystem::CreateFile( EFileType::E_FILE_TYPE_NORMAL);
    if( !targetFile->Open( targetPath, EAccesMode::E_ACCES_MODE_WRITE ) )
    {
        return -1;
    }

    if( !targetFile->Write( nativeTextureHeader, totalMipSize + sizeof(SGLTextureHeader), 1 ) )
    {
        return -1;
    }


    THOT_FREE(nativeTextureHeader);
    Shutdown();

	return 0;
}

bool Verify( const Soil_TextureHeader* soilHeader, const SGLTextureHeader* header )
{
    if( header->m_levels != soilHeader->m_levels )
    {
        return false;
    }

    for( u32 mipLevel = 0; mipLevel <= header->m_levels; mipLevel ++ )
    {
        void* mipLevelData = (char*)header + header->m_mipOffsets[ mipLevel ];

        if( header->m_mipSizes[mipLevel] != soilHeader->m_mipSizes[mipLevel] )
        {
            return false;
        }

        if( memcmp( mipLevelData, soilHeader->m_mipOffsets[mipLevel], header->m_mipSizes[mipLevel] ) !=0 )
        {
            return false;
        }

     }

    return true;
}

void ConvertSoilToNativeTextureHeader( const Soil_TextureHeader& soilHeader, SGLTextureHeader& nativeHeader )
{
    nativeHeader.m_target           = soilHeader.m_target      ;
    nativeHeader.m_levels           = soilHeader.m_levels      ;
    nativeHeader.m_internalFormat   = soilHeader.m_internalFormat;
    nativeHeader.m_width            = soilHeader.m_width       ;
    nativeHeader.m_height           = soilHeader.m_height      ;
    nativeHeader.m_depth            = soilHeader.m_depth       ;
    nativeHeader.m_format           = soilHeader.m_format      ;
    nativeHeader.m_pixelType        = soilHeader.m_pixelType   ;
    nativeHeader.m_isCompressed     = soilHeader.m_isCompressed;
    //u32     m_mipOffsets[MAX_MIP_MAP_COUNT];    //offsets to the mip data; miplevel "i" data is found between m_mipOffsets[i] and m_mipOffsets[i+1];
    //u32     m_mipSizes[MAX_MIP_MAP_COUNT];      // size of each mip

    for( u32 mipLevel = 0 ; mipLevel <= ThNumericCast<u32>(soilHeader.m_levels); mipLevel++)
    {
        nativeHeader.m_mipSizes[mipLevel] = ThNumericCast<u32>( soilHeader.m_mipSizes[mipLevel] );
    }
}

void Init( HINSTANCE hInstance)
{
    HWND handleWindow = CreateNewWindow( hInstance );
    //g_handleDeviceContext = GetDC(handleWindow);
    //g_handleRenderContext = wglCreateContext (g_handleDeviceContext );
    //wglMakeCurrent( g_handleDeviceContext, g_handleRenderContext);
}

void Shutdown()
{
    wglMakeCurrent( g_handleDeviceContext, NULL);
    wglDeleteContext( g_handleRenderContext );
}
void SetupPixelFormat(HDC hDC)
{
    int pixelFormat;
    
    //[TODO] get pixel format descriptor from a setting from render or something like that:D:D
    PIXELFORMATDESCRIPTOR pfd =
    {   
        sizeof(PIXELFORMATDESCRIPTOR),  // size
            1,                          // version
            PFD_SUPPORT_OPENGL |        // OpenGL window
            PFD_DRAW_TO_WINDOW |        // render to window
            PFD_DOUBLEBUFFER,           // support double-buffering
            PFD_TYPE_RGBA,              // color type
            32,                         // prefered color depth
            0, 0, 0, 0, 0, 0,           // color bits (ignored)
            0,                          // no alpha buffer
            0,                          // alpha bits (ignored)
            64,                         // accumulation buffer
            0, 0, 0, 0,                 // accum bits (ignored)
            24,                         // depth buffer
            8,                          // stencil buffer
            0,                          // no auxiliary buffers
            PFD_MAIN_PLANE,             // main layer
            0,                          // reserved
            0, 0, 0,                    // no layer, visible, damage masks
    };

    pixelFormat = ChoosePixelFormat(hDC, &pfd);
    THOT_ASSERT( pfd.cStencilBits==8 && pfd.cColorBits == 32 && pfd.cDepthBits == 24); // verify color, depth and stencil buffer
    SetPixelFormat(hDC, pixelFormat, &pfd);
}

LRESULT CALLBACK  MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    // dispatch messages
    switch (uMsg)
    {   
    case WM_CREATE:         // window creation
        g_handleDeviceContext = GetDC(hWnd);
        SetupPixelFormat(g_handleDeviceContext);
        g_handleRenderContext = wglCreateContext(g_handleDeviceContext);
        wglMakeCurrent(g_handleDeviceContext, g_handleRenderContext);

        break;

    case WM_DESTROY:            // window destroy
    case WM_QUIT:
    case WM_CLOSE:                  // windows is closing

        // deselect rendering context and delete it
        wglMakeCurrent( g_handleDeviceContext, NULL);
        wglDeleteContext( g_handleRenderContext );

        // send WM_QUIT to message queue
        PostQuitMessage(0);
        break;
    }
 
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

HWND CreateNewWindow( HINSTANCE hInstance )
{
    WNDCLASSEX windowClass;     // window class
    HWND       hwnd;            // window handle
    DWORD      dwExStyle;       // Window Extended Style
    DWORD      dwStyle;         // Window Style
    RECT       windowRect;

    windowRect.left     = (long)0;                        // Set Left Value To 0
    windowRect.right    = (long) 100; // Set Right Value To Requested Width
    windowRect.top      = (long)0;                         // Set Top Value To 0
    windowRect.bottom   = (long) 100;   // Set Bottom Value To Requested Height

    // fill out the window class structure
    windowClass.cbSize          = sizeof(WNDCLASSEX);
    windowClass.style           = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc     = MainWindowProc;
    windowClass.cbClsExtra      = 0;
    windowClass.cbWndExtra      = 0;
    windowClass.hInstance       = hInstance;
    windowClass.hIcon           = LoadIcon(NULL, IDI_APPLICATION);  // default icon
    windowClass.hCursor         = LoadCursor(NULL, IDC_ARROW);      // default arrow
    windowClass.hbrBackground   = NULL;                             // don't need background
    windowClass.lpszMenuName    = NULL;                             // no menu
    windowClass.lpszClassName   = "GLClass";
    windowClass.hIconSm         = LoadIcon(NULL, IDI_WINLOGO);      // windows logo small icon

    // register the windows class
    if (!RegisterClassEx(&windowClass))
    {
        return NULL;
    }

    if ( /*Game::GetGameParams().m_bFullscreen*/0 )      // fullscreen?
    {
        DEVMODE dmScreenSettings; memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize         = sizeof(dmScreenSettings); 
        dmScreenSettings.dmPelsWidth    = 12 ;         // screen width
        dmScreenSettings.dmPelsHeight   = 12;           // screen height
        dmScreenSettings.dmBitsPerPel   = 8;             // bits per pixel
        dmScreenSettings.dmFields       = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        // 
        if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            // setting display mode failed, switch to windowed
            MessageBoxA(NULL, "Display mode failed", NULL, MB_OK);
            
        }
    }

    if ( /*Game::GetGameParams().m_bFullscreen*/ 0 )  // Are We Still In Fullscreen Mode?
    {
        dwExStyle=WS_EX_APPWINDOW;              // Window Extended Style
        dwStyle=WS_POPUP;                       // Windows Style
        ShowCursor(false);                      // Hide Mouse Pointer
    }
    else
    {
        //dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // Window Extended Style
        //dwStyle = WS_OVERLAPPEDWINDOW;                    // Windows Style
        //ShowCursor(false);

        dwExStyle = WS_EX_APPWINDOW;            // Window Extended Style
        dwStyle = WS_POPUP;                     // Windows Style
        ShowCursor(false);                      // Hide Mouse Pointer
    }

    AdjustWindowRectEx(&windowRect, dwStyle, false, dwExStyle);     // Adjust Window To True Requested Size

    // class registered, so now create our window
    hwnd = CreateWindowEx(0,                         // extended style
        "GLClass",                                      // class name
        "SKINNING",                                 // app name
        dwStyle | WS_CLIPCHILDREN |
        WS_CLIPSIBLINGS,
        0, 0,                               // x,y coordinate
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top, // width, height
        NULL,                               // handle to parent
        NULL,                               // handle to menu
        hInstance,                          // application instance
        NULL);                              // no extra params

    // check if window creation failed (hwnd would equal NULL)
    if (!hwnd)
    {
        THOT_ASSERT(false, "Failed to create window handle" );
        return hwnd;
    }

    ShowWindow(hwnd, SW_SHOW);          // display the window
    UpdateWindow(hwnd);                 // update the window

 
    
    return hwnd;
}
