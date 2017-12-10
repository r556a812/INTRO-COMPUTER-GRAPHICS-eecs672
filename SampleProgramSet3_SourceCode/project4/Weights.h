#ifndef Weights_H
#define Weights_H

#include <GL/gl.h>
#include "SceneElement.h"
#include "Cylinder.h"
#include "Disk.h"
#include "LiftingBar.h"

typedef float vec3[3];

class Weights : public SceneElement
{
public:
  Weights(ShaderIF* sIF, double x, const char* bbellTexture, const char* bWeightTexture, const char* rWeightTexture, const char* grWeightTexture);
  virtual ~Weights();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

protected:
  const char* bbell;
  const char* bW;
  const char* rW;
  const char* grW;
private:
  double kd[3];
  float xmin, xmax, ymin, ymax, zmin, zmax;
  double x1;
  Cylinder* arrayCylinder[8];
  Disk* arrayDisk[18];
  LiftingBar* arrayBar[3];

  void defineInitialGeometry();

};

#endif
