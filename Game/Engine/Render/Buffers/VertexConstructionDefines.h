#pragma once
#ifndef __RENDER_VERTEX_CONSTRUCTION_DEFINES_H__
#define __RENDER_VERTEX_CONSTRUCTION_DEFINES_H__

/*
    HELPER MACROS USED TO CONSTRUCT A GENERIC VERTEX CLASS;
*/

//#ifdef _DEBUG
#define DECLARE_VERTEX_DEBUG_PRINT_FUNCTIONS(__className)   \
static void DebugPrint()                        \
{                                               \
    THOT_TRACE_LINE("Vertex class [%s]", THOT_STRINGIFY(__className) );    \
    const u32 size = THOT_ARRAY_SIZE(ms_offsets);    \
    for(u32 i=0; i<size;i++)                    \
    {                                           \
        THOT_TRACE_LINE( "[%d]:   offsets[%d]     typeIDs[%d]     CompCount[%d]   att[%d]     normalized[%d]", i, ms_offsets[i], ms_typeIDs[i], ms_compCount[i], ms_attributeLocations[i], ms_normalized[i] );    \
    }                                          \
    THOT_TRACE_LINE(""); \
 }  \
static char* GetVertexClassName() { return THOT_STRINGIFY(__className);}

//#else
//#define DECLARE_VERTEX_DEBUG_PRINT_FUNCTIONS
//#endif

#define DECLARE_VERTEX_STATIC_ARRAYS(__size)        \
static u32  ms_offsets              [__size];       \
static u32  ms_typeIDs              [__size];       \
static u32  ms_compCount            [__size];       \
static u32  ms_attributeLocations   [__size];       \
static u32  ms_normalized           [__size];       \
static TVertexAttributePointerCallback ms_vertexAttributeFunctions [__size]



#define DECLARE_VERTEX_FUNCTIONS                                                            \
static u32 GetAttributeCount( ) { return THOT_ARRAY_SIZE(ms_offsets); }                          \
private:                                                                                    \
static Bool SetGeneric ( u32* prop, u32 memberOffset, u32 value )                           \
{                                                                                           \
    u32 size = THOT_ARRAY_SIZE(ms_offsets);                                                      \
    if ( memberOffset > ms_offsets[size-1]  )                                               \
    {                                                                                       \
        return false;                                                                       \
    }                                                                                       \
                                                                                            \
    for( u32 i=0; i<size; i++ )                                                             \
    {                                                                                       \
        if( ms_offsets[i]==memberOffset )                                                   \
        {                                                                                   \
            prop[i] = value;                                                                \
            return true;                                                                    \
        }                                                                                   \
        else if( ms_offsets[i] > memberOffset )                                             \
        {                                                                                   \
            return false;                                                                   \
        }                                                                                   \
    }                                                                                       \
    return false;                                                                           \
}                                                                                           \
public:                                                                                     \
static Bool SetAttributeLocation( u32 memberOffset, u32 attributeLocation )                 \
{                                                                                           \
    return SetGeneric( ms_attributeLocations, memberOffset, attributeLocation );            \
}                                                                                           \
static Bool SetNormalized( u32 memberOffset, Bool normalized )                              \
{                                                                                           \
    return SetGeneric( ms_normalized, memberOffset, (u32)normalized );                      \
}


// [TODO] add friend class that will be responsable for register vertex structs
#define DECLARE_VERTEX_REGISTRATION_VALIDATOR   \
private:        \
static  Bool        ms_vertexStructIsRegistred; \
public:                                                 \
static  void        OnRegister(){ms_vertexStructIsRegistred = true;}    \
static  void        OnUnregister(){ms_vertexStructIsRegistred = false;} \
public: \
static  Bool        IsRegistred(){ return ms_vertexStructIsRegistred; }


#define IMPLEMENT_VERTEX_REGISTRATION_VALIDATOR(__className)   \
Bool __className::ms_vertexStructIsRegistred = false;


#define DECLARE_VERTEX_STATIC_INSTANCE(__className) \
static __className* ms_instance;

#define IMPLEMENT_VERTEX_STATIC_INSTANCE(__className)   \
__className* __className::ms_instance = new __className;





#define DECLARE_MEMBERS_GENERIC( __className )  \
    DECLARE_VERTEX_STATIC_INSTANCE(__className) \
    DECLARE_VERTEX_REGISTRATION_VALIDATOR       \
    DECLARE_VERTEX_FUNCTIONS                \
    DECLARE_VERTEX_DEBUG_PRINT_FUNCTIONS(__className)


#define DECLARE_MEMBERS1(__className,m0) \
DECLARE_MEMBERS_GENERIC(__className)     \
DECLARE_VERTEX_STATIC_ARRAYS(1)

#define DECLARE_MEMBERS2(__className,m0,m1) \
DECLARE_MEMBERS_GENERIC(__className)        \
DECLARE_VERTEX_STATIC_ARRAYS(2)         

#define DECLARE_MEMBERS3(__className,m0,m1,m2) \
    DECLARE_MEMBERS_GENERIC(__className)        \
    DECLARE_VERTEX_STATIC_ARRAYS(3)
   

#define DECLARE_MEMBERS4(__className,m0,m1,m2, m4) \
DECLARE_MEMBERS_GENERIC(__className)            \
DECLARE_VERTEX_STATIC_ARRAYS(4)

#define DECLARE_MEMBERS5(__className,m0,m1,m2, m4, m5) \
DECLARE_MEMBERS_GENERIC(__className)            \
DECLARE_VERTEX_STATIC_ARRAYS(5)

#define DECLARE_MEMBERS6(__className,m0,m1,m2, m4, m5, m6) \
DECLARE_MEMBERS_GENERIC(__className)            \
DECLARE_VERTEX_STATIC_ARRAYS(6)

#define DECLARE_MEMBERS7(__className,m0,m1,m2, m4, m5, m6, m7) \
DECLARE_MEMBERS_GENERIC(__className)            \
DECLARE_VERTEX_STATIC_ARRAYS(7)



#define IMPLEMENT_INSTANCE(__className) \
__className* __className::ms_instance = new __className;

#define IMPLEMENT_ELEMENT_OFFSETS(__className,_m) \
    THOT_MEMBER_OFFSET(__className,_m)

#define IMPLEMENT_ELEMENT_TYPEID(__className,_m) \
GetGlTypeID(__className::ms_instance->_m.Get())

#define IMPLEMENT_ELEMENT_COMP_COUNT(__className,_m) \
sizeof(__className::ms_instance->_m)/sizeof(__className::ms_instance->_m.Get())

#define IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,_m) \
GetVertexAttributeFunction(GetGlTypeID(__className::ms_instance->_m.Get()))


#define IMPLEMENT_MEMBERS_GENERIC(__className)  \
IMPLEMENT_INSTANCE(__className) \
IMPLEMENT_VERTEX_REGISTRATION_VALIDATOR(__className)


#define IMPLEMENT_MEMBERS1(__className,m0)   \
IMPLEMENT_MEMBERS_GENERIC(__className)      \
u32 __className::ms_offsets             [1] = { IMPLEMENT_ELEMENT_OFFSETS(__className,m0) }; \
u32 __className::ms_typeIDs             [1] = { IMPLEMENT_ELEMENT_TYPEID(__className,m0) }; \
u32 __className::ms_compCount           [1] = { IMPLEMENT_ELEMENT_COMP_COUNT(__className, m0) }; \
u32  __className::ms_attributeLocations [1] = {0};   \
u32 __className::ms_normalized          [1] = {0};  \
TVertexAttributePointerCallback __className::ms_vertexAttributeFunctions[1] = {IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m0)};



#define IMPLEMENT_MEMBERS2(__className,m0,m1) \
IMPLEMENT_MEMBERS_GENERIC(__className)      \
u32 __className::ms_offsets             [2] = { IMPLEMENT_ELEMENT_OFFSETS(__className,m0), IMPLEMENT_ELEMENT_OFFSETS(__className,m1)}; \
u32 __className::ms_typeIDs             [2] = { IMPLEMENT_ELEMENT_TYPEID(__className,m0), IMPLEMENT_ELEMENT_TYPEID(__className,m1)}; \
u32 __className::ms_compCount           [2] = { IMPLEMENT_ELEMENT_COMP_COUNT(__className, m0), IMPLEMENT_ELEMENT_COMP_COUNT(__className,m1) }; \
u32  __className::ms_attributeLocations [2] = {0,0};   \
u32 __className::ms_normalized          [2] = {0,0}; \
TVertexAttributePointerCallback __className::ms_vertexAttributeFunctions[2] = {IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m0),IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m1)};


#define IMPLEMENT_MEMBERS3(__className, m0,m1,m2) \
IMPLEMENT_MEMBERS_GENERIC(__className)      \
u32 __className::ms_offsets             [3] = { IMPLEMENT_ELEMENT_OFFSETS(__className,m0), IMPLEMENT_ELEMENT_OFFSETS(__className,m1), IMPLEMENT_ELEMENT_OFFSETS(__className,m2)}; \
u32 __className::ms_typeIDs             [3] = { IMPLEMENT_ELEMENT_TYPEID(__className,m0), IMPLEMENT_ELEMENT_TYPEID(__className,m1), IMPLEMENT_ELEMENT_TYPEID(__className,m2)}; \
u32 __className::ms_compCount           [3] = { IMPLEMENT_ELEMENT_COMP_COUNT(__className, m0), IMPLEMENT_ELEMENT_COMP_COUNT(__className,m1), IMPLEMENT_ELEMENT_COMP_COUNT(__className,m2) }; \
u32  __className::ms_attributeLocations [3] = {0,0,0};   \
u32 __className::ms_normalized          [3] = {0,0,0};  \
TVertexAttributePointerCallback __className::ms_vertexAttributeFunctions[3] = {IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m0), IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m1), IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m2)};


#define IMPLEMENT_MEMBERS4(__className, m0,m1,m2,m3) \
IMPLEMENT_MEMBERS_GENERIC(__className)      \
u32 __className::ms_offsets             [4] = { IMPLEMENT_ELEMENT_OFFSETS(__className,m0), IMPLEMENT_ELEMENT_OFFSETS(__className,m1), IMPLEMENT_ELEMENT_OFFSETS(__className,m2),  IMPLEMENT_ELEMENT_OFFSETS(__className,m3)}; \
u32 __className::ms_typeIDs             [4] = { IMPLEMENT_ELEMENT_TYPEID(__className,m0), IMPLEMENT_ELEMENT_TYPEID(__className,m1), IMPLEMENT_ELEMENT_TYPEID(__className,m2), IMPLEMENT_ELEMENT_TYPEID(__className,m3)}; \
u32 __className::ms_compCount           [4] = { IMPLEMENT_ELEMENT_COMP_COUNT(__className, m0), IMPLEMENT_ELEMENT_COMP_COUNT(__className,m1), IMPLEMENT_ELEMENT_COMP_COUNT(__className,m2), IMPLEMENT_ELEMENT_COMP_COUNT(__className,m3) }; \
u32  __className::ms_attributeLocations [4] = {0,0,0,0};   \
u32 __className::ms_normalized          [4] = {0,0,0,0};    \
TVertexAttributePointerCallback __className::ms_vertexAttributeFunctions[4] = {IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m0), IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m1), IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m2), IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m3) };


#define IMPLEMENT_MEMBERS5(__className, m0,m1,m2,m3, m4) \
IMPLEMENT_MEMBERS_GENERIC(__className)      \
u32 __className::ms_offsets             [5] = { IMPLEMENT_ELEMENT_OFFSETS(__className,m0), IMPLEMENT_ELEMENT_OFFSETS(__className,m1), IMPLEMENT_ELEMENT_OFFSETS(__className,m2),  IMPLEMENT_ELEMENT_OFFSETS(__className,m3), IMPLEMENT_ELEMENT_OFFSETS(__className,m4)}; \
u32 __className::ms_typeIDs             [5] = { IMPLEMENT_ELEMENT_TYPEID(__className,m0), IMPLEMENT_ELEMENT_TYPEID(__className,m1), IMPLEMENT_ELEMENT_TYPEID(__className,m2), IMPLEMENT_ELEMENT_TYPEID(__className,m3), IMPLEMENT_ELEMENT_TYPEID(__className,m4)}; \
u32 __className::ms_compCount           [5] = { IMPLEMENT_ELEMENT_COMP_COUNT(__className, m0), IMPLEMENT_ELEMENT_COMP_COUNT(__className,m1), IMPLEMENT_ELEMENT_COMP_COUNT(__className,m2), IMPLEMENT_ELEMENT_COMP_COUNT(__className,m3), IMPLEMENT_ELEMENT_COMP_COUNT(__className,m4) }; \
u32  __className::ms_attributeLocations [5] = {0,0,0,0,0};   \
u32 __className::ms_normalized          [5] = {0,0,0,0,0};  \
TVertexAttributePointerCallback __className::ms_vertexAttributeFunctions[5] = {IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m0), IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m1), IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m2), IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m3), IMPLEMENT_ELEMENT_VERTEX_ATTRIBUTE_FUNCTION(__className,m4) };


//#define DECLARE_ANIMATED_VERTEX(__className, __memberBoneIdx, __memberBoneWeights)  \
//Bool AddBoneData( u32 boneID, float boneWeight )
//{
//    
//}


//#define DECLARE_VERTEX_DESCRIPTOR(__descriptorFlags)    \
//static const u64 ms_vertexDescriptor = __descriptorFlags;


#endif /*__RENDER_VERTEX_CONSTRUCTION_DEFINES_H__*/