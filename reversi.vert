#version 430 core
//vertex shader
const vec4 vertexs[4]=vec4[](
	vec4(-1, -1, 0.5, 1),
	vec4( 1, -1, 0.5, 1),
	vec4( 1,  1, 0.5, 1),
	vec4(-1,  1, 0.5, 1));

void main(){
	gl_Position = vertexs[gl_VertexID];
}
