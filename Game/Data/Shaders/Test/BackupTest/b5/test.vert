#version 120
varying vec4 diffuse, ambient;
varying vec3 normal, halfVector, eye, reflected;

void main() 
{
    normal = normalize(gl_NormalMatrix * gl_Normal);
    halfVector = gl_LightSource[0].halfVector.xyz;
    
    vec3 lightDir = vec3( gl_LightSource[0].position );

    eye = normalize ( -vec3( gl_ModelViewMatrix * gl_Vertex ) );

    reflected = normalize ( -2.0 * dot( normal, lightDir ) * normal  + lightDir );

    diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
    ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
    ambient += gl_FrontMaterial.ambient * gl_LightModel.ambient;

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}