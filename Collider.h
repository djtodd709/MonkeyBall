#ifndef __COLLIDER_H__
#define __COLLIDER_H__

//Entity collder, attach to an Entity object
class Collider{
public:
	Collider();
	bool importCollision(const char * path);
	//Checks if  incoming vector collides with the object, returns the normal vector of whichever surface we hit.
	v3 checkCollision(v3 incoming);
private:
	//Bounding box used to early out if we miss the collider completely
	v3 boundingBoxMin;
	v3 boundingBoxMax;
	std::vector < v3* > vertices;
	std::vector < v3* > normals;
};

#endif
