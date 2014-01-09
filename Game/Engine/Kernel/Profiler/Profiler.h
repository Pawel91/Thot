#if !defined(__KERNEL_PROFILER_H__)
#define __KERNEL_PROFILER_H__


#include "Kernel/Config.h"

// this file if compiled only it THOT_ENABLE_PROFILER is defined
#if defined( THOT_ENABLE_PROFILER)


#include "Kernel/DebugSystem/DebugSystem.h"
#include "Kernel/DataStructures/CString.h"
#include "Kernel/Time/Timer.h"
#include "Kernel/Singleton.h"
#include "Kernel/DataStructures/Array/Vector.h"
#include "Kernel/DataStructures/Array/Array.h"
#include "Kernel/Utils/StringUtils.h"


class CTimer;

namespace ThotProfiler
{

   
    struct KERNEL_API SPlaceInfo
    {
        SPlaceInfo(){}
        SPlaceInfo(const char* file, const char* functionName, u64 line, const char* description );

        char        m_file[1024];
        char        m_function[1024];
        char        m_description[1024];
        u64         m_line;

        const SPlaceInfo& operator= ( const SPlaceInfo& other);
    };

    class KERNEL_API CPlaceID
    {
        friend class CManager;
    public:
        CPlaceID( const SPlaceInfo& placeInfo );

    public:
        u64                     GetID();
        const SPlaceInfo&       GetInfo();

    private:
        Bool    RequestID();

    private:
        u64         m_id;
        SPlaceInfo  m_info;
    };

    class KERNEL_API CScopedProfiler
    {
        friend class CManager;
    public:
        CScopedProfiler( CPlaceID& placeID );

        CScopedProfiler( CPlaceID& placeID, const char* description );
        ~CScopedProfiler();

    private:
        CTimer      m_privateTimer;
        CPlaceID*   m_placeID;
        char        m_description[1024];

    };

    class KERNEL_API CProfilePlaceData
    {
        friend class CManager;
    public:
        CProfilePlaceData();

    private:
        static const u64                                    ms_profiledCount = 1024;
        u64                                                 m_hitCount;
        CTimer::TimeUnits                                   m_maxProfiledTime;
        CTimer::TimeUnits                                   m_lastProfiledTime;
        CTimer::TimeUnits                                   m_avarageProfileTime;
        CString                                             m_profiledTimeDescription[ms_profiledCount];
        CTimer::TimeUnits                                   m_profiledTimeArray[ms_profiledCount];
    };
    
    THOT_DECLARE_TEMPLATE_API( KERNEL_TEMPLATE_API, thVector< CPlaceID*>  );
    THOT_DECLARE_TEMPLATE_API( KERNEL_TEMPLATE_API, thVector<CProfilePlaceData>  );

    class KERNEL_API  CManager
    {
        THOT_DECLARE_SINGLETON_LAZY(CManager);
    private:
        CManager();
    
    public:
        ~CManager();

        void    BeginProfiling( u64 frameCount );
        void    EndProfiling();
        
        void    OnBeginFrame();
        void    OnEndFrame();
        void    Dump();

        void    CollectProfiledData( CScopedProfiler& scopedProfiler );

        void    OnRequestID ( CPlaceID& placeID );
        



    private:
        void    DumpProfileData( CProfilePlaceData& profileData, CPlaceID* placeID, CString& outDump );
        void    Reset();
        void    Init();

        thVector< CPlaceID*>         m_placeIDs;
        thVector<CProfilePlaceData>  m_profileData;
        u64                         m_framesProfiled;
        u64                         m_framesToProfile;
        Bool                        m_isProfiling;
    };

}


//inline functions
namespace ThotProfiler
{

    THOT_FORCE_INLINE const SPlaceInfo& SPlaceInfo::operator= ( const SPlaceInfo& other)
    {
        strcpy( m_file        ,other.m_file );
        strcpy( m_function    ,other.m_function);
        strcpy( m_description ,other.m_description );
        m_line          = other.m_line;

        return *this;
    }

    THOT_FORCE_INLINE CPlaceID::CPlaceID( const SPlaceInfo& placeInfo )
    {
        m_info = placeInfo;
        CManager::GetInstance()->OnRequestID( *this );
    }

    THOT_FORCE_INLINE SPlaceInfo::SPlaceInfo(const char* file, const char* functionName, u64 line, const char* description )
    {
        strcpy( m_file          ,file );
        strcpy( m_function      ,functionName);
        strcpy( m_description   ,description );
        m_line = line;
    }

    THOT_FORCE_INLINE CScopedProfiler::CScopedProfiler( CPlaceID& placeID, const char* description )
    {
        strcpy(m_description, description);
        m_placeID = &placeID;
        m_privateTimer.Start();
    }

    THOT_FORCE_INLINE CScopedProfiler::CScopedProfiler( CPlaceID& placeID)
    {
        Memory::Set(m_description, THOT_ARRAY_SIZE(m_description), 0);
        m_placeID = &placeID;
        m_privateTimer.Start();
    }

    THOT_FORCE_INLINE CScopedProfiler::~CScopedProfiler()
    {
        m_privateTimer.Stop();
        CManager::GetInstance()->CollectProfiledData( *this );
    }

    THOT_FORCE_INLINE CProfilePlaceData::CProfilePlaceData()
    : m_hitCount                ( 0 )
    , m_maxProfiledTime         ( 0 )
    , m_lastProfiledTime        ( 0 )
    , m_avarageProfileTime      ( 0 )
    {
        Memory::Set( m_profiledTimeArray, THOT_ARRAY_SIZE( m_profiledTimeArray), 0 );
    }

    THOT_FORCE_INLINE u64 CPlaceID::GetID()
    {
        return m_id;
    }

}// namespace ThotProfiler


#define DECLARE_PROFILE_SCOPED(__description )\
static    ThotProfiler::CPlaceID  __placeID  ( ThotProfiler::SPlaceInfo( __FILE__, __FUNCSIG__, __LINE__, __description) );   \
ThotProfiler::CScopedProfiler __scopedProfiler ( __placeID )

#define DECLARE_PROFILE_SCOPED_HIT_INFO(__description, ...)\
static    ThotProfiler::CPlaceID  __placeID  ( ThotProfiler::SPlaceInfo( __FILE__, __FUNCSIG__, __LINE__, __description) );   \
ThotProfiler::CScopedProfiler __scopedProfiler ( __placeID, StringUtils::FormatString_cstr( __VA_ARGS__ ) )

#else 

#define DECLARE_PROFILE_SCOPED(__description)

#endif //THOT_ENABLE_PROFILER


#endif //__KERNEL_PROFILER_H__