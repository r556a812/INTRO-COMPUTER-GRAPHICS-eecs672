#ifndef Room_H
#define Room_H

#include <GL/gl.h>
#include "ModelView.h"
#include "ShaderIF.h"
#include "Floor.h"
#include "Rwall.h"

typedef float vec3[3];

class Room : public ModelView
{
public:
  Room(ShaderIF* sIF);
  virtual ~Room();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

private:
  ShaderIF* shaderIF;

  float xmin, xmax, ymin, ymax, zmin, zmax;
  double kd[3];
  Floor* arrayFloor[9];
  Rwall* arrayWall[7];

  void defineInitialGeometry();

};

#endif
