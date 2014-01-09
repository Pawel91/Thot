#pragma once
#ifndef __KERNEL_REF_COUNTER_H__
#define __KERNEL_REF_COUNTER_H__


class KERNEL_API CRefCounter
{
public:
     CRefCounter();

    void    AddRef          ();
    u32     GetRefCount     ();
    u32     Release         ();

private:
    u32     m_refCount;
};

#include "RefCounter.inl"


#endif /*__KERNEL_REF_COUNTER_H__*/