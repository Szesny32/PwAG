#version 460 

layout(triangles) in;

//wyjsciowym prymitywem powinny byc punkty!!!
//layout(points, max_vertices=200) out;
layout(triangle_strip, max_vertices = 6) out;

uniform float time;

int level = 2;

vec4 CG;

void main() {
	
	CG = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position)/3.0;

	for(int i = 0; i < gl_in.length(); i++) {
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}