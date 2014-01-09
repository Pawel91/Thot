#include "Kernel_PCH.h"
#include "Vector.h"

SVectorProperties::SVectorProperties()
    : m_size        ( 0 )
    , m_capacity    ( 0 )
{
}

//--------------------------------------------------------------------------------
void SVectorProperties::Reset()
{
    m_size     = 0;
    m_capacity = 0;
}

