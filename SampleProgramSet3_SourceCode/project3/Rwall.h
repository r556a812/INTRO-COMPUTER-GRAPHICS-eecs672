#ifndef Rwall_H
#define Rwall_H

#include <GL/gl.h>
#include "SceneElement.h"

typedef float vec3[3];

class Rwall : public SceneElement
{
public:
  Rwall(ShaderIF* sIF, float cx, float cy, float cz, float lx, float ly, float lz, double k[3]);
  virtual ~Rwall();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

private:
  GLuint vao[1];
  GLuint vbo[1];

  double xyz[6];
  float kd[3];

  void defineInitialGeometry();

};

#endif
