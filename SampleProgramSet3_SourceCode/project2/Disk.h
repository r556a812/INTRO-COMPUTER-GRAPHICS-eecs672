#ifndef Disk_H
#define Disk_H

#include <GL/gl.h>
#include "ModelView.h"
#include "ShaderIF.h"

typedef float vec3[3];

class Disk : public ModelView
{
public:
  Disk(ShaderIF* sIF, double x, double y, double z,  double r, double k[3]);
  virtual ~Disk();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

private:
  ShaderIF* shaderIF;
  GLuint vao[1];
  GLuint vbo[1];

  double xyz[6];
  float kd[3];
  double x1, y1, z1, r1;

  void defineInitialGeometry();

};

#endif
