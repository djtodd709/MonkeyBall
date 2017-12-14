#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <cstdio>
#include "Player.h"

Player::Player(const char * pathToAssetFolder) : Entity(pathToAssetFolder)
{
	rootPos = new v3;
	rootPos->x = 0;
	rootPos->y = 0;
	rootPos->z = 0;
}