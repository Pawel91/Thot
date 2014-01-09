#if !defined(__KERNEL_CONTAINER_H__)
#define __KERNEL_CONTAINER_H__


template<class T>
class CContainer
{
public:

};


#define thForEach( __iterator, __ContainerType, __Container )\
for( __ContainerType::Iterator __iterator = __Container.Begin(); __iterator!=__Container.End(); ++__iterator )

#define stdForEach(__iterator, __ContainerType, __Container) \
for( __ContainerType::iterator __iterator = __Container.begin(); __iterator!=__Container.end(); ++__iterator )



#endif//