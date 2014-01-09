#version 330

//********************************
//  INPUT ATTRIBUTES
//********************************
layout( location = 0 )      in vec4     inWorldPosition;
layout( location = 1 )      in vec4     inColor;

//********************************
//  OUTPUT
//********************************
smooth  out  vec4   color;


//********************************
//  UNIFORM
//********************************
uniform     mat4        uModelViewMatrix;
uniform     mat4        uModelViewProjectionMatrix;

void main() 
{
    gl_Position = uModelViewProjectionMatrix * inWorldPosition;
    color = inColor;
}