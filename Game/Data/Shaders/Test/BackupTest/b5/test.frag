#version 120

varying vec4 diffuse, ambient;
varying vec3 normal, halfVector, eye, reflected;

void main() 
{
    vec3 n, lightDir;
    float NdotL;

    lightDir = vec3( gl_LightSource[0].position );

    // the rezulting color for the fragment; init with ambient term
    vec4 color = ambient;

    // normalize the normal send by vertex shader
    n = normalize(normal);
    
    //cos between normal and light direction
    NdotL = max( dot( n, lightDir ), 0.0 );


    // if cos > 0.0 add to color the difusse term
    if( NdotL > 0.0 )
    {
        color += diffuse * NdotL;

        // normalize the half vector send by vertex shader
        vec3 E = normalize(eye);
        vec3 refl = normalize( reflected );
        vec3 halfV = normalize( halfVector );
        
        //cos between half vector and normal
        float NdotHV = max( dot( n, halfV ), 0.0 );
        //float NdotHV = max( dot( E, refl ), 0.0 );
        
        // add to color the specular term
        color += gl_FrontMaterial.specular * gl_LightSource[0].specular * pow( NdotHV, gl_FrontMaterial.shininess); 
    }

    gl_FragColor = color;
}