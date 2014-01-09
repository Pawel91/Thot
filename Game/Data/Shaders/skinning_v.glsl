#version 330
//===========================================================
//              ATTRIBUTES
//===========================================================
layout( location = 0 )  in vec4     position;
layout( location = 1 )  in vec3     normal;
layout( location = 2 )  in vec3     texCoord;
layout( location = 3 )  in ivec4    boneIndexes;    // bone indexes
layout( location = 4 )  in vec4     boneWeights;    // bone weights;


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

const int   MAX_BONE_SIZE=124;
uniform     mat4    uBoneMatrices[MAX_BONE_SIZE];
uniform     int     uBoneCount;
uniform     int     uUseSkinning;


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
};

out SFragCommon fragmentCommon;

out vec4 testColor;

vec4  GetMeshPos()
{
    if( uUseSkinning == 0 )
    {
        return position;
    }
    else
    {
    vec4 finalVertexPos = vec4( 0.0, 0.0, 0.0, 1.0 );

    int boneIdx = boneIndexes.x;
    float boneWeight = boneWeights.x;
    //finalVertexPos += position * uBoneMatrices[boneIdx] * boneWeight;
    finalVertexPos = boneWeight * uBoneMatrices[boneIdx] * position;

    boneIdx = boneIndexes.y;
    boneWeight = boneWeights.y;
    finalVertexPos = finalVertexPos + boneWeight * uBoneMatrices[boneIdx] * position;

    boneIdx = boneIndexes.z;
    boneWeight = boneWeights.z;
    finalVertexPos = finalVertexPos + boneWeight * uBoneMatrices[boneIdx] * position;

    boneIdx = boneIndexes.w;
    boneWeight = boneWeights.w;
    finalVertexPos = finalVertexPos + boneWeight * uBoneMatrices[boneIdx] * position;


    return finalVertexPos;
    }
}

void main() 
{

    vec4 meshPosition = GetMeshPos();
    vec4 worldPosition = uModelMatrix * meshPosition;
    //vec4 worldPosition = uModelMatrix * position;
    fragmentCommon.m_position     = worldPosition.xyz;
    fragmentCommon.m_normal       = (normalize ( uModelMatrix * vec4(normal, 0.0 ) ) ).xyz;
    fragmentCommon.m_textureCoord = texCoord.xy;

    gl_Position = uMVP * meshPosition;
}