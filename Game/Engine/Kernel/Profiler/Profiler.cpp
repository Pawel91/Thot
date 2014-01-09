#include "Kernel_PCH.h"
#include "Profiler.h"

#if defined(THOT_ENABLE_PROFILER)

#include "Kernel/Defines.h"
#include "Kernel/Utils/StringUtils.h"
#include "Kernel/FileSystem/FileSystem.h"

namespace ThotProfiler
{


    THOT_IMPLEMENT_SINGLETON_LAZY(CManager);

    void   CManager::OnRequestID( CPlaceID& placeID )
    {
        m_placeIDs.PushBack( &placeID );
        m_profileData.PushBack( CProfilePlaceData() );
        placeID.m_id = m_placeIDs.Size()-1;
    }

    CManager::~CManager()
    {

    }

    CManager::CManager()
        : m_isProfiling     (false)
        , m_framesProfiled  ( 0 )
        , m_framesToProfile ( 0 )
    {
        Init();
    }

    void    CManager::Init()
    {
    
    }

    void    CManager::CollectProfiledData( CScopedProfiler& scopedProfiler )
    {
        if( !m_isProfiling )
        {
            return;
        }

        CProfilePlaceData& profileData = m_profileData[ scopedProfiler.m_placeID->GetID() ];
        CTimer::TimeUnits currentTimer = scopedProfiler.m_privateTimer.GetTimerValue();
        profileData.m_lastProfiledTime = currentTimer;
        profileData.m_maxProfiledTime = ThMax( currentTimer, profileData.m_maxProfiledTime );
        
        profileData.m_avarageProfileTime = ( ( (profileData.m_hitCount)? (profileData.m_avarageProfileTime  * profileData.m_hitCount) : currentTimer )+ currentTimer) 
                                                            / ( profileData.m_hitCount + 1);
        
        if( profileData.m_hitCount < THOT_ARRAY_SIZE(profileData.m_profiledTimeDescription) )
        {
            profileData.m_profiledTimeDescription[profileData.m_hitCount] = scopedProfiler.m_description;
            profileData.m_profiledTimeArray[ profileData.m_hitCount ] = currentTimer;
        }

        profileData.m_hitCount ++;
    }

    void CManager::OnBeginFrame()
    {
        if( !m_isProfiling )
        {
            return;
        }


    }

    void CManager::OnEndFrame()
    {
        if( !m_isProfiling )
        {
            return;
        }

        m_framesProfiled ++;

        if( m_framesProfiled >= m_framesToProfile )
        {
            EndProfiling();
        }
    }

    void CManager::BeginProfiling( u64 frameCount )
    {
        m_isProfiling = true;
        m_framesToProfile = frameCount;
    }

    void CManager::EndProfiling()
    {
        Dump();
        m_isProfiling = false;
        m_framesToProfile = 0;
        m_framesProfiled = 0;
        Reset();

    }

    void CManager::Reset()
    {
        for( u64 i=0; i<m_profileData.Size(); i++ )
        {
            CProfilePlaceData& profileData =  m_profileData[ i ];
            profileData.~CProfilePlaceData();
            new(&profileData) CProfilePlaceData();
        }
    }

    void CManager::Dump()
    {
        CString dumpString;

        dumpString += StringUtils::FormatString("=============BEGIN PROFILER DUMP========================\n");

        for( u64 i=0; i<m_profileData.Size(); i++ )
        {
            CPlaceID* placeID =  m_placeIDs[ i ];
            CProfilePlaceData& profileData =  m_profileData[ i ];

            DumpProfileData( profileData, placeID, dumpString );
        }

        dumpString+= StringUtils::FormatString("=============END PROFILER DUMP========================");

        THOT_TRACE_LINE( "%s", dumpString.c_str() );

        FileSystem::FileHandle outputProfileFileHandle = FileSystem::CreateFile(EFileType::E_FILE_TYPE_MEMORY);
        if( !outputProfileFileHandle->Open("ProfileDump.dmp", EAccesMode::E_ACCES_MODE_WRITE ) )
        {
            THOT_ASSERT( false, "CANNOT OPEN DUMP FILE");
        }

        if( !outputProfileFileHandle->Write( dumpString ) )
        {
            THOT_ASSERT( false, "CANNOT WRITE TO FILE");
        }
    }

    void CManager::DumpProfileData( CProfilePlaceData& profileData,  CPlaceID* placeID, CString& outDump )
    {
        CProfilePlaceData& frameProfileData = m_profileData[0];
        double avgPercent = (double)profileData.m_avarageProfileTime / (double)frameProfileData.m_avarageProfileTime ;
        double lastPercent = (double)profileData.m_lastProfiledTime / (double)frameProfileData.m_lastProfiledTime;

        CString& dumpString = outDump;

        dumpString += StringUtils::FormatString("---------------------------------------------\n");
        dumpString += StringUtils::FormatString("   BEGIN PROFILE POINT:\n");

        dumpString += StringUtils::FormatString("       Begin place info:\n");
        dumpString += StringUtils::FormatString("           profileID:              [%d]\n", placeID->m_id);
        dumpString += StringUtils::FormatString("           profile file:           [%s]\n", placeID->m_info.m_file );
        dumpString += StringUtils::FormatString("           profile function:       [%s]\n", placeID->m_info.m_function );
        dumpString += StringUtils::FormatString("           profile line:           [%d]\n", placeID->m_info.m_line );
        dumpString += StringUtils::FormatString("           profile description:    [%s]\n", placeID->m_info.m_description );
        dumpString += StringUtils::FormatString("       End place info:\n");
        dumpString += StringUtils::FormatString("\n");

        dumpString += StringUtils::FormatString("       hit count:                  [%d]\n", profileData.m_hitCount);
        dumpString += StringUtils::FormatString("       last profiled time:         micro[%d], mili[%d], seconds[%d], percent[%f]\n",  
                                                                                                CTimer::GetMicroseconds( profileData.m_lastProfiledTime ),
                                                                                                CTimer::GetMiliseconds( profileData.m_lastProfiledTime ),
                                                                                                CTimer::GetSeconds( profileData.m_lastProfiledTime ),
                                                                                                lastPercent*100);
        dumpString += StringUtils::FormatString("       average time:               micro[%d], mili[%d], seconds[%d], percent[%f]\n",  
                                                                                            CTimer::GetMicroseconds(profileData.m_avarageProfileTime ),
                                                                                            CTimer::GetMiliseconds(profileData.m_avarageProfileTime ),
                                                                                            CTimer::GetSeconds(profileData.m_avarageProfileTime ),
                                                                                            avgPercent*100);

        dumpString += StringUtils::FormatString("       max time:                   micro[%d], mili[%d], seconds[%d], percent[%f]\n",  
                                                                                            CTimer::GetMicroseconds(profileData.m_maxProfiledTime ),
                                                                                            CTimer::GetMiliseconds(profileData.m_maxProfiledTime ),
                                                                                            CTimer::GetSeconds(profileData.m_maxProfiledTime ) );



        CString profileArrayTimes;
        u64 size = ThMin( THOT_ARRAY_SIZE(profileData.m_profiledTimeArray), profileData.m_hitCount );
        for( u64 i=0; i<size; i++)
        {
            CTimer::TimeUnits timeUnits = profileData.m_profiledTimeArray[i];
            u64 microseconds = CTimer::GetMicroseconds(profileData.m_profiledTimeArray[i]);
            u64 miliseconds = CTimer::GetMiliseconds(profileData.m_profiledTimeArray[i]);
            const CString& hitDescription = profileData.m_profiledTimeDescription[i];
            profileArrayTimes += StringUtils::FormatString( "                           At hit [%d]........[%d us] [%d ms]; description = [%s] \n", i, microseconds, miliseconds, hitDescription.c_str() );
        }

        THOT_TRACE_LINE("%s", profileArrayTimes.c_str() );
        dumpString += StringUtils::FormatString("       profiled times: \n%s \n", profileArrayTimes.c_str() );


        dumpString += StringUtils::FormatString("   END PROFILE POINT:\n");
        dumpString += StringUtils::FormatString("---------------------------------------------\n");
        dumpString += StringUtils::FormatString("\n");
        
        //THOT_TRACE_LINE("%s", dumpString.c_str() );
    }

}// namespace ThotProfiler

#endif //#if defined(THOT_ENABLE_PROFILER)