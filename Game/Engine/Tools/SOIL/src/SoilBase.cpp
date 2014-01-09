#include "SoilBase.h"
#include "stdlib.h"
#include <map>



//map that holds all the allocated memory inside soil
std::map<void*, size_t>   g_allocatedMemorySizeMap;
const size_t INVALID_SIZE = 0xFFFFFFFF;

void* Soil_Malloc( size_t size )
{

    void* memory = malloc(size);
    g_allocatedMemorySizeMap.insert( std::pair<void*, size_t>( memory, size ) );
    return memory;
}

void Soil_Free( void* memory )
{
    g_allocatedMemorySizeMap.erase(memory);
    free( memory );
}

size_t GetAllocSize( void* memory )
{
    std::map<void*, size_t>::iterator  it = g_allocatedMemorySizeMap.find(memory);
    if( it != g_allocatedMemorySizeMap.end() )
    {
        return it->second;
    }

    return INVALID_SIZE;
}