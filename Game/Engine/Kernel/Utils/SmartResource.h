#pragma once
#ifndef __KERNEL_SMART_RESOURCE_H__
#define __KERNEL_SMART_RESOURCE_H__

#include "RefCounter.h"


class IResource
{


    IResource();
    virtual ~IResource()    = 0;
    void Destroy()          = 0;
};
IResource::~IResource(){}


//[TODO]
template<class T>
class CSmartResource
{
    CSmartResource ( );
    CSmartResource ( const CSmartResource<T>& other  )
    const CSmartResource<T>& operator = ( const CSmartResource<T>& other );


//=======================================
//      HELPERS
//=======================================
protected:
    void        InitFromOther       ( const CSmartResource<T>& other );


//=======================================
//      MEMBERS
//=======================================
protected:
   CRefCounter*         m_refCounter;

};


#include "SmartResource.inl"

#endif