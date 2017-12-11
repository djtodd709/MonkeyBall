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

/*obj for blender - turn every selection off to wirte file in simplest form - tick selection only*/

//WRITE OBJ IMPORTER
bool Mesh::importObj(const char * path, bool textured)
{
  std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
  std::vector< Vec3* > temp_vertices;
  std::vector< Vec2* > temp_uvs;
  std::vector< Vec3* > temp_normals;

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
      Vec3* vertex = new Vec3();
      fscanf(file, "%f %f %f\n", &vertex->x, &vertex->y, &vertex->z );
      temp_vertices.push_back(vertex);
    }
    else if ( strcmp( lineHeader, "vt" ) == 0 ){
      Vec2* uv = new Vec2();
      fscanf(file, "%f %f\n", &uv->x, &uv->y );
      temp_uvs.push_back(uv);
    }
    else if ( strcmp( lineHeader, "vn" ) == 0 ){
      Vec3* normal = new Vec3();
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
    Vec3 vertex = *temp_vertices[ vertexIndex-1 ];
    out_vertices.push_back(vertex);
  }
  //For each uv of each triangle
  for( unsigned int i=0; i<uvIndices.size(); i++ ){
    unsigned int uvIndex = uvIndices[i];
    Vec2 uv = *temp_uvs[ uvIndex-1 ];
    out_uvs.push_back(uv);
  }
  //For each normal of each triangle
  for( unsigned int i=0; i<normalIndices.size(); i++ ){
    unsigned int normalIndex = normalIndices[i];
    Vec3 normal = *temp_normals[ normalIndex-1 ];
    out_normals.push_back(normal);
  }
  return true;
}

//function for actually rendering/drawing the terrain mesh
void Mesh::drawMesh(){
  glBegin(GL_TRIANGLES);
  for( unsigned int i=0; i<out_vertices.size(); i++ ){
    glVertex3f(out_vertices[i].x,out_vertices[i].y,out_vertices[i].z);
  }
  glEnd();
}
