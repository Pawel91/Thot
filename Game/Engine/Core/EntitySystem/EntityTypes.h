#if !defined(__ENTITY_TYPES_H__)
#define __ENTITY_TYPES_H__

class CEntity;
class IComponent;
class CEntitySystem;
class CEntityHandle;

typedef u16     TEntityID;

enum
{
    INVALID_ENTITY_ID = TEntityID(-1)
};



#endif //__ENTITY_TYPES_H__