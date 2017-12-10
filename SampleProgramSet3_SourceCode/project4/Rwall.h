#ifndef Rwall_H
#define Rwall_H

#include <GL/gl.h>
#include "SceneElement.h"

typedef float vec3[3];
typedef float vec2[2];

class Rwall : public SceneElement
{
public:
  Rwall(ShaderIF* sIF, float cx, float cy, float cz, float lx, float ly, float lz, double k[3], float s, float a, const char* texImageSource, int divide);
  virtual ~Rwall();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

protected:
  int d;
  GLenum wrapS, wrapT;

private:
  GLuint vao[1];
  GLuint vbo[2];

  double xyz[6];
  float kd[3];

  void defineInitialGeometry();

};

#endif
