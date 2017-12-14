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

Entity::Entity(char* pathToAssetFolder)
{
	char* modelPath = 	strcpy(modelPath, pathToAssetFolder);		strcat(modelPath,".obj");
	char* collisionPath = strcpy(collisionPath, pathToAssetFolder);	strcat(collisionPath,"collision.obj");
	//Load the model data
	model = new Mesh();
	if (!importModel(modelPath, true))
	{
		printf("Failed to import model at:%s", modelPath);
	}
	collisionGeometry = new Collider();
	if (!importCollision(collisionPath))
	{
		printf("Failed to import model at:%s", modelPath);
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
