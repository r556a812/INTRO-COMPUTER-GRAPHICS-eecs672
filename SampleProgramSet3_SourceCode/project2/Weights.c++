// Weights.c++

#include "Weights.h"

Weights::Weights(ShaderIF* sIF, double x) : shaderIF(sIF)
{
  xmin = x-0.8; xmax = x+0.8;
  ymin = 1.0-0.8; ymax = 6.0+0.8;
  zmin = 4.45; zmax = 35.35;
  x1 = x;
  defineInitialGeometry();
}

Weights::~Weights()
{
  for (int i = 0; i < 8; i++)
  {
    arrayCylinder[i] -> ~Cylinder();
  }
  for (int i = 0; i < 18; i++)
  {
    arrayDisk[i] -> ~Disk();
  }
  for (int i = 0; i < 3; i++)
  {
    arrayBar[i] -> ~LiftingBar();
  }
}
void Weights::getMCBoundingBox(double* xyzLimits) const
{
  xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}


void Weights::defineInitialGeometry()
{
  double k[3];
	double kr[3];
	double kg[3];
	double kb[3];
	kr[0] = 1.0; kr[1] = 0.0; kr[2] = 0.0; //Red weights
	kg[0] = 0.2; kg[1] = 1.0; kg[2] = 0.5; //Green weights
	kb[0] = 0.0; kb[1] = 0.0; kb[2] = 1.0; //Blue weights
	k[0] = 0.90; k[1] = 0.91; k[2] = 0.98; //Silver

	/************ Create the weight lifting bars ************/

	//Bar #1
  arrayBar[0] = new LiftingBar(shaderIF, x1, 6, 29.7, 34.1);
	arrayDisk[0] = new Disk(shaderIF, x1, 6, 28.45, 0.2, k);
	arrayDisk[1] = new Disk(shaderIF, x1, 6, 35.35, 0.2, k);
	//Bar #2
  arrayBar[1] = new LiftingBar(shaderIF, x1, 1, 17.7, 22.1);
	arrayDisk[2] = new Disk(shaderIF, x1, 1, 16.45, 0.2, k);
	arrayDisk[3] = new Disk(shaderIF, x1, 1, 23.35, 0.2, k);
	//Bar #3
  arrayBar[2] = new LiftingBar(shaderIF, x1, 5, 5.7, 10.1);
	arrayDisk[4] = new Disk(shaderIF, x1, 5, 4.45, 0.2, k);
	arrayDisk[5] = new Disk(shaderIF, x1, 5, 11.35, 0.2, k);


/********** Create the weights on the bars **********/

	//Bar #1
	//Red Weight
	arrayCylinder[0] = new Cylinder(shaderIF, x1, 6, 29.3, 29.69, 0.8, kr);
	arrayCylinder[1] = new Cylinder(shaderIF, x1, 6, 34.11, 34.4, 0.8, kr);
	//Disk for ends of Red
	arrayDisk[6] = new Disk(shaderIF, x1, 6, 29.3, 0.8, kr);
	arrayDisk[7] = new Disk(shaderIF, x1, 6, 29.69, 0.8, kr);
	arrayDisk[8] = new Disk(shaderIF, x1, 6, 34.11, 0.8, kr);
  arrayDisk[9] = new Disk(shaderIF, x1, 6, 34.4, 0.8, kr);
	//Green Weight
	arrayCylinder[2] = new Cylinder(shaderIF, x1, 6, 29.1, 29.31, 0.6, kg);
	arrayCylinder[3] = new Cylinder(shaderIF, x1, 6, 34.41, 34.6, 0.6, kg);
	//Disk for ends of Green
	arrayDisk[10] = new Disk(shaderIF, x1, 6, 29.1, 0.6, kg);
	arrayDisk[11] = new Disk(shaderIF, x1, 6, 34.6, 0.6, kg);

  /********** BAR #2 HAS NO WEIGHTS **********/

	//Bar #3
	//Red Weight
	arrayCylinder[4] = new Cylinder(shaderIF, x1, 5, 5.3, 5.7, 0.8, kr);
	arrayCylinder[5] = new Cylinder(shaderIF, x1, 5, 10.1, 10.4, 0.8, kr);
	//Disk for ends of Red
	arrayDisk[12] = new Disk(shaderIF, x1, 5, 5.7, 0.8, kr);
	arrayDisk[13] = new Disk(shaderIF, x1, 5, 5.3, 0.8, kr);
	arrayDisk[14] = new Disk(shaderIF, x1, 5, 10.4, 0.8, kr);
  arrayDisk[15] = new Disk(shaderIF, x1, 5, 10.1, 0.8, kr);
	//Blue Weight
  arrayCylinder[6] =new Cylinder(shaderIF, x1, 5, 5.15, 5.3, 0.68, kb);
	arrayCylinder[7] = new Cylinder(shaderIF, x1, 5, 10.4, 10.55, 0.68, kb);
	//Disk for ends of Blue
	arrayDisk[16] = new Disk(shaderIF, x1, 5, 5.15, 0.68, kb);
	arrayDisk[17] = new Disk(shaderIF, x1, 5, 10.55, 0.68, kb);
}

void Weights::render()
{
	for (int i = 0; i < 8; i++)
  {
    arrayCylinder[i] -> render();
  }
  for (int i = 0; i < 18; i++)
  {
    arrayDisk[i] -> render();
  }
  for (int i = 0; i < 3; i++)
  {
    arrayBar[i] -> render();
  }
}
