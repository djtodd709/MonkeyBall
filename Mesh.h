#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include "Vec.h"

class Mesh{
public:
  Mesh();

  bool importObj(const char * path, bool textured);
  void drawMesh();

private:
  std::vector < Vec3 > out_vertices;
  std::vector < Vec2 > out_uvs;
  std::vector < Vec3 > out_normals;
};

#endif
