
precision mediump float;
uniform sampler2D sampler2d;
                                          
varying vec2	v_texCoord;
//varying vec4	v_color;
                                          
void main (void)
{
    //gl_FragColor = texture2D(sampler2d, v_texCoord) * v_color;
    gl_FragColor = texture2D(sampler2d, v_texCoord);
    //gl_FragColor = v_color;
}

