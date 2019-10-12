/*
precision mediump float;

uniform vec4    u_color;
                                          
void main (void)
{
    gl_FragColor = u_color;
}

*/

#version 330 core

// Ouput data
out vec3 color;

void main()
{

	// Output color = red 
	color = vec3(0,1,1);

}
