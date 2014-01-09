#pragma once
#ifndef __TEHNICI_COMPILARE_ENTRY_POINT_H__
#define __TEHNICI_COMPILARE_ENTRY_POINT_H__


THOT_BEGIN_EXTERN_C

    COMPILER_API char*   _stdcall           _Compile        ( const char* sourceCode, const char* programInput, const char* helperSolutionPath );
    COMPILER_API s32    _stdcall            _GetLastCompileStatus();
    COMPILER_API int    _stdcall            GetTestNumber   ( );
    COMPILER_API const char*  _stdcall      GetTestString   ( );

THOT_END_EXTERN_C






#endif /*__TEHNICI_COMPILARE_ENTRY_POINT_H__*/