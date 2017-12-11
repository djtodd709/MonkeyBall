#ifndef __MATHHELPER_H__
#define __MATHHELPER_H__

#include <stdio.h>
#include <math.h>

struct v3
{
	float x;
	float y;
	float z;
	
	inline v3 operator+ (v3 o)
	{
		this->x = this->x + o.x;
		this->y = this->y + o.y;
		this->z = this->z + o.z;
		return *this;
	}
	inline v3 operator- (v3 o)
	{
		this->x = this->x - o.x;
		this->y = this->y - o.y;
		this->z = this->z - o.z;
		return *this;
	}
	inline v3 operator* (float m)
	{
		this->x = this->x * m;
		this->y = this->y * m;
		this->z = this->z * m;
		return *this;
	}
	inline v3 operator/ (float m)
	{
		this->x = this->x / m;
		this->y = this->y / m;
		this->z = this->z / m;
		return *this;
	}
};

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

#endif