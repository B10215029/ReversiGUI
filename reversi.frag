#version 430 core
//fragment shader
//uniform float time;
//uniform vec2 mouse;
uniform vec2 resolution;
uniform int[64] data;
out vec4 fragmentcolor; 

void main(){
	float x = 1-gl_FragCoord.y/resolution.y;
	float y = gl_FragCoord.x/resolution.x;
	int index = int(x*8) + int(y*8*8);
	index = int(x*8) + int(y*8)*8;
	if(data[index] == 1)
		fragmentcolor = vec4(0.0, 0.0, 0.0, 1.0);
	else if(data[index] == 2)
		fragmentcolor = vec4(1.0, 1.0, 1.0, 1.0);
	else
		fragmentcolor = vec4(0.5, 0.5, 0.5, 1.0);

}
