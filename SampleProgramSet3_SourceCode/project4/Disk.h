#ifndef Disk_H
#define Disk_H

#include <GL/gl.h>
#include "SceneElement.h"

typedef float vec3[3];
typedef float vec2[2];

class Disk : public SceneElement
{
public:
  Disk(ShaderIF* sIF, double x, double y, double z,  double r, double k[3], float s, const char* texImageSource, float divide);
  virtual ~Disk();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

protected:
  GLenum wrapS, wrapT;
  float d;

private:
  GLuint vao[1];
  GLuint vbo[2];

  double xyz[6];
  float kd[3];
  double x1, y1, z1, r1;

  void defineInitialGeometry();

};

#endif
