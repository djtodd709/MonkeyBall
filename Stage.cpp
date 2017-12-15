#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "Stage.h"

Stage::Stage()
{
	playerStart = new v3;
	playerStart->x = 0.0f;
	playerStart->y = 0.0f;
	playerStart->z = 0.0f;
}