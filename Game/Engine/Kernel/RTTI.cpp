#include "Kernel_PCH.h"
#include "RTTI.h"

#include "Kernel\DataTypes.h"

SReplicator::SReplicator( )
:m_pBaseReplicator        (NULL)
{
}

SReplicator::SReplicator( SReplicator* pBaseReplicator )
:m_pBaseReplicator        (NULL)
{
    m_pBaseReplicator = pBaseReplicator;
}

SReplicator::SReplicator( const SReplicator& )
{

}
