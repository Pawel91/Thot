#pragma once
#ifndef __RTTI_H__
#define __RTTI_H__

#include "Kernel\KernelDef.h"

//============== DECLARE and IMPLEMENT macros for InPlaceConstructor
#define    DECLARE_INPLACE_CONSTRUCTOR( _className )    \
public:                                                \
static _className*    s_InPlaceConstructor();                    

#define    IMPLEMENT_INPLACE_CONSTRUCTOR( _className )    \
_className*    _className::s_InPlaceConstructor()        \
{                                                    \
    return THOT_NEW _className;                        \
}                                                    


//============== DECLARE and IMPLEMENT macros for RTTI

#define DECLARE_RTTI_FUNCTIONS(_className, _baseName)                    \
virtual    Bool                IsA( const SReplicator& replicator );        \
static    const SReplicator&    s_GetClassReplicator( );                    \
virtual    const SReplicator&    GetInstanceReplicator( );                    


#define IMPLEMENT_RTTI_FUNCTIONS(_className, _baseName)                    \
Bool _className::IsA( const SReplicator& replicator )                    \
{                                                                        \
    SReplicator* base = &s_replicator;                                    \
    while( base != base->m_pBaseReplicator )                            \
    {                                                                    \
        if( base == &replicator )                                        \
            return true;                                                \
        base = base->m_pBaseReplicator;                                    \
    }                                                                    \
                                                                        \
    if( base == &replicator )                                            \
        return true;                                                    \
                                                                        \
    return false;                                                        \
}                                                                        \
const SReplicator&    _className::s_GetClassReplicator( )                    \
{                                                                        \
    return s_replicator;                                                \
}                                                                        \
const SReplicator&    _className::GetInstanceReplicator( )                \
{                                                                        \
    return s_replicator;                                                \
}



#define DECLARE_RTTI( _className, _baseName )        \
typedef _baseName super;                            \
public:                                                \
DECLARE_INPLACE_CONSTRUCTOR(_className)                \
DECLARE_RTTI_FUNCTIONS(_className, _baseName)        \
static SReplicator s_replicator;                                    
                

#define IMPLEMENT_RTTI( _className, _baseName )        \
IMPLEMENT_INPLACE_CONSTRUCTOR(_className)            \
IMPLEMENT_RTTI_FUNCTIONS(_className, _baseName)        \
SReplicator _className::s_replicator( &_baseName::s_replicator );                        


// RTTI  abstract classes
#define DECLARE_RTTI_ABSTRACT( _className, _baseName )    \
typedef _baseName super;                                \
public:                                                    \
/*DECLARE_INPLACE_CONSTRUCTOR(_className)*/                \
DECLARE_RTTI_FUNCTIONS(_className, _baseName)            \
static SReplicator s_replicator;                                


#define IMPLEMENT_RTTI_ABSTRACT( _className, _baseName )    \
/*IMPLEMENT_INPLACE_CONSTRUCTOR(_className)*/                \
IMPLEMENT_RTTI_FUNCTIONS(_className, _baseName)                \
SReplicator _className::s_replicator( &_baseName::s_replicator );


class KERNEL_API SReplicator
{
#pragma region CONSTRUCTORS
private:
    // not allowed
    SReplicator        ( );
    SReplicator        ( const SReplicator& );
public:
    SReplicator        ( SReplicator* pBaseReplicator );
#pragma endregion

    SReplicator*    m_pBaseReplicator;
};




#endif /*__RTTI_H__*/