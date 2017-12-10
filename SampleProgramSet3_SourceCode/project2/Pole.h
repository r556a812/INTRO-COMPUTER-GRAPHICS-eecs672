#ifndef Pole_H
#define Pole_H

#include <GL/gl.h>
#include "ModelView.h"
#include "ShaderIF.h"

typedef float vec3[3];

class Pole : public ModelView
{
public:
  Pole(ShaderIF* sIF, double cx, double cy, double cz, double lx, double ly, double lz, double k[3]);
  virtual ~Pole();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

private:
  ShaderIF* shaderIF;
  GLuint vao[1];
  GLuint vbo[1];
  GLuint ebo[3];

  float xmin, xmax, ymin, ymax, zmin, zmax;
  float kd[3];

  static GLuint indexList[3][4];

  void defineInitialGeometry();
  void renderPole();

};

#endif
