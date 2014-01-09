#include "Kernel_PCH.h"
#include "Regex.h"

#if !defined(__KERNEL_NOT_USE_REGEX_CLASS)

#include "Kernel\DebugSystem\DebugSystem.h"
#include "Kernel\DataStructures\CString.h"
#include "boost\regex.hpp"

#define m_regex (( boost::regex*&)m_regex)

typedef boost::regex TRegexBase;

static u32 s_defaultRegexFlags = boost::regex::perl;

//------------------------------------------------------------------------------

CRegex::CRegex ( const CString& regex, Bool bIgnoreCase )
{
    m_bIgnoreCase = bIgnoreCase;
    
    //u32 flag = boost::regex::icase;
    u32 constructorFlags = (m_bIgnoreCase)?s_defaultRegexFlags|boost::regex::icase : s_defaultRegexFlags;
    
    m_regex = THOT_NEW TRegexBase(regex.GetBuffer(), constructorFlags );
}

//------------------------------------------------------------------------------

CRegex::~CRegex()
{
    THOT_ASSERT(m_regex);
    if( !m_regex )
    {
        THOT_DELETE(m_regex);
    }
}

//------------------------------------------------------------------------------

Bool CRegex::GetRegexString( CString& out )
{

    return true;
}

//------------------------------------------------------------------------------

Bool CRegex::Match( const CString& string )
{
    if(! boost::regex_match( string.GetBuffer(), *m_regex ) )
    {
        return false;
    }

    return true;
}

//------------------------------------------------------------------------------

Bool CRegex::Match( const CString& string, CRegex::TCaptures& outCaptures )
{
    outCaptures.Resize(0);

    boost::smatch nativeCaptureGroups;
    std::string nativeString( string.GetBuffer());

    if( !boost::regex_match( nativeString, nativeCaptureGroups, *m_regex ) )
    {
        return false;
    }

    THOT_TRACE_LINE("========================");
    size_t size = nativeCaptureGroups.size();
    for( size_t i = 0; i < size; ++i)
      {
         ////std::cout << "      $" << i << " = {";
         // THOT_TRACE_LINE( "      $%d = {", i );
         //for( int j = 0; j < nativeCaptureGroups.captures(i).size(); ++j )
         //{
         //   if(j)
         //   {
         //       THOT_TRACE_LINE(", ");
         //   }
         //   else
         //   {
         //       THOT_TRACE_LINE(" ");
         //   }
         //   THOT_TRACE_LINE("\"%s\"", nativeCaptureGroups.captures(i)[j] );
         //}
         //
         //THOT_TRACE_LINE( " }\n" );
          outCaptures.Add( nativeCaptureGroups.str((int)i).c_str() );
          THOT_TRACE_LINE( "%s", nativeCaptureGroups.str((int)i).c_str() );
      }


    return true;
}

//------------------------------------------------------------------------------

CString CRegex::Replace ( const CString& what, const CString& with )
{
#ifndef THOT_ENABLE_MOVE_CONSTRUCTOR
#pragma message( "CRegex::Replace NOT USING MOVE CONSTRUCTOR. PERFORMANCE HIT!");
#endif /*THOT_ENABLE_MOVE_CONSTRUCTOR*/

    std::string nativeWhat( what.GetBuffer() );
    std::string nativeWith( with.GetBuffer() );

    std::string nativeResult = boost::regex_replace( nativeWhat, *m_regex, nativeWith );

    CString out = nativeResult.c_str();
    return out;
}

//------------------------------------------------------------------------------

Bool CRegex::Find( const CString& string, TCaptures& outResult )
{
    outResult.Resize(0);
    std::string text( string.GetBuffer() );

    boost::sregex_token_iterator iter(text.begin(), text.end(), *m_regex, 0 );
    boost::sregex_token_iterator end;

    if( iter == end )
    {
        return false;
    }

    for( ; iter != end; ++iter ) 
    {
        outResult.Add( iter->str().c_str() );
    }

    return true;
}

#endif //#if !defined(__KERNEL_NOT_USE_REGEX_CLASS)