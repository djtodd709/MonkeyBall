#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "Collider.h"

Collider::Collider()
{
	
}

bool Collider::importCollision(char* path)
{
	//TODO: Implement
}

v3 Collider::checkCollision(v3 incoming)
{
	
}