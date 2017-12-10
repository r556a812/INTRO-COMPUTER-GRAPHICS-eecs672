#ifndef Weights_H
#define Weights_H

#include <GL/gl.h>
#include "ModelView.h"
#include "ShaderIF.h"
#include "Cylinder.h"
#include "Disk.h"
#include "LiftingBar.h"

typedef float vec3[3];

class Weights : public ModelView
{
public:
  Weights(ShaderIF* sIF, double x);
  virtual ~Weights();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

private:
  ShaderIF* shaderIF;

  double kd[3];
  float xmin, xmax, ymin, ymax, zmin, zmax;
  double x1;
  Cylinder* arrayCylinder[8];
  Disk* arrayDisk[18];
  LiftingBar* arrayBar[3];

  void defineInitialGeometry();

};

#endif
