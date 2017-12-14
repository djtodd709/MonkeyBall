#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "Mesh.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>


Mesh::Mesh(){}

GLubyte* Mesh::LoadPPM(char* file, int* width, int* height, int* max)
{
	GLubyte* img;
	FILE *fd;
	int n, m;
	int  k, nm;
	char c;
	int i;
	char b[100];
	float s;
	int red, green, blue;

	fd = fopen(file, "r");
	fscanf(fd,"%[^\n] ",b);
	if(b[0]!='P'|| b[1] != '3')
	{
		printf("%s is not a PPM file!\n",file);
		exit(0);
	}
	printf("%s is a PPM file\n", file);
	fscanf(fd, "%c",&c);
	while(c == '#')
	{
		fscanf(fd, "%[^\n] ", b);
		printf("%s\n",b);
		fscanf(fd, "%c",&c);
	}
	ungetc(c,fd);
	fscanf(fd, "%d %d %d", &n, &m, &k);

	printf("%d rows  %d columns  max value= %d\n",n,m,k);

	nm = n*m;

	img = (GLubyte*)(malloc(3*sizeof(GLuint)*nm));

	s=255.0/k;


	for(i=0;i<nm;i++)
	{
		fscanf(fd,"%d %d %d",&red, &green, &blue );
		img[3*nm-3*i-3]=red*s;
		img[3*nm-3*i-2]=green*s;
		img[3*nm-3*i-1]=blue*s;
	}

	*width = n;
	*height = m;
	*max = k;

	return img;
}

bool Mesh::importObj(const char * path, bool textured, char * texPath)
{
  std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
  std::vector< v3* > temp_vertices;
  std::vector< v2* > temp_uvs;
  std::vector< v3* > temp_normals;

  FILE * file = fopen(path, "r");
  if( file == NULL ){
    printf("Impossible to open the file !\n");
    return false;
  }
  while( 1 ){

    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
      break; // EOF = End Of File. Quit the loop.

    // else : parse lineHeader
    if ( strcmp( lineHeader, "v" ) == 0 ){
      v3* vertex = new v3;
      fscanf(file, "%f %f %f\n", &vertex->x, &vertex->y, &vertex->z );
      temp_vertices.push_back(vertex);
    }
    else if ( strcmp( lineHeader, "vt" ) == 0 ){
      v2* uv = new v2;
      fscanf(file, "%f %f\n", &uv->x, &uv->y );
      temp_uvs.push_back(uv);
    }
    else if ( strcmp( lineHeader, "vn" ) == 0 ){
      v3* normal = new v3;
      fscanf(file, "%f %f %f\n", &normal->x, &normal->y, &normal->z );
      temp_normals.push_back(normal);
    }
    else if ( strcmp( lineHeader, "f" ) == 0 ){
      std::string vertex1, vertex2, vertex3;
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      if(textured){
        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
        if (matches != 9){
          printf("File too complex!\n");
          return false;
        }
        uvIndices    .push_back(uvIndex[0]);
        uvIndices    .push_back(uvIndex[1]);
        uvIndices    .push_back(uvIndex[2]);
      }
      else{
        int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
        if (matches != 6){
          printf("File too complex!\n");
          return false;
        }
      }
      vertexIndices.push_back(vertexIndex[0]);
      vertexIndices.push_back(vertexIndex[1]);
      vertexIndices.push_back(vertexIndex[2]);
      normalIndices.push_back(normalIndex[0]);
      normalIndices.push_back(normalIndex[1]);
      normalIndices.push_back(normalIndex[2]);
    }
  }
  // For each vertex of each triangle
  for( unsigned int i=0; i<vertexIndices.size(); i++ ){
    unsigned int vertexIndex = vertexIndices[i];
    v3* vertex = temp_vertices[ vertexIndex-1 ];
    out_vertices.push_back(vertex);
  }
  //For each uv of each triangle
  for( unsigned int i=0; i<uvIndices.size(); i++ ){
    unsigned int uvIndex = uvIndices[i];
    v2* uv = temp_uvs[ uvIndex-1 ];
    out_uvs.push_back(uv);
  }
  //For each normal of each triangle
  for( unsigned int i=0; i<normalIndices.size(); i++ ){
    unsigned int normalIndex = normalIndices[i];
    v3* normal = temp_normals[ normalIndex-1 ];
    out_normals.push_back(normal);
  }
	TEX = false;
  if(textured){
    tex = Mesh::LoadPPM(texPath, &width, &height, &max);
		TEX = true;
  }
  return true;
}

//function for actually rendering/drawing the terrain mesh
void Mesh::drawMesh(float repeats){
	if(TEX){
		glBindTexture(GL_TEXTURE_2D, *tex);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);
	}

  glBegin(GL_TRIANGLES);
    for( unsigned int i=0; i<out_vertices.size(); i++ ){
      glNormal3f(out_normals[i]->x,out_normals[i]->y,out_normals[i]->z);
			if(TEX){
				glTexCoord2f(((out_uvs[i]->x*-1) + 1)*repeats, out_uvs[i]->y*repeats);
			}
      glVertex3f(out_vertices[i]->x,out_vertices[i]->y,out_vertices[i]->z);
    }
  glEnd();
}
