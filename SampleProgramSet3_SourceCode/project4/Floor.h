#ifndef Floor_H
#define Floor_H

#include <GL/gl.h>
#include "SceneElement.h"

typedef float vec3[3];
typedef float vec2[2];

class Floor : public SceneElement
{
public:
  Floor(ShaderIF* sIF, float cx, float cy, float cz, float lx, float ly, float lz, double k[3], float s, const char* texImageSource, float divide);
  virtual ~Floor();
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

  void defineInitialGeometry();

};

#endif
