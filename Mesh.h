#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include "MathHelper.h"

class Mesh{
public:
  Mesh();

  bool importObj(const char * path, bool textured, char * texPath);
  void drawMesh(float repeats);
  GLubyte* LoadPPM(char* file, int* width, int* height, int* max);

private:
  std::vector < v3* > out_vertices;
  std::vector < v2* > out_uvs;
  std::vector < v3* > out_normals;
  bool TEX;
  GLubyte *tex;
  int width, height, max;
};

#endif
