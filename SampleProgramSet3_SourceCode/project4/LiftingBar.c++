// LiftingBar.c++

#include "LiftingBar.h"

LiftingBar::LiftingBar(ShaderIF* sIF, double x, double y, double zs, double ze, const char* bbellTexture) : SceneElement(sIF, *(new PhongMaterial(0.90, 0.91, 0.98)))
{
  xStart = x; yStart = y; zStart = zs; zEnd = ze;

  xmin = x-0.2; xmax = x+0.2;
  ymin = y-0.2; ymax = y+0.2;
  zmin = zs-1.25; zmax = ze+1.25;

  bbell = bbellTexture;

  defineInitialGeometry();
}

LiftingBar::~LiftingBar()
{
  for(int i = 0; i < 3; i++)
  {
    delete arrayCylinder[i];
  }
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void LiftingBar::getMCBoundingBox(double* xyzLimits) const
{
  xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void LiftingBar::defineInitialGeometry()
{
  double k[3]; k[0] = 0.90; k[1] = 0.91; k[2] = 0.98; //Silver
  //Skinny bar part in the middle
  arrayCylinder[0] = new Cylinder(shaderIF, xStart, yStart, zStart, zEnd, 0.1, k, 100, bbell, 10);
  //Bigger bar parts on the ends
	arrayCylinder[1] = new Cylinder(shaderIF, xStart, yStart, zStart-1.25, zStart, 0.2, k, 100, bbell, 10);
	arrayCylinder[2] = new Cylinder(shaderIF, xStart, yStart, zEnd, zEnd+1.25, 0.2, k, 100, bbell, 10);
}

void LiftingBar::render()
{
	for (int i = 0; i < 3; i++)
  {
    arrayCylinder[i] -> render();
  }
}
