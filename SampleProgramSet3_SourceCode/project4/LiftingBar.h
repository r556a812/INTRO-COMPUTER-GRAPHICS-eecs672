#ifndef LiftingBar_H
#define LiftingBar_H

#include <GL/gl.h>
#include "SceneElement.h"
#include "Cylinder.h"


typedef float vec3[3];

class LiftingBar : public SceneElement
{
public:
  LiftingBar(ShaderIF* sIF, double x, double y, double zs, double ze, const char* bbellTexture);
  virtual ~LiftingBar();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

protected:
  const char* bbell;
private:
  float xmin, xmax, ymin, ymax, zmin, zmax;
  double xStart, yStart, zStart, zEnd;
  double kd[3];
  Cylinder* arrayCylinder[3];


  void defineInitialGeometry();

};

#endif
