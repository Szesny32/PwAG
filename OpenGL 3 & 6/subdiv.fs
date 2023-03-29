#version 460 core
uniform float timeFlow;
out vec4 fColor;

void main()
{
   fColor =  vec4( 
	   (sin(timeFlow) + 1.0)/2.0, 
	   (cos(timeFlow) + 1.0)/2.0,
	   1.0 - (sin(timeFlow) + 1.0)/2.0,
	   1.0 
   );
}
