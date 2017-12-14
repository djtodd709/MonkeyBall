#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Mesh.h"
#include "Collider.h"

//Base class for all game objects - each should include a model and  collision geometry.
class Entity{
public:
	Entity(const char * pathToAssetFolder);

	void drawMesh(float repeats);
	v3 checkCollision(v3 incoming);
	virtual void onTick();
	virtual void onCollision();
protected:

	bool importModel(char* path, bool textured);
	bool importCollision(char* path);
	Mesh* model;
	Collider* collisionGeometry;
	char* modelExt = (char*)".obj";
	char* collisionExt = (char*)"collision.obj";
};

#endif
