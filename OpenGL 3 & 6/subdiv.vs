#version 460 core
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vNormal;
uniform float timeFlow;
uniform mat4 MVP;

void main()
{
	gl_Position =  MVP*vPosition + vNormal * (timeFlow);

}
