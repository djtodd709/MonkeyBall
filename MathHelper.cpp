#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "MathHelper.h"
#include <math.h>


float magnitude(v3 vector)
{
	float ret = vector.x*vector.x + vector.y*vector.y + vector.z*vector.z;
	return sqrt(ret);
}

v3 reflectVector (v3 incoming, v3 surfaceNormal)
{
	v3 ret;
	ret.x = surfaceNormal.x;
	ret.y = surfaceNormal.y;
	ret.z = surfaceNormal.z;
	ret = ret * magnitude(incoming);
	return ret;
}

float dotProduct (v3 vector1, v3 vector2){
	float ret = vector1.x*vector2.x + vector1.y*vector2.y + vector1.z*vector2.z;
	return ret;
}
