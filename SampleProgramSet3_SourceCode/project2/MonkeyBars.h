#ifndef MonkeyBars_H
#define MonkeyBars_H

#include <GL/gl.h>
#include "ModelView.h"
#include "ShaderIF.h"
#include "Pole.h"

typedef float vec3[3];

class MonkeyBars : public ModelView
{
public:
  MonkeyBars(ShaderIF* sIF, double xStart, double xEnd, double zStart, double zEnd, double height, double k[3]);
  virtual ~MonkeyBars();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

private:
  ShaderIF* shaderIF;

  float xmin, xmax, ymin, ymax, zmin, zmax;
  double kd[3];
  Pole* arrayPole[24];

  void defineInitialGeometry();

};

#endif
