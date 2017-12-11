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


float MathHelper::magnitude(v3 vector)
{
	float ret = vector.x*vector.x + vector.y*vector.y + vector.z*vector.z;
	return sqrt(ret);
}

v3 MathHelper::reflectVector (v3 incoming, v3 surfaceNormal)
{
	v3 ret;
	ret.x = surfaceNormal.x;
	ret.y = surfaceNormal.y;
	ret.z = surfaceNormal.z;
	ret = ret * magnitude(incoming);
	return ret;
}