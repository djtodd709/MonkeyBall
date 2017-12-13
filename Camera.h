#ifndef CAMERA_H
#define CAMERA_H

#include "MathHelper.h"

class Camera{
public:
	Camera();
	void orbitView (void);

	//position of camera and target. camPos is scaled to the size of the terrain
	v3* camPos; //where the camera is
	v3* camTarget;

	//Orbit cam vars
	float camDist;
	float camTwist;
	float camElev;
	float camAzimuth;
	float camX;
	float camZ;
//private:
};
#endif