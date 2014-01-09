#pragma once
#ifndef __TEHNICI_COMPILARE_COMPILER_H__
#define __TEHNICI_COMPILARE_COMPILER_H__


extern const char* traceFile;
#define CL_TRACE(__format, ...)                                     \
do                                                                  \
{                                                                   \
    CString str = StringUtils::FormatString(__format, __VA_ARGS__); \
    CCompiler::Trace( str );                                                   \
}while(false)

enum ECompilerStatus
{
     ECompilerStatus_InternalFail
    ,ECompilerStatus_CompileSucceeded
    ,ECompilerStatus_CompileFailed
};


class CCompiler
{
public:
     CCompiler  ( );
    ~CCompiler  ( );

public:

    Bool            OnInit                      ( const char* sourceCode, const char* programInput, const char* helperSolutionPath );

    // return a string containing all errors;
    Bool            Compile                     ( );

    CString         GetLastErrors               ( )const;
    const CString&  GetCompileErrors            ( )const;
    const CString&  GetProgramOutput            ( )const;
    ECompilerStatus GetStatus                   ( )const                    { return m_compileStatus; }

static    void      Trace                       ( const CString& string);
protected:
    void            AddErrorString              ( const CString& error );

    Bool            RunPreCompileStep           ( );
    Bool            RunCompileStep              ( );
    Bool            RunPostCompileStep          ( );
    Bool            RunCommand                  ( const CString& command );
    Bool            OnCompileFail               ( );
    Bool            CopyCppFile                 ( );
    Bool            CopySourceCode              ( const CString& sourceCode );
    void            SetStatus                   ( ECompilerStatus status )  {m_compileStatus = status;}


    Bool            OnCompileSucceeded          ( );


const   CString&    GetDevenvPath               ( );
        CString     GetSolutionPath             ( );
        CString     GetSolutionFile             ( );
        CString     GetSolutionCppFile          ( );
        CString     GetSolutionCppFileRaw       ( );
        CString     GetCompiledExeFilePath      ( );
        CString     GetExePath                  ( );

private:
mutable CString         m_lastError;
        //CString         m_sourceFileName;
        CString         m_compilerOutputFile;
        CString         m_compileErrors;
        CString         m_devenvPath;

        CString         m_sourceCodeToCompile;
        CString         m_programInput;
        CString         m_programOutput;

        CString         m_workingDir;
        CString         m_helperSolutionPath;

        ECompilerStatus m_compileStatus;

static CString      ms_vsEnvToolsVar;
static CString      ms_vsSetupBat;
static CString      ms_errorsLogFile;
static CString      ms_compilerLogFile;

};












#endif /*__TEHNICI_COMPILARE_COMPILER_H__*/