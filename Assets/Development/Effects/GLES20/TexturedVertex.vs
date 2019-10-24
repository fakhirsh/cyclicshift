
attribute vec2	a_position;
attribute vec4	a_UV;
//attribute vec4	a_color;
                                          
uniform	mat4	PMVMatrix;
                                          
varying	vec2	v_texCoord;
//varying	vec4	v_color;
                                          
void main(void)
{
    gl_Position = PMVMatrix * vec4(a_position.x, a_position.y, 0.0, 1.0);
    v_texCoord = a_UV.st;
//    v_color = a_color;
}

