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

Entity::Entity(const char * pathToAssetFolder)
{
	char * modelPath = 	strcpy(modelPath, pathToAssetFolder);		strcat(modelPath,".obj");
	char * collisionPath = strcpy(collisionPath, pathToAssetFolder);	strcat(collisionPath,"collision.obj");
	//Load the model data 
	this.model = new Mesh();
	this.model = model.importModel(const char * modelPath, bool textured);
	this.collisionGeometry = new Collider();
	this.collisionGeometry = collisionGeometry.importCollision(const char * collisionPath);
}

bool importCollision(const char * path);

//Passthroughs
void Entity::drawMesh()
{
	model.drawMesh();
}
v3 Entity::checkCollision(v3 incoming)
{
	return collisionGeometry.checkCollision(incoming);
}

void Entity::onTick()
{
	
}

void Entity::onCollision()
{
	
}