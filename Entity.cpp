#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "Entity.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

Entity::Entity(const char* pathToAssetFolder)
{
	printf("Does this even work");
	std::string modelPath("");
	printf("HOO-ERS\n");
	modelPath.append(pathToAssetFolder);
	printf("Save me devito");
	modelPath = modelPath + modelExt;
	std::string collisionPath (pathToAssetFolder);
	collisionPath += collisionExt;

	printf("Guess so");
	char mpca[modelPath.length()]; strcpy(mpca, modelPath.c_str());
	char cpca[collisionPath.length()]; strcpy(cpca, collisionPath.c_str());
	//Load the model data
	printf("Guess so");
	model = new Mesh();
	printf("Mesh?");
	if (!importModel(mpca, true))
	{
		printf("Failed to import model at:%s", mpca);
	}
	collisionGeometry = new Collider();
	if (!importCollision(cpca))
	{
		printf("Failed to import model at:%s", cpca);
	}
}

bool Entity::importModel(char* path, bool textured)
{
	//model = importModel(modelPath, true);
	return false;
}

bool Entity::importCollision(char* path)
{
	//collisionGeometry = importCollision(char* collisionPath);
	return false;
}

//Passthroughs
void Entity::drawMesh(float repeats)
{
	model->drawMesh(repeats);
}
v3 Entity::checkCollision(v3 incoming)
{
	return collisionGeometry->checkCollision(incoming);
}

void Entity::onTick()
{

}

void Entity::onCollision()
{

}
