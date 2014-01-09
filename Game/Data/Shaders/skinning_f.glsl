#version 330

vec4 textureColor;
vec4 texture2Color;
vec4 textureSpecColor;

//===========================================================
//              HELPERS
//===========================================================

float dot01 ( in vec3 a, in vec3 b )
{
    return max( dot(a,b), 0.0 );
}


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

uniform     int     uUseSkinning;
uniform     SDirectionalLight       uDirLight;
uniform     SPositionalLight        uPosLight;
uniform     SSpotLight              uSpotLight;
uniform     SMaterial               uMaterial;
uniform     vec4                    uGlobalAmbient;
uniform     vec3                    uCameraPos;

uniform 	sampler2D 				myTexture;
uniform     sampler2D               greenTexture;
uniform     sampler2D               specTexture;
//===========================================================
//              INPUT FROM VERTEX SHADER
//===========================================================
struct SFragCommon
{
    vec3    m_position;
    vec3    m_normal;
    vec2    m_textureCoord;
};

in SFragCommon fragmentCommon;
//===========================================================
//              OUTPUT
//===========================================================
out vec4 outColor;


vec4 ApplyLight_Directional( in SFragCommon fragment, in SDirectionalLight dirLight )
{
    vec4 outColor;
    vec3  lightDir;

    // the rezulting color for the fragment; init with ambient term
    outColor = uMaterial.m_ambient * dirLight.m_ambient;

    // normalize the normal send by vertex shader

    //cos between normal and light direction
    float cosNormalLight = dot01( fragment.m_normal, dirLight.m_direction );

    float opacity = uMaterial.m_opacity;

    // if cos > 0.0 add to color the difusse term
    if( cosNormalLight == 0.0 )
    {
        return outColor;
    }

    outColor += uMaterial.m_diffuse * dirLight.m_diffuse * cosNormalLight;
    //outColor += textureColor * dirLight.m_diffuse * cosNormalLight;
    
    vec3 eye    = normalize(uCameraPos - fragment.m_position);
    vec3 halfV  = normalize( eye + dirLight.m_direction );
    
    //cos between half vector and normal
    float NdotHV = dot01( fragment.m_normal, halfV );
    
    float specularFactor = pow( NdotHV, uMaterial.m_shininess );
    
    // if we have transparency
    if( opacity < 0.999 )
    {
        opacity = opacity + ( 1.0 - opacity) * specularFactor;
    }
    

    // add to color the specular term
    outColor += uMaterial.m_specular * dirLight.m_specular * specularFactor;
    //outColor += textureSpecColor * dirLight.m_specular * specularFactor;

    
    //outColor.a = opacity;

    return outColor;
}


vec4 ApplyLight_Positional( in SFragCommon fragment, in SPositionalLight posLight  )
{
    vec4 outColor;

    //compute dir to light and attenuation factor
    vec3 dirToLight = posLight.m_position - fragment.m_position;
    float fDistanceToLight = length(dirToLight);
    dirToLight /= fDistanceToLight;
    float fAttenuationFactor = 1.0/( posLight.m_attenuation.x + posLight.m_attenuation.y *  fDistanceToLight + posLight.m_attenuation.z * fDistanceToLight * fDistanceToLight );


    //add ambient  wiht attenuation;... ambient is not affacted by attenuation..:-?
    //outColor = uMaterial.m_ambient * posLight.m_ambient; //* fAttenuationFactor;
    outColor = texture2Color * posLight.m_ambient;
    //outColor = textureSpecColor * posLight.m_ambient;


    float cosNormalLight = dot01( fragment.m_normal, dirToLight );
    
    // we don`t see the surface
    if( cosNormalLight == 0.0 )
    {
        return outColor;
    }

   outColor += uMaterial.m_diffuse * posLight.m_diffuse * cosNormalLight * fAttenuationFactor;
   
   vec3 eye        = normalize( uCameraPos - fragment.m_position );
   vec3 halfVector = normalize( eye + dirToLight );

   float cosNormalHalfVector = dot01( fragment.m_normal, halfVector );
   float fSpecularFactor = pow( cosNormalHalfVector, uMaterial.m_shininess );
   outColor += uMaterial.m_specular * posLight.m_specular * fSpecularFactor * fAttenuationFactor;
    

    return outColor;
}



vec4 ApplyLight_Spot( in SFragCommon fragment, in SSpotLight spotLight )
{
    vec4 outColor;

    //compute dir to light and attenuation factor
    vec3 dirToLight = spotLight.m_position - fragment.m_position;
    float fDistanceToLight = length(dirToLight);
    dirToLight /= fDistanceToLight;
    float fAttenuationFactor = 1.0/( spotLight.m_attenuation.x + spotLight.m_attenuation.y *  fDistanceToLight + spotLight.m_attenuation.z * fDistanceToLight * fDistanceToLight );


    //add ambient  wiht attenuation
    outColor = uMaterial.m_ambient * spotLight.m_ambient; //* fAttenuationFactor;


    float cosSpotVertex = dot(spotLight.m_direction, -dirToLight );
    
    // the vertex is not in the view
    if( cosSpotVertex < spotLight.m_cosCutoff )
    {
        return outColor;
    }

    
    fAttenuationFactor *= pow( cosSpotVertex, spotLight.m_exponent );

    float cosNormalLight = dot01( fragment.m_normal, dirToLight );
    
    if( cosNormalLight == 0.0 )
    {
        return outColor;
    }
    
    outColor += uMaterial.m_diffuse * spotLight.m_diffuse * cosNormalLight * fAttenuationFactor;
    
    vec3 eye        = normalize( uCameraPos - fragment.m_position );
    vec3 halfVector = normalize( eye + dirToLight );

    float cosNormalHalfVector = dot01( fragment.m_normal, halfVector );
    float fSpecularFactor = pow( cosNormalHalfVector, uMaterial.m_shininess );
    
    //outColor += uMaterial.m_specular * spotLight.m_specular * fSpecularFactor * fAttenuationFactor;
    outColor += textureSpecColor * spotLight.m_specular * fSpecularFactor * fAttenuationFactor;

    return outColor;
}

in vec4 testColor;



void main() 
{
    SFragCommon frag;

    textureColor = texture2D(myTexture, fragmentCommon.m_textureCoord ); 
    texture2Color = texture2D( greenTexture, fragmentCommon.m_textureCoord );
    textureSpecColor = texture2D( specTexture, fragmentCommon.m_textureCoord );

    frag.m_position = fragmentCommon.m_position;
    frag.m_normal = normalize( fragmentCommon.m_normal );

    outColor = ApplyLight_Directional   ( frag, uDirLight );
    outColor = textureColor;
    //outColor += ApplyLight_Positional   ( frag, uPosLight );
    //outColor += ApplyLight_Spot         ( frag, uSpotLight );
}