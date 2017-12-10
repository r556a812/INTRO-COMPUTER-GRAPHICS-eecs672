#ifndef WeightHolder_H
#define WeightHolder_H

#include <GL/gl.h>
#include "SceneElement.h"
#include "Cylinder.h"
#include "Disk.h"
#include "Pole.h"

typedef float vec3[3];

class WeightHolder : public SceneElement
{
public:
  WeightHolder(ShaderIF* sIF, double x, double z, const char* bWeightTexture, const char* rWeightTexture, const char* grWeightTexture);
  virtual ~WeightHolder();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

protected:
  const char* bbell;
  const char* bW;
  const char* rW;
  const char* grW;

private:
  float xmin, xmax, ymin, ymax, zmin, zmax;
  double xStart, yStart, zStart;
  double kd[3];
  Cylinder* arrayCylinder[5];
  Disk* arrayDisk[10];
  Pole* arrayPole[17];

  void defineInitialGeometry();

};

#endif
