#include "Compiler.h"
#include "Kernel\Utils\StringUtils.h"
#include "stdlib.h"
#include "windows.h"

#undef DeleteFile
#undef CreateProcess
#undef CreateFile

//-------------------------------------------------------------------------------------------------

CString         CCompiler::ms_compilerLogFile       = "compile.log";
CString         CCompiler::ms_vsEnvToolsVar         = "VS110COMNTOOLS";
CString         CCompiler::ms_vsSetupBat            = "vsvars32.bat";

//CString         CCompiler::ms_solutionAbsolutePath  = "C:\\Users\\Radu\\Documents\\Visual Studio 2012\\Projects\\CompilerDummy\\";
//CString         CCompiler::ms_slnCppFileName        = "C:\\Users\\Radu\\Documents\\Visual Studio 2012\\Projects\\CompilerDummy\\CompilerDummy\\CompilerDummy.cpp";
//CString         CCompiler::ms_slnFileName           = "CompilerDummy.sln";

CString         CCompiler::ms_errorsLogFile         = "errors.log";

const char* traceFile = "c:\\cltrace.log";

#define CL_FULL_TRACE_ERROR

#if !defined(CL_FULL_TRACE_ERROR)
#define CL_ERROR( __format, ... )       \
do                                                                              \
{                                                                               \
    CString formatedError = StringUtils::FormatString( __format, __VA_ARGS__ ); \
    AddErrorString( formatedError);                                             \
}while(false)
#else

#define CL_ERROR_FULL(__file,__line,__format,...)                                                   \
do                                                                                                  \
{                                                                                                   \
    CString file = __file;                                                                          \
    unsigned long line = __line;                                                                    \
    CString format = "file[%s];line[%d]:";                                                           \
    format += __format;                                                                             \
    CString formatedError = StringUtils::FormatString( format,file.GetBuffer(), line, __VA_ARGS__ );\
    AddErrorString(formatedError);\
}while(false)

#define CL_ERROR( __format, ... ) CL_ERROR_FULL( __FILE__,__LINE__, __format, __VA_ARGS__ )

#endif

//-------------------------------------------------------------------------------------------------

CString CCompiler::GetSolutionPath( )
{
    return m_helperSolutionPath;
}

CString CCompiler::GetSolutionFile( )
{
    return m_helperSolutionPath + "CompilerDummy.sln";
}

CString CCompiler::GetSolutionCppFile( )
{
    return m_helperSolutionPath + "CompilerDummy\\CompilerDummy.cpp";
}

CString CCompiler::GetSolutionCppFileRaw( )
{
    return "CompilerDummy.cpp";
}

//--------------------------------------------------------------------------------------------------

CCompiler::CCompiler()
    :m_compileStatus    ( ECompilerStatus_InternalFail )
{
    CL_TRACE("Enter Compiler Constructor");
    CPath::SetCurrPath(m_workingDir);
}

//--------------------------------------------------------------------------------------------------

CCompiler::~CCompiler()
{
    //CPath::DeleteFile( m_compilerOutputFile );
}


//--------------------------------------------------------------------------------------------------

Bool CCompiler::OnInit( const char* sourceCode, const char* programInput, const char* helperSolutionPath )
{
    CL_TRACE("Initializing Compiler with");
    if( !sourceCode )
    {
        CL_ERROR("Failed to init Compiler! Source code is NULL");
        return false;
    }

    m_programInput = programInput;
    m_sourceCodeToCompile = sourceCode;

    if( !helperSolutionPath )
    {
        CL_ERROR(" helper solution path not found");
        return false;
    }


    // set helper solution path and validate it;
    m_helperSolutionPath = helperSolutionPath;
    if( !CPath::IsAbsolute(m_helperSolutionPath) )
    {
        CL_ERROR("solution path provided is not absolute:[%s]", m_helperSolutionPath.GetBuffer() );
        return false;
    }
    if( !CPath::DirectoryExists(m_helperSolutionPath) )
    {
        CL_ERROR( "solution directoy does not exists:[%s]", m_helperSolutionPath.GetBuffer() );
        return false;
    }

    if( !CPath::GetCurrPath( m_workingDir ) )
    {
        CL_ERROR("initialization step failed. Cannot get current directory");
        return false;
    }

    CPath::SetCurrPath( m_helperSolutionPath );

    if( !CPath::GetAbsolutePath(ms_compilerLogFile, m_compilerOutputFile) )
    {
        CL_ERROR( "failed to get absolute path from path:[%s]", ms_compilerLogFile );
        return false;
    }

    // get path to devenv and validate it;
    CString vsToolsPath;
    ThGetEnvVariable( ms_vsEnvToolsVar, vsToolsPath );
    vsToolsPath += "..\\IDE\\";
    if( !CPath::GetAbsolutePath(vsToolsPath, m_devenvPath ) )
    {
        CL_ERROR( " failed to get devenv absolute path from tools path:[%s]", vsToolsPath.GetBuffer() );
        return false;
    }
    CString devenvExecutableFullPath = m_devenvPath + "devenv.exe";
    if( !CPath::FileExists( devenvExecutableFullPath ) )
    {
        CL_ERROR( "failed to get path to devenv.exe. We got [%s] but this file does not exists!", devenvExecutableFullPath.GetBuffer() );
        return false;
    }

    CL_TRACE("Compile initialization succeeded");
    return true;
}

//--------------------------------------------------------------------------------------------------

Bool CCompiler::RunCommand ( const CString& command )
{
    const char* ptr = command.GetBuffer();
    CL_TRACE("Running command:[%s]", ptr );

    int rezult = system(command.GetBuffer());

    CL_TRACE("command [%s] has finished with result:[%d]", command.GetBuffer(), rezult );

    if( rezult != 0 )
    {
        return false;
    }

    return true;
}

//--------------------------------------------------------------------------------------------------

Bool CCompiler::RunPreCompileStep( )
{
    CL_TRACE("Enter CCompiler::RunPreCompileStep");

    //if( !CopyCppFile() )
    //{
    //    CL_ERROR("failed to copy cpp files");
    //    return false;
    //}
    if( !CopySourceCode( m_sourceCodeToCompile ) )
    {
        CL_ERROR("failed to copy source");
        return false;
    }

    // delete output file to have a clean compile log
    CPath::DeleteFile( m_compilerOutputFile );  

    CString pathToSettupBat;
    if( !ThGetEnvVariable(ms_vsEnvToolsVar, pathToSettupBat) )
    {
        CL_ERROR("failed to get path to settup bat from env variable:[%s]", ms_vsEnvToolsVar );
        return false;
    }

    CString vsSettupCommand =  "call \"" + pathToSettupBat + ms_vsSetupBat + "\"";

    if( !RunCommand(vsSettupCommand) )
    {
        return false;        
    }

    return true;
}

//--------------------------------------------------------------------------------------------------

Bool CCompiler::RunCompileStep ( )
{
    CL_TRACE("Enter CCompiler::RunCompileStep");

    // remove the old .exe if exists;
    CPath::DeleteFile( GetCompiledExeFilePath() );


    // run bat file to setup visual studio env settings;
    CString outputFileCommandLineParameter = (m_compilerOutputFile.GetLenght()==0)? "" : (" /Out " + StringUtils::Quote(m_compilerOutputFile) );
    CString command = CString("devenv.exe ") + StringUtils::Quote( GetSolutionFile() ) + " /Rebuild \"Release|Win32\"" + outputFileCommandLineParameter;

    Bool rez = true;
    CString currDir;
    CPath::GetCurrPath(currDir);
    CPath::SetCurrPath( GetDevenvPath() );
    if( !RunCommand(command) )
    {
        CPath::SetCurrPath( currDir );
        return false;
    }
    rez &= CPath::SetCurrPath( currDir );

    return true;
}

//--------------------------------------------------------------------------------------------------


// main function to compile a file
Bool CCompiler::Compile ( )
{
    CL_TRACE("Begining compiling...");

    if( !RunPreCompileStep() )
    {
        CL_ERROR( "failed to run precompile step\n" );
        SetStatus( ECompilerStatus_InternalFail );
        return false;
    }

    if( !RunCompileStep( ) )
    {
        CL_TRACE("Compilation failed..Trying to retrive the errors");
        if( OnCompileFail() )
        {
            SetStatus( ECompilerStatus_CompileFailed );
            return true;
        }
        else
        {
            SetStatus( ECompilerStatus_InternalFail );
            return false;
        }
    }
    else
    {
        CL_TRACE("Compilation succeded...Trying go get the rezult of the program");
        if( OnCompileSucceeded() )
        {
            SetStatus( ECompilerStatus_CompileSucceeded );
            return true;
        }
        else
        {
            SetStatus( ECompilerStatus_InternalFail );
            return false;
        }
    }

    return true; // Compile step succeeded;
}

//--------------------------------------------------------------------------------------------------

Bool CCompiler::CopyCppFile( )
{
    //CL_TRACE( "Enter CCompiler::CopyCppFile" );
    //CString targetFilePath = GetSolutionCppFile();

    //CL_TRACE( "Running copy files: source[%s] to target[%s]", m_sourceFileName.GetBuffer(), targetFilePath.GetBuffer() );
    //if( !FileSystem::CopyFileContent( m_sourceFileName, targetFilePath ) )
    //{
    //    CL_ERROR("CCompiler::CopyCppFile failed to copy cpp files");
    //    return false;
    //}

    //CL_TRACE( "Finished CCompiler::CopyCppFile" );
    //return true;
    THOT_ASSERT(false, "deprecated");
    return false;
}

//--------------------------------------------------------------------------------------------------

Bool CCompiler::CopySourceCode( const CString& sourceCode )
{
    if( sourceCode.GetLenght() == 0 )
    {
        CL_ERROR("source code is empty");
        return false;
    }

    FileSystem::FileHandle targetFile = FileSystem::CreateFile( EFileType::E_FILE_TYPE_MEMORY );
    
    CString targetFilePath = GetSolutionCppFile();
    if( !CPath::FileExists(targetFilePath) )
    {
        CL_ERROR( "target file:[%s] does not exists", targetFilePath.GetBuffer() );
        return false;
    }

    if( !targetFile->Open( targetFilePath, EAccesMode::E_ACCES_MODE_WRITE ) )
    {
        CL_ERROR( "failed to open target file:[%s]", targetFilePath.GetBuffer() );
        return false;
    }

    if( !targetFile->Write( sourceCode.GetBuffer(), sourceCode.GetLenght(), 1 ) )
    {
        CL_ERROR("failed to write to target file:[%s]", targetFilePath.GetBuffer() );
        return false;
    }

    return true;
}

//--------------------------------------------------------------------------------------------------

Bool CCompiler::RunPostCompileStep          ( )
{

    return true;
}

//--------------------------------------------------------------------------------------------------

Bool CCompiler::OnCompileFail( )
{
    CL_TRACE("Enter CCompiler::OnCompileFail");

    FileSystem::FileHandle compileLogFile = FileSystem::CreateFile(EFileType::E_FILE_TYPE_MEMORY);
    
    if( !compileLogFile->Open( m_compilerOutputFile, EAccesMode::E_ACCES_MODE_READ ) )
    {
        CL_ERROR( "failed to open file:[%s]", m_compilerOutputFile.GetBuffer() );
        return false;
    }

    u64 fileSize = compileLogFile->GetSize();
    CString fileContent;
    fileContent.Resize(fileSize);

    if( !compileLogFile->Read( fileContent.GetBuffer(), fileSize, 1 ) )
    {
        CL_ERROR( "failed to read file content for:[%s]" ,m_compilerOutputFile.GetBuffer() );
        return false;
    }

#define COMPILER_USE_FULL_DEVENV_OUTPUT

#if !defined(COMPILER_USE_FULL_DEVENV_OUTPUT)
    //replace CompilerDummy.cpp with our file
    CString slnCppFileName = GetSolutionCppFileRaw();
    CString sourceFileName = "CodSursa.cpp";

    CRegex regexReplace( slnCppFileName );
    fileContent = regexReplace.Replace( fileContent, sourceFileName);

    CL_TRACE("fileContent:\n[%s]\n=======================", fileContent.GetBuffer());
    //CL_ERROR("fileContent:\n[%s]\n=======================", fileContent.GetBuffer());

    const CString regexString = sourceFileName + "\\([0-9]+\\):.*error C[0-9]+:[^\n]*";
    CRegex errorRegex( regexString, true );
    CRegex::TCaptures errors;

    if( !errorRegex.Find( fileContent, errors ) )
    {
        CL_ERROR( "failed to find errors in file:[%s]",m_compilerOutputFile.GetBuffer() );
        return false;
    }

    for( u64 i=0; i<errors.GetSize(); i++ )
    {
        const CString& error = errors[i];
        m_compileErrors += error;
    }
#else
    m_compileErrors = fileContent;
#endif //COMPILER_USE_FULL_DEVENV_OUTPUT

    return true;    // The OnCompileFailed step succeeded;
}

//--------------------------------------------------------------------------------------------------

void CCompiler::AddErrorString( const CString& error )
{
    m_lastError += "\n" + error;
}

//--------------------------------------------------------------------------------------------------

CString CCompiler::GetLastErrors( )const
{
    CString toRet = m_lastError;
    m_lastError = "";
    return toRet;
}

//--------------------------------------------------------------------------------------------------

const CString& CCompiler::GetCompileErrors( )const
{
    return m_compileErrors;
}

//--------------------------------------------------------------------------------------------------

const CString& CCompiler::GetDevenvPath( )
{
    return m_devenvPath;
}

//--------------------------------------------------------------------------------------------------

void CCompiler::Trace( const CString& string)
{
    FILE* pFile = fopen( traceFile, "a" );
    if(pFile)
    {
        fprintf( pFile, "%s", string.GetBuffer() );
        fprintf(pFile,"\n");
        fclose(pFile);
    }  
}

//--------------------------------------------------------------------------------------------------

CString CCompiler::GetCompiledExeFilePath()
{
    return GetSolutionPath() +"bin\\CompilerDummy.exe";
}

//--------------------------------------------------------------------------------------------------

CString CCompiler::GetExePath( )
{
    return GetSolutionPath() + "bin\\";
}

//--------------------------------------------------------------------------------------------------

Bool CCompiler::OnCompileSucceeded( )
{
    CString exePath = GetCompiledExeFilePath();
    if( !CPath::FileExists(exePath) )
    {
        CL_ERROR( "Compiled succeeded but the file:[%s] was not found", exePath.GetBuffer() );
        return false;
    }
    
    CString inputFileName = GetExePath() + "input.in";
    CString outputFileName = GetExePath() + "output.out";

    CPath::DeleteFile( inputFileName );
    CPath::DeleteFile( outputFileName );

    // write the program input to the file
    FileSystem::FileHandle inputFileHandle = FileSystem::CreateFile( EFileType::E_FILE_TYPE_MEMORY );
    if(!inputFileHandle->Open( inputFileName, EAccesMode::E_ACCES_MODE_WRITE ) )
    {
        CL_ERROR("failed to set the program input");
        return false;
    }

    if( !inputFileHandle->Write( m_programInput, m_programInput.GetLenght(), 1 ) )
    {
        CL_ERROR("failed to set the program input");
        return false;
    }

    // close the input file so that the new program can read from it;
    inputFileHandle->Close();

#if !defined (CL_USE_PROCESS)

    CString command = "call " +  StringUtils::Quote(exePath) + " < " + StringUtils::Quote( inputFileName ) + " > " + StringUtils::Quote( outputFileName );

    RunCommand( command );

    Sleep( 3000 );//sleep 3 second so we can let the process to do the job;
    FileSystem::FileHandle outputFileHandle = FileSystem::CreateFile( EFileType::E_FILE_TYPE_MEMORY );

    if( !outputFileHandle->Open( outputFileName, EAccesMode::E_ACCES_MODE_READ ) )
    {
        CL_ERROR("failed to get the output of the your program" );
        return false;
    }

    u64 fileSize = outputFileHandle->GetSize();
    if(fileSize == 0)
    {
        CL_ERROR("failed to get the output of your program");
        return false;
    }
    
    CString outputFileContent;
    outputFileContent.Resize( fileSize + 1 );

    if( !outputFileHandle->Read( outputFileContent.GetBuffer(), fileSize, 1 ) )
    {
        CL_ERROR( "failed to get the output of your program" );
        return false;
    }

    m_programOutput = outputFileContent;

#elif defined( CL_USE_PROCESS )
    SECURITY_ATTRIBUTES sa;
    ThZeroMemoryTmpl(sa);
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE; 



    HANDLE inputFileHandle = CreateFileA(   inputFile.GetBuffer(),
                                            FILE_APPEND_DATA,
                                            FILE_SHARE_WRITE | FILE_SHARE_READ,
                                            &sa,
                                            OPEN_ALWAYS,
                                            FILE_ATTRIBUTE_NORMAL,
                                            NULL
                                        );

    if( inputFileHandle == INVALID_HANDLE_VALUE )
    {
        CL_ERROR("failed to redirect child process stdin ");
        CL_ERROR("WIN last error = %d", GetLastError());
        return false;
    }

    HANDLE outputFileHandle = CreateFileA(outputFile.GetBuffer(),
                                            GENERIC_READ | GENERIC_WRITE,
                                            FILE_SHARE_WRITE | FILE_SHARE_READ,
                                            &sa,
                                            CREATE_ALWAYS,
                                            FILE_ATTRIBUTE_NORMAL,
                                            NULL
                                        );

    if( outputFileHandle == INVALID_HANDLE_VALUE )
    {
        CL_ERROR("failed to redirect child process stout ");
        CL_ERROR("WIN last error = %d", GetLastError());
        return false;
    }


    SetHandleInformation(inputFileHandle, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);

    // setup startup info
    STARTUPINFO processStartupInfo;
    ThZeroMemoryTmpl(processStartupInfo);
    processStartupInfo.cb = sizeof(processStartupInfo);
    processStartupInfo.dwFlags |= STARTF_USESTDHANDLES;
    processStartupInfo.hStdInput = inputFileHandle;
    processStartupInfo.hStdOutput = outputFileHandle;


    PROCESS_INFORMATION processInfo;

    if( !CreateProcessA( exePath.GetBuffer() // application name  
                        ,exePath.GetBuffer()
                        ,NULL
                        ,NULL
                        ,TRUE
                        ,0
                        ,NULL
                        ,NULL
                        ,&processStartupInfo
                        ,&processInfo) 
        )
    {
        CL_ERROR("Cannot start process:[%s]", exePath.GetBuffer());
        return false;
    }

    WaitForSingleObject(processInfo.hProcess, 3000 );
    CloseHandle( processInfo.hThread );
    CloseHandle( processInfo.hProcess );
#endif
    return true;
}

//--------------------------------------------------------------------------------------------------

const CString&  CCompiler::GetProgramOutput( )const
{
    return m_programOutput;
}