#include "ComponentContainer.h"
#include "Core/Components/ComponentBase.h"

#include <hash_map>

class CComponentContainer_PrivateData
{
public:
    // [TODO] Add allocator to use THOT_NEW

    typedef std::hash_map<TComponentID, IComponent*>    TMap;
    typedef std::pair<TComponentID, IComponent*>        TPair;
    typedef TMap::iterator                              TIterator;
    typedef TMap::const_iterator                        TConstIterator;


    TMap                m_map;
};



//---------------------------------------------------------------------------
CComponentContainer::~CComponentContainer()
{
    THOT_COMPILE_ASSERT2( sizeof(CComponentContainer_PrivateData) < THOT_ARRAY_SIZE( ((CComponentContainer*)0)->m_rawData), "ERROR!! PLEASE INCREASE SIZE OF CComponentContainer::m_rawData" );
    //[TODO]
}

Bool CComponentContainer::PushComponent( IComponent* component )
{
    //cannot add in a component container 2 components with the same ID;
    if( HasComponentWithID(component->GetID()) )
    {
        return false;
    }

    m_privateData->m_map.insert( CComponentContainer_PrivateData::TPair(component->GetID(), component) );

    return true;
}

//---------------------------------------------------------------------------
CComponentContainer::CComponentContainer()
    : m_privateData( new(m_rawData) CComponentContainer_PrivateData )
{

}

//---------------------------------------------------------------------------
Bool CComponentContainer::PopComponentWithID( TComponentID id)
{
    CComponentContainer_PrivateData::TIterator it = m_privateData->m_map.find( id );
    if( it == m_privateData->m_map.end() )
    {
        return false;
    }

    m_privateData->m_map.erase(it);

    return true;
}

//---------------------------------------------------------------------------
Bool CComponentContainer::PopComponent( IComponent* component )
{
    THOT_TRAP( component!=0 );
    return PopComponentWithID( component->GetID() );
}

//---------------------------------------------------------------------------
Bool CComponentContainer::HasComponentWithID( TComponentID id)
{
    CComponentContainer_PrivateData::TIterator it = m_privateData->m_map.find( id );
    if( it == m_privateData->m_map.end() )
    {
        return false;
    }

    return true;
}

//---------------------------------------------------------------------------
IComponent* CComponentContainer::GetComponentByID( TComponentID id )
{
    CComponentContainer_PrivateData::TIterator it = m_privateData->m_map.find( id );
    if( it == m_privateData->m_map.end() )
    {
        return NULL;
    }

    return it->second;
}

//---------------------------------------------------------------------------