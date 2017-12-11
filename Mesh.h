#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include "MathHelper.h"

class Mesh{
public:
  Mesh();

  bool importObj(const char * path);
  void drawMesh();

private:
  std::vector < v3* > out_vertices;
  std::vector < v2* > out_uvs;
  std::vector < v3* > out_normals;
};

#endif
