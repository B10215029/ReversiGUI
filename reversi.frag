#version 430 core
//fragment shader
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
out vec4 fragmentcolor; 

void main(){
	fragmentcolor = vec4(0.0, 0.0, 1.0, 1.0); 
}
