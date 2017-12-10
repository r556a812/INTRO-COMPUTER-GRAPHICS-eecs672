#ifndef Floor_H
#define Floor_H

#include <GL/gl.h>
#include "ModelView.h"
#include "ShaderIF.h"

typedef float vec3[3];

class Floor : public ModelView
{
public:
  Floor(ShaderIF* sIF, float cx, float cy, float cz, float lx, float ly, float lz, double k[3]);
  virtual ~Floor();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

private:
  ShaderIF* shaderIF;
  GLuint vao[1];
  GLuint vbo[1];

  double xyz[6];
  float kd[3];

  void defineInitialGeometry();

};

#endif
