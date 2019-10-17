/*
attribute vec2	a_position;
                                          
uniform	mat4	PMVMatrix;

uniform vec4    u_color;
                                          
void main(void)
{
    gl_Position = PMVMatrix * vec4(a_position.x, a_position.y, 0.0, 1.0);
}

*/

#version 330 core

// Input vertex data, different for all executions of this shader.
attribute   vec3    a_position;
uniform     mat4    PMVMatrix;
uniform     vec4    u_color;

void main(){

    gl_Position = PMVMatrix * vec4(a_position.x, a_position.y, a_position.z, 1.0);

//    gl_Position = vec4(a_position.x, a_position.y, a_position.z, 1.0);

}

