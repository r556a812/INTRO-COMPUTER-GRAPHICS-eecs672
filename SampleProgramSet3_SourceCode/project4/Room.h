#ifndef Room_H
#define Room_H

#include <GL/gl.h>
#include "SceneElement.h"
#include "Floor.h"
#include "Rwall.h"
#include "Pole.h"

typedef float vec3[3];

class Room : public SceneElement
{
public:
  Room(ShaderIF* sIF, const char* texImageSource_mat, const char* texImageSource_wood, const char* texImageSource_grass, const char* texImageSource_bmat, const char* texImageSource_wall);
  virtual ~Room();
  void getMCBoundingBox(double* xyzLimits) const;
  void render();

private:
  const char* woodTexture;
  const char* matTexture;
  const char* grassTexture;
  const char* bmatTexture;
  const char* wallTexture;
  float xmin, xmax, ymin, ymax, zmin, zmax;
  double kd[3];
  Floor* arrayFloor[10];
  Rwall* arrayWall[13];
  Pole* arrayPole[14];

  void defineInitialGeometry();

};

#endif
