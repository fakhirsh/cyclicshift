
#version 330 core

in          vec3    a_position;
uniform     mat4    PMVMatrix;

void main(){
    gl_Position = PMVMatrix * vec4(a_position.x, a_position.y, a_position.z, 1.0);
}

