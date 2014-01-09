
#version 330

layout( location = 0 )  in vec4 position;
layout( location = 1 )  in vec3 normal;
layout( location = 2 )  in vec4 color;

struct SDirectionalLight
{
    vec3        m_direction;
    vec4        m_diffuse;
    vec4        m_ambient;
    vec4        m_specular;
};

struct SMaterial
{
    vec4        m_diffuse;
    vec4        m_ambient;
    vec4        m_specular;
};



uniform     SDirectionalLight       uDirLight;
uniform     SMaterial               uMaterial;
uniform     vec4                    uGlobalAmbient;



uniform     mat4                    uModelViewMatrix;
uniform     mat4                    uProjectionMatrix;
uniform     mat4                    uMVP;
uniform     mat3                    uNormalMatrix;

out   vec4  fragColor;
void main() 
{
    //fragColor = color;
    fragColor = uMaterial.m_diffuse;
    //fragColor = uDirLight.m_ambient; // so ligth params seems to be ok;
    gl_Position = uMVP * position;
}