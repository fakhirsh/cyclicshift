/*
precision mediump float;

uniform vec4    u_color;
                                          
void main (void)
{
    gl_FragColor = u_color;
}

*/

#version 330 core

uniform vec4    u_color;

// Ouput data
out vec4 color;

void main()
{

	// Output color = red 
	color = u_color;

}
