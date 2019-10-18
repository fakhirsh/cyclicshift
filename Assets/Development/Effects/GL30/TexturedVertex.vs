
#version 330 core

in      vec3	a_position;
in      vec4	a_UV;                                        
uniform	mat4	PMVMatrix;

out 	vec2	v_texCoord;

void main(void)
{
    gl_Position = PMVMatrix * vec4(a_position.x, a_position.y, a_position.z, 1.0);
    v_texCoord = a_UV.st;
}

