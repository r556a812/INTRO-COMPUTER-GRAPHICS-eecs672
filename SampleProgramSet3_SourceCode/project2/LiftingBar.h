#ifndef LiftingBar_H
#define LiftingBar_H

#include <GL/gl.h>
#include "ModelView.h"
#include "ShaderIF.h"
#include "Cylinder.h"


typedef float vec3[3];

class LiftingBar : public ModelView
{
public:
  LiftingBar(ShaderIF* sIF, double x, double y, double zs, double ze);
  virtual ~LiftingBar();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

private:
  ShaderIF* shaderIF;

  float xmin, xmax, ymin, ymax, zmin, zmax;
  double xStart, yStart, zStart, zEnd;
  double kd[3];
  Cylinder* arrayCylinder[3];


  void defineInitialGeometry();

};

#endif
