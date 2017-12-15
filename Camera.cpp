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

#include "Camera.h"

//Camera movement function

Camera::Camera()
{
	camPos = new v3; //where the camera is
	//Cam pos is currently calculated from camDist etc through matrix transforms, can't set directly
	camPos->x = 0;
	camPos->y = 5;
	camPos->z = 40;
	camTarget = new v3;
	camTarget->x = 0.0f;
	camTarget->y = 0.0f;
	camTarget->z = 0.0f;

	camDist = 40; //Distance from target
	camTwist = 0; //Sideways angle, not used
	camElev = 40; //Angle above x-z plane (horizontal)
	camAzimuth = 40; //Angle away from y-z plane (vertical, clockwise)
}

//Takes a pointer to a position vector, which becomes the followed camera target
void Camera::setTargetObject(v3* targetPos)
{
	printf("Pos: %f,%f,%f\n", targetPos->x, targetPos->y, targetPos->z);
	camTarget = targetPos;
}

void Camera::update()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*
	printf("Dist: %f; Twist: %f; Elev: %f; Azim: %f\n", camDist, camTwist, camElev, camAzimuth);
	printf("Cam Pos: %f,%f,%f\n", camPos->x, camPos->y, camPos->z);
	printf("Target Pos: %f,%f,%f\n", camTarget->x, camTarget->y, camTarget->z);
	*/
        gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
	orbitView();
}

void Camera::orbitView(void)
{
	glLoadIdentity();
	if (this->camDist < 1) {
		camDist = 1;
	}
	if (camElev < -85) {
		camElev = -85;
	} else if (camElev > 85) {
		camElev = 85;
	}

	glTranslatef(0.0, 0.0, -camDist);
	glRotatef(camElev, 1.0, 0.0, 0.0);
	glRotatef(-camAzimuth, 0.0, 1.0, 0.0);
	glRotatef(camTwist, 0.0, 0.0, 1.0);
	glTranslatef(-camTarget->x, 0, 0);
	glTranslatef(0, -camTarget->y, 0);
	glTranslatef(0, 0, -camTarget->z);
}