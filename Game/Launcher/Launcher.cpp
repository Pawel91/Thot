
#include "windows.h"

#include "..\\Game\GameEntryPoint.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //MessageBoxA(NULL, "Game is about to launch!!", NULL, MB_OK);

   
    //TODO read command line from a config file..
    return RunGame( hInstance, lpCmdLine );
}
