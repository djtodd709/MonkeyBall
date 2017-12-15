#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Mesh.h"
#include "Collider.h"

//Base class for all game objects - each should include a model and  collision geometry.
class Entity{
public:
	Entity(const char * pathToAssetFolder);

	virtual void drawMesh(float repeats);
	v3 checkCollision(v3 incoming);
	virtual void reset() = 0;
	virtual void onTick() = 0;
	virtual void onCollision(Entity* o, v3 normal) = 0; //Entity collided with, as well as the normal of the collision surface
	v3* currentPosition;
	v3* startingPosition;
protected:

	bool importModel(char* path, bool textured);
	bool importCollision(char* path);
	Mesh* model;
	Collider* collisionGeometry;
	char* modelExt = (char*)".obj";
	char* collisionExt = (char*)"collision.obj";
};

#endif
