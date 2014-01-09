//void main() 
//{
//gl_FrontColor=gl_Color;
//gl_Position=gl_ModelViewProjectionMatrix * gl_Vertex;
//}
//varying vec4 diffuse, ambient;
//varying vec3 normal, halfVector

void main() 
{
    vec3 normal;
    vec3 lightDir;
    vec4 diffuse, ambient, globalAmbient, specular;
    float cosine;
    vec3 eye = normalize(-vec3( gl_ModelViewMatrix * gl_Vertex ) );

    // compute cos between normal and light direction
    normal = normalize( gl_NormalMatrix * gl_Normal );
    lightDir = normalize( vec3( gl_LightSource[0].position ) );
    cosine = max( dot( normal, lightDir ), 0.0 );

    // I = Id * Md * cos;
    diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * cosine;

    // ambient from directional light    
    ambient = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;

    //ambient from global light model
	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;

    if (cosine > 0.0) 
    {
		// normalize the half-vector, and then compute the
		// cosine (dot product) with the normal
        float cos2;
        vec3 vReflected = normalize (- 2.0 * normal * dot( lightDir, normal ) + lightDir );

		cos2 = max(dot(normal, gl_LightSource[0].halfVector.xyz),0.0);
        //cos2 = max( dot( vReflected, -eye ), 0.0 );
		specular = gl_FrontMaterial.specular * gl_LightSource[0].specular *	pow( cos2 ,gl_FrontMaterial.shininess);
	}


    
    gl_FrontColor = diffuse + globalAmbient + ambient + specular;




    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;       
}