
#version 330 core

uniform sampler2D sampler2d;
                                          
in      vec2    v_texCoord;

//out     vec4    color;

void main (void)
{
    //gl_FragColor = texture2D(sampler2d, v_texCoord) * v_color;
    //gl_FragColor = v_color;
    gl_FragColor = texture2D(sampler2d, v_texCoord);
}

