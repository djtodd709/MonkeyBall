#ifndef CAMERA_H
#define CAMERA_H

#include "MathHelper.h"

class Camera{
public:
	Camera();
	void orbitView (void);
	void setTargetObject(v3* targetPos);
	void update();

	//position of camera and target. camPos is scaled to the size of the terrain
	v3* camPos; //where the camera is
	v3* camTarget;

	//Orbit cam vars
	float camDist;
	float camTwist;
	float camElev;
	float camAzimuth;
//private:
};
#endif