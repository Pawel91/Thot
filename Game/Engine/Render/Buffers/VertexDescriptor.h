#ifndef __RENDER_VERTEX_DESCRIPTOR_H__
#define __RENDER_VERTEX_DESCRIPTOR_H__

#include "Render/GLWrapper/OpenGL.h"

namespace RenderLowLevel
{
    // template class that maps a basic type( int, float etc ) to a GLEnum value;
    template<typename TYPE_BasicType>
    class CGlTypeDescriptor;

    // enum to specify which glVertexAttribFunction is to be called
    enum EVertexAttributeFunctionPointerID
    {
        EVertexAttributeFunctionPointer_Normal,
        EAttributeFunctionPointer_IntegerTypes,
        EAttributeFunctionPointer_Double
    };

#if defined ( BEGIN_GL_TYPE_MAP_DESCRIPTION ) || defined (END_GL_TYPE_MAP_DESCRIPTION) || defined( DECLARE_GL_TYPE_MAP )
#   error MACRO NAME CONFLICT! PLEASE RESOLVE
#endif

#define BEGIN_GL_TYPE_MAP_DESCRIPTION()
#define END_GL_TYPE_MAP_DESCRIPTION()
#define DECLARE_GL_TYPE_MAP(__type, __glTypeID, __vertexAttributeFunctionID )    \
    template<>                                                                  \
    class CGlTypeDescriptor<__type>                                             \
    {                                                                           \
    public:                                                                     \
    static const u32 ms_typeID = __glTypeID;                                    \
    static const u32 ms_vertexAttributeFunctionID  = __vertexAttributeFunctionID; \
    };

// map each type to a gl enum type
BEGIN_GL_TYPE_MAP_DESCRIPTION()
    DECLARE_GL_TYPE_MAP( float,     gl::FLOAT,          EVertexAttributeFunctionPointer_Normal );
    DECLARE_GL_TYPE_MAP( double,    gl::DOUBLE,         EAttributeFunctionPointer_Double );
    DECLARE_GL_TYPE_MAP( u8,        gl::UNSIGNED_BYTE,  EAttributeFunctionPointer_IntegerTypes );
    DECLARE_GL_TYPE_MAP( u16,       gl::UNSIGNED_SHORT, EAttributeFunctionPointer_IntegerTypes );
    DECLARE_GL_TYPE_MAP( u32,       gl::UNSIGNED_INT,   EAttributeFunctionPointer_IntegerTypes );
    DECLARE_GL_TYPE_MAP( s8,        gl::BYTE,           EAttributeFunctionPointer_IntegerTypes );
    DECLARE_GL_TYPE_MAP( s16,       gl::SHORT,          EAttributeFunctionPointer_IntegerTypes );
    DECLARE_GL_TYPE_MAP( s32,       gl::INT,            EAttributeFunctionPointer_IntegerTypes );
END_GL_TYPE_MAP_DESCRIPTION()

#undef BEGIN_GL_TYPE_MAP_DESCRIPTION
#undef END_GL_TYPE_MAP_DESCRIPTION
#undef DECLARE_GL_TYPE_MAP

    struct SVertexMemberInfo
    {
        char*       m_vertexAttributeName;      // atribute name in the shader
        u32         m_vertexStructSize;         // the sizeof vertex struct
        u32         m_offset;                   // offset of a member in a vertex struct
        u32         m_glType;                   // native opengl typeID
        u32         m_basicTypeCount;           // component count of the member
        bool        m_mustNormalized;           // if the value must be normalized
        u32         m_attributeLocation;        //[TODO]: this has to be done at run-time somehow
    };

    template<typename TYPE_Vertex>
    class CVertexDescriptor;

    template< u32 GL_AttribFunctionPointerID >
    struct SVertexAttributeFunctor;

    template< >
    struct SVertexAttributeFunctor<EVertexAttributeFunctionPointer_Normal>
    {
        THOT_FORCE_INLINE
        static void Call ( const SVertexMemberInfo& memberInfo )
        {
            //[TODO]; put in SVertexMemberInfo in this order
            gl::VertexAttribPointer(     memberInfo.m_attributeLocation
                                        ,memberInfo.m_basicTypeCount
                                        ,memberInfo.m_glType
                                        ,memberInfo.m_mustNormalized
                                        ,memberInfo.m_vertexStructSize
                                        ,(GLvoid*)memberInfo.m_offset
                                        );
        }

        THOT_FORCE_INLINE 
        static void Call( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer )
        {
            gl::VertexAttribPointer( index, size, type, normalized, stride, pointer );
        }
    };

    template< >
    struct SVertexAttributeFunctor<EAttributeFunctionPointer_IntegerTypes>
    {
        THOT_FORCE_INLINE
        static void Call ( const SVertexMemberInfo& memberInfo )
        {
            //[TODO]; put in SVertexMemberInfo in this order
            gl::VertexAttribIPointer(    memberInfo.m_attributeLocation
                                        ,memberInfo.m_basicTypeCount
                                        ,memberInfo.m_glType
                                        //,memberInfo.m_mustNormalized // ignore this component
                                        ,memberInfo.m_vertexStructSize
                                        ,(GLvoid*)memberInfo.m_offset
                                        );
        }

        THOT_FORCE_INLINE 
        static void Call( GLuint index, GLint size, GLenum type, GLboolean /*unused*/, GLsizei stride, const GLvoid* pointer )
        {
            gl::VertexAttribIPointer( index, size, type, stride, pointer );
        }
    };


// defines use to construct a vertex descriptor
// 
#define DECLARE_VERTEX_DESCRIPTOR(__className)                                  \
    template<>                                                                  \
    class CVertexDescriptor<__className>                                        \
    {                                                                           \
        typedef __className     TVertexType;                                    \
    public:                                                                     \
                                                                                \
        static THOT_FORCE_INLINE                                                \
        void VertexAttributePointerAllMembers();                                \
        static const u32                ms_vertexSize = sizeof(__className);    \
        static const SVertexMemberInfo  ms_membersInfo[];                       \
        static const u32                ms_memberCount;                         \
    };

#define BEGIN_VERTEX_CLASS_DESCRIPTOR(__className)          \
void CVertexDescriptor<__className>::VertexAttributePointerAllMembers(){

#define END_VERTEX_CLASS_DESCRIPTOR(__className)            \
    }


#define REGISTER_VERTEX_MEMBER( __className, __member, __attributeShaderName, __atributeLocation, __type,  __count, __normalized )  \
    gl::EnableVertexAttribArray( __atributeLocation );                                                          \
    SVertexAttributeFunctor< CGlTypeDescriptor<__type>::ms_vertexAttributeFunctionID >::Call                    \
                    (                                                                                           \
                        __atributeLocation,                                                                     \
                        __count,                                                                                \
                        CGlTypeDescriptor<__type>::ms_typeID,                                                   \
                        __normalized,                                                                           \
                        sizeof(__className),                                                                    \
                        (GLvoid*)THOT_MEMBER_OFFSET(__className, __member)                                      \
                    );                                                                                
};



#endif //__RENDER_VERTEX_DESCRIPTOR_H__