#if !defined( __RENDER_SHADER_PARAMETER_IMPL_H__ )
#define __RENDER_SHADER_PARAMETER_IMPL_H__

#include "Render/ShaderFramework/ShaderParameter.h"
#include "Render/ShaderFramework/ShaderLayout/ShaderUniform.h"
#include "Render/Textures/Texture.h"


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!ALL CShaderParameters MUST BE DECLARED WITH RENDER_API !!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



template<>
class RENDER_API CShaderParameter<CTexture,1>:public CShaderParameterTemplateBase<CTexture, 1>
{
public:

    const CTexture* operator->()const   { return &m_data;}
    CTexture* operator->()              { return &m_data;}
    operator CTexture&()                { return m_data;}
    operator const CTexture&()          { return m_data;}

    virtual void SetParameterShaderData ( u32 uniformLocation ) override
    {
        CTexture& texture = m_data;
        THOT_ASSERT( texture.IsValid(), "TRYING TO SETUP AN INVALID TEXTURE AS PARAMETER TO SHADER");
        gl::Uniform1i( uniformLocation, texture.GetProperties().m_textureUnit );
        texture.Bind();
    }
};


template< >
class CShaderParameter<s32, 1>: public CShaderParameterTemplateBase<s32, 1>
{

public:

    operator s32 () const   { return m_data;}
    operator s32&()         { return m_data;}

    void    operator = ( s32 other)
    {
        m_data = other;
    }


    virtual void SetParameterShaderData ( u32 uniformLocation ) override
    {
        gl::Uniform1iv( uniformLocation, 1, ( GLint*)&m_data );
    }
};

template< u32 SIZE>
class CShaderParameter<s32, SIZE>: public CShaderParameterTemplateBase<s32, SIZE>
{
public:
    virtual void SetParameterShaderData() override
    {
        gl::Uniform1iv( uniformLocation, SIZE, ( GLint*)m_data );
    }
};

//======================================================
//          CColor
//======================================================


//======================================================
//          m4x4
//======================================================
template<>
class RENDER_API CShaderParameter<m4x4, 1> : public CShaderParameterTemplateBase<m4x4, 1>
{
public:
    THOT_FORCE_INLINE m4x4& GetMatrix()
    {
        return m_data;
    }

    THOT_FORCE_INLINE operator m4x4&()
    {
        return m_data;
    }

    THOT_FORCE_INLINE const m4x4& operator = ( const m4x4& other )
    {
        m_data = other;
        return m_data;
    }

    THOT_FORCE_INLINE const tVect3& operator [] ( u32 index)const
    {
        return m_data.operator [](index);
    }

    THOT_FORCE_INLINE tVect3& operator [] ( u32 index)
    {
        return m_data.operator [](index);
    }


    virtual void SetParameterShaderData ( u32 uniformLocation ) override
    {
        gl::UniformMatrix4fv( uniformLocation, 1, gl::FALSE, (GLfloat*) m_data );
    }
};

template<  u32 SIZE  >
class RENDER_API CShaderParameter<m4x4, SIZE> : public CShaderParameterTemplateBase<m4x4, SIZE>
{
public:
    virtual void SetParameterShaderData ( u32 uniformLocation ) override
    {
        gl::UniformMatrix4fv( uniformLocation, SIZE, gl::FALSE, (GLfloat*) m_data );
    }
};

template<>
class RENDER_API CShaderParameter<m3x3, 1>: public CShaderParameterTemplateBase<m3x3, 1>
{
public:
    CShaderParameter( const m3x3& other )
        
    {
        m_data = other;
    }

    THOT_FORCE_INLINE const tVect3&  operator[](u32 index)const
    {
        return m_data.operator[](index);
    }

    THOT_FORCE_INLINE tVect3&  operator[](u32 index)
    {
        return m_data.operator[](index);
    }


    THOT_FORCE_INLINE const m3x3& operator = ( const m3x3& other )
    {
        m_data = other;
        return m_data;
    }


    virtual void SetParameterShaderData( u32 uniformLocation ) override
    {
        gl::UniformMatrix3fv( uniformLocation, 1, gl::FALSE, (GLfloat*) m_data );
    }
};

//======================================================
//          tVect3
//======================================================
template<>
class RENDER_API CShaderParameter<tVect3> : public CShaderParameterTemplateBase<tVect3, 1>
{
public:

    operator tVect3&()
    {
        return m_data;
    }

    operator const tVect3&()const
    {
        return m_data;
    }

    const tVect3& operator = ( const tVect3& other )
    {
        m_data = other;
        return other;
    }

    virtual void SetParameterShaderData ( u32 uniformLocation )
    {
        gl::Uniform3fv( uniformLocation, 1, (GLfloat*)m_data );
    }
};



//======================================================
//          CColor
//======================================================
template<>
class RENDER_API CShaderParameter<CColor>: public CShaderParameterTemplateBase<CColor,1>
{
public:
    operator CColor&()
    {
        return m_data;
    }

    operator const CColor&()const
    {
        return m_data;
    }

    const CColor& operator = ( const CColor& other)
    {
        m_data = other;
        return *this;
    }


    virtual void SetParameterShaderData ( u32 uniformLocation )
    {
        gl::Uniform4fv( uniformLocation, 1, (GLfloat*)m_data );
    }
};

//======================================================
//          float
//======================================================
template<>
class RENDER_API CShaderParameter<float>: public CShaderParameterTemplateBase<float, 1>
{
public:
    operator float&()
    {
        return m_data;
    }

    operator float()const
    {
        return m_data;
    }

    float operator = ( float other)
    {
        m_data = other;
        return other;
    }

    virtual void SetParameterShaderData ( u32 uniformLocation )
    {
        gl::Uniform1fv( uniformLocation, 1, (GLfloat*)&m_data );
    }

};

//template<u32 SIZE >
//class CShaderParameter<float, SIZE>
//{
//    CShaderParameter();
//
//    virtual void SetParameterShaderData ( u32 uniformLocation )
//    {
//        gl::Uniform1fv( uniformLocation, SIZE, (GLfloat*)m_data );
//    }
//
//};



#endif //__RENDER_SHADER_PARAMETER_IMPL_H__