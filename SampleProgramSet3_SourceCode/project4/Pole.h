#ifndef Pole_H
#define Pole_H

#include <GL/gl.h>
#include "SceneElement.h"

typedef float vec3[3];

class Pole : public SceneElement
{
public:
  Pole(ShaderIF* sIF, double cx, double cy, double cz, double lx, double ly, double lz, double k[3]);
  virtual ~Pole();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

private:
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
