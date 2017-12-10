#ifndef WeightHolder_H
#define WeightHolder_H

#include <GL/gl.h>
#include "ModelView.h"
#include "ShaderIF.h"
#include "Cylinder.h"
#include "Disk.h"
#include "Pole.h"

typedef float vec3[3];

class WeightHolder : public ModelView
{
public:
  WeightHolder(ShaderIF* sIF, double x, double z);
  virtual ~WeightHolder();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

private:
  ShaderIF* shaderIF;

  float xmin, xmax, ymin, ymax, zmin, zmax;
  double xStart, yStart, zStart;
  double kd[3];
  Cylinder* arrayCylinder[5];
  Disk* arrayDisk[10];
  Pole* arrayPole[17];

  void defineInitialGeometry();

};

#endif
