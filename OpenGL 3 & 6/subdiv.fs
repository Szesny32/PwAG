#version 460 core
uniform float timeFlow;
out vec4 fColor;
//in vec4 fPos;


float colorSin(float f){

	return f = (sin(f)+ 1.0)/2.0;
}



void main()
{
//		float x = sin(timeFlow + fPos.x);
//		float y = sin(timeFlow + fPos.y);
//		float z = sin(timeFlow + fPos.z);

//		float x2 = x*x;
//		float y2 = y*y;
//		float z2 = z*z;
//		float ax = atan(x, sqrt(y2 + z2));
//		float ay = atan(y, sqrt(x2 + z2));
//		float az = atan(z, sqrt(x2 + y2));
//
//		float sx = sin(ax) / cos(ax);
//		float sy = sin(ay) / cos(ay);
//		float sz = sin(az) / cos(az);

//		fColor =  vec4( 
//		norm(sin(sx)),
//		norm(sin(sy)),
//		norm(sin(sz)),
//		1.0 
 //  );

 //		colorSin(timeFlow +  gl_FragCoord.x), 
//		colorSin(timeFlow +  gl_FragCoord.y),

  fColor =  vec4(
		colorSin(timeFlow), 
		0.0,
		0.0,
		1.0
  );



}
