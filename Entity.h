#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Mesh.h"
#include "Collider.h"

//Base class for all game objects - each should include a model and  collision geometry.
class Entity{
public:
	Entity(char * pathToAssetFolder);

	void drawMesh(float repeats);
	v3 checkCollision(v3 incoming);
	virtual void onTick();
	virtual void onCollision();
private:

	bool importModel(char* path, bool textured);
	bool importCollision(char* path);
	Mesh* model;
	Collider* collisionGeometry;
};

#endif
