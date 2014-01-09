#if !defined(__SOIL_BASE_H__)
#define __SOIL_BASE_H__


extern const size_t INVALID_SIZE;

#if defined(__cplusplus)
extern "C"
{
#endif

void* Soil_Malloc( size_t size );
void Soil_Free( void* memory );
size_t GetAllocSize( void* memory );

#if defined(__cplusplus)
}
#endif


#endif  //__SOIL_BASE_H__