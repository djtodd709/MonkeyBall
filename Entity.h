#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Mesh.h"
#include "Collider.h"

//Base class for all game objects - each should include a model and  collision geometry.
class Entity{
public:
	Entity(const char * pathToAssetFolder);

	void drawMesh();
	v3 checkCollision(v3 incoming);
	virtual void onTick();
	virtual void onCollision();
private:

	bool importModel(const char * path, bool textured);
	bool importCollision(const char * path, bool textured);
	Mesh model;
	Collider collisionGeometry;
};

#endif
