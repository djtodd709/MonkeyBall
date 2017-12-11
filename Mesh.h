#ifndef __MESH_H__
#define __MESH_H__

class Mesh{
public:
  Mesh();

  bool importObj(const char * path);
  void drawMesh();

private:
  std::vector < glm::vec3 > out_vertices;
  std::vector < glm::vec2 > out_uvs;
  std::vector < glm::vec3 > out_normals;
};

#endif
