#version 330
//===========================================================
//              ATTRIBUTES
//===========================================================
layout( location = 0 )  in vec4     position;
layout( location = 1 )  in vec3     normal;
layout( location = 2 )  in vec3     texCoord;
layout( location = 3 )  in vec4     color;

//===========================================================
//              UNIFORMS
//===========================================================

struct SDirectionalLight
{
    vec3        m_direction;
    vec4        m_diffuse;
    vec4        m_ambient;
    vec4        m_specular;
};

struct SPositionalLight
{
    vec3        m_position;
    vec4        m_diffuse;
    vec4        m_ambient;
    vec4        m_specular;
    vec3        m_attenuation;
};

struct SSpotLight
{
    vec3        m_position;
    vec4        m_diffuse;
    vec4        m_ambient;
    vec4        m_specular;
    vec3        m_attenuation;
    vec3        m_direction;
    float       m_cosCutoff;
    float       m_exponent;
};

struct SMaterial
{
    vec4        m_diffuse;
    vec4        m_ambient;
    vec4        m_specular;
    float       m_shininess;
    float       m_opacity;
};

uniform     SDirectionalLight       uDirLight;
uniform     SPositionalLight        uPosLight;
uniform     SSpotLight              uSpotLight;
uniform     SMaterial               uMaterial;
uniform     vec4                    uGlobalAmbient;


uniform     mat4                    uModelMatrix;
uniform     mat4                    uViewMatrix;
uniform     mat4                    uProjectionMatrix;
uniform     mat4                    uModelViewMatrix;
uniform     mat4                    uViewProjectionMatrix;
uniform     mat4                    uMVP;
uniform     mat3                    uNormalMatrix;
uniform     vec3                    uCameraPos;

//===========================================================
//                  VARYING
//===========================================================
struct SFragCommon
{
    vec3    m_position;
    vec3    m_normal;
    vec2    m_textureCoord;
    vec4    m_color;
};

out SFragCommon fragmentCommon;

out vec4 testColor;

void main() 
{
    vec4 worldPosition = uModelMatrix * position;
    fragmentCommon.m_position     = worldPosition.xyz;
    fragmentCommon.m_normal       = (normalize ( uModelMatrix * vec4(normal, 0.0 ) ) ).xyz;
    fragmentCommon.m_textureCoord = vec2( fract(texCoord.x), fract(texCoord.y) );
    fragmentCommon.m_color = color;

    gl_Position = uMVP * position;
}