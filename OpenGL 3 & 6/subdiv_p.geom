#version 460 

layout(triangles) in;

//wyjsciowym prymitywem powinny byc punkty!!!
layout(points, max_vertices=200) out;
//layout(triangle_strip, max_vertices = 6) out;
//layout(line_strip, max_vertices = 2) out;

uniform float time;

out vec4 fPos;
int level = 2;

vec4 CG;

vec4 calcBarycentricCoords(float s, float t){
	return gl_in[0].gl_Position + s *(gl_in[1].gl_Position - gl_in[0].gl_Position) + t * (gl_in[2].gl_Position - gl_in[0].gl_Position);
}


void main() {
	CG = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position)/3.0;

	gl_Position = CG;
	gl_Position = calcBarycentricCoords(0, 0.5);
	EmitVertex();
	EndPrimitive();

	gl_Position = calcBarycentricCoords(0.5, 0);
	EmitVertex();
	EndPrimitive();

	gl_Position = calcBarycentricCoords(0.5, 0.5);
	EmitVertex();
	EndPrimitive();

		for(int i = 0; i < gl_in.length(); i++) {
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
		EndPrimitive();
	}

}


//void main() {
	
//	CG = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position)/3.0;
//	
//	for(int i = 0; i < gl_in.length(); i++) {
//		gl_Position = gl_in[i].gl_Position;
//		fPos = gl_Position;
//		EmitVertex();
//	}
//	EndPrimitive();
//}