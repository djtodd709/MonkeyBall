#include "Camera.h"
#include <stdio.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

//Camera movement function

void orbitView(float dist, float twist, float elev, float azimuth)
{
	//printf("Dist: %f; Twist: %f; Elev: %f; Azim: %f\n", dist, twist, elev, azimuth);
	if (dist > 1) {
		dist = 1;
	}
	if (elev < -85) {
		elev = -85;
	} else if (elev > 85) {
		elev = 85;
	}
	glTranslatef(0.0, 0.0, dist);
	glRotatef(-twist, 0.0, 0.0, 1.0);
	glRotatef(-elev, 1.0, 0.0, 0.0);
	//glTranslatef(-camX, 0, 0);
	//glTranslatef(0, 0, -camZ);
	glRotatef(azimuth, 0.0, 1.0, 0.0);
	//glTranslatef(-(float)gridsize / 2, 0, -(float)gridsize/2);
}