#include "EntryPoint.h"
#include "Compiler.h"
#include "Kernel\Utils\StringUtils.h"

static ECompilerStatus g_lastCompileStatus = ECompilerStatus_InternalFail;

COMPILER_API char* _stdcall _Compile ( const char* sourceCode, const char* programInput, const char* helperSolutionPath )
{
    CL_TRACE("Enter Compiler");
    g_lastCompileStatus = ECompilerStatus_InternalFail;

    CCompiler compiler;
    compiler.OnInit( sourceCode, programInput, helperSolutionPath );

    CString errors;
    errors.SetInternalBufferOwnership(false);

    compiler.Compile();


    switch(compiler.GetStatus())
    {
    case ECompilerStatus_CompileFailed:
        {
            errors = compiler.GetCompileErrors();
            g_lastCompileStatus = ECompilerStatus_CompileFailed;
            break;
        }
    case ECompilerStatus_CompileSucceeded:
        {
            errors = compiler.GetProgramOutput();
            g_lastCompileStatus = ECompilerStatus_CompileSucceeded;
            break;
        }
    
    case ECompilerStatus_InternalFail:
        {
            errors = compiler.GetLastErrors();
            g_lastCompileStatus = ECompilerStatus_InternalFail;
         break;
        }

    }

    return errors;
}

COMPILER_API s32    _stdcall _GetLastCompileStatus()
{
    return g_lastCompileStatus;
}

COMPILER_API int _stdcall GetTestNumber()
{
    return 21;
}

COMPILER_API const char* _stdcall GetTestString   ( )
{
    //char* string = smalloc_type(20,char);
    //string[0] = 'T';
    //string[1] = 'H';
    //string[2] = 'O';
    //string[3] = 'T';
    //string[4] = 0;

    //return string;
    return NULL;
}
