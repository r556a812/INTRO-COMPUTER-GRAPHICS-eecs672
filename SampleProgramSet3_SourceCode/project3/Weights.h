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
  Weights(ShaderIF* sIF, double x);
  virtual ~Weights();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

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
