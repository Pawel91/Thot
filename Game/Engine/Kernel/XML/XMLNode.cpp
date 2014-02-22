#include "Kernel_PCH.h"

#include "XMLNode.h"

void*   rapidXmlAllocator_allocate  ( thTSize size)
{
    return smalloc(size);
}

void    rapidXmlAllocator_free      (void* data )
{
    sfree(data);
}
