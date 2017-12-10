// WeightHolder.c++

#include "WeightHolder.h"

WeightHolder::WeightHolder(ShaderIF* sIF, double x, double z, const char* bWeightTexture, const char* rWeightTexture, const char* grWeightTexture) : SceneElement(sIF, *(new PhongMaterial(0.90, 0.91, 0.98)))
{
  xStart = x; zStart = z;

  xmin = x; xmax = x+1.7;
  ymin = 0; ymax = 1.6+0.32;//diamater of biggest weight(red) + height of the weight holder base
  zmin = z; zmax = z+4.0;

  bW = bWeightTexture; rW = rWeightTexture; grW = grWeightTexture;

  defineInitialGeometry();
}

WeightHolder::~WeightHolder()
{
  for (int i = 0; i < 17; i++)
  {
    delete arrayPole[i];
  }
  for (int i = 0; i < 5; i++)
  {
    delete arrayCylinder[i];
  }
  for (int i = 0; i < 10; i++)
  {
    delete arrayDisk[i];
  }
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void WeightHolder::getMCBoundingBox(double* xyzLimits) const
{
  xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void WeightHolder::defineInitialGeometry()
{
  double kb[3]; kb[0] = 0.0; kb[1] = 0.0; kb[2] = 0.0; //black
	double kr[3]; kr[0] = 1.0; kr[1] = 0.0; kr[2] = 0.0; //Red weights
	double kg[3]; kg[0] = 0.2; kg[1] = 1.0; kg[2] = 0.5; //Green weights
	double kbl[3]; kbl[0] = 0.0; kbl[1] = 0.0; kbl[2] = 1.0; //Blue weights
	double ks[3]; ks[0] = 0.90; ks[1] = 0.91; ks[2] = 0.98; //Silver

	arrayPole[0] = new Pole(shaderIF, xStart, 0.01, zStart, 1.7, 0.3, 4.0, ks); //Base of weight holder
	arrayPole[1] = new Pole(shaderIF, xStart, 0.31, zStart, 1.7, 0.01, 4.0, kb); //Base of weight holder

	arrayPole[2] = new Pole(shaderIF, xStart, 0.3, zStart, 0.1, 0.7, 0.1, ks); //bar at end
	arrayPole[3] = new Pole(shaderIF, xStart+1.6, 0.3, zStart, 0.1, 0.7, 0.1, ks); //bar at end
	arrayPole[4] = new Pole(shaderIF, xStart, 0.9, zStart, 1.7, 0.1, 0.1, ks); //bar at end
  zStart+=0.5;
	arrayCylinder[0] = new Cylinder(shaderIF, xStart + 0.85, 1.11, zStart, zStart+0.4, 0.8, kr, 50, rW, 1); //Red weight
	arrayDisk[0] = new Disk(shaderIF, xStart + 0.85, 1.11, zStart, 0.8, kr, 50, rW, 1); //Disk end
	arrayDisk[1] = new Disk(shaderIF, xStart + 0.85, 1.11, zStart+0.4, 0.8, kr, 50, rW, 1); //Disk end
  zStart+=0.5;
	arrayPole[5] = new Pole(shaderIF, xStart, 0.3, zStart, 0.1, 0.7, 0.1, ks); //bar between weights
	arrayPole[6] = new Pole(shaderIF, xStart+1.6, 0.3, zStart, 0.1, 0.7, 0.1, ks); //bar between weights
	arrayPole[7] = new Pole(shaderIF, xStart, 0.9, zStart, 1.7, 0.1, 0.1, ks); //bar between weights

	arrayCylinder[1] = new Cylinder(shaderIF, xStart + 0.85, 1.11, zStart+0.2, zStart+0.6, 0.8, kr, 50, rW, 1); //Red weight
	arrayDisk[2] = new Disk(shaderIF, xStart + 0.85, 1.11, zStart+0.2, 0.8, kr, 50, rW, 1); //Disk end
  arrayDisk[3] = new Disk(shaderIF, xStart + 0.85, 1.11, zStart+0.6, 0.8, kr, 50, rW, 1); //Disk end
  zStart+=1.0;
  arrayPole[8] = new Pole(shaderIF, xStart, 0.3, zStart, 0.1, 0.7, 0.1, ks); //bar between weights
	arrayPole[9] = new Pole(shaderIF, xStart+1.6, 0.3, zStart, 0.1, 0.7, 0.1, ks); //bar between weights
	arrayPole[10] = new Pole(shaderIF, xStart, 0.9, zStart, 1.7, 0.1, 0.1, ks); //bar between weights

  arrayCylinder[2] = new Cylinder(shaderIF, xStart + 0.85, 1.0, zStart+0.1, zStart+0.25, 0.68, kbl, 50, bW, 1);//Blue Weight
  arrayDisk[4] = new Disk(shaderIF, xStart + 0.85, 1.0, zStart+0.1, 0.68, kbl, 50, bW, 1);
	arrayDisk[5] = new Disk(shaderIF, xStart + 0.85, 1.0, zStart+0.25, 0.68, kbl, 50, bW, 1);

  arrayCylinder[3] = new Cylinder(shaderIF, xStart + 0.85, 0.91, zStart+0.3, zStart+0.51, 0.6, kg, 50, grW, 1); //Green Weight
  arrayDisk[6] = new Disk(shaderIF, xStart + 0.85, 0.91, zStart+0.3, 0.6, kg, 50, grW, 1);
  arrayDisk[7] = new Disk(shaderIF, xStart + 0.85, 0.91, zStart+0.51, 0.6, kg, 50, grW, 1);
  zStart+=1.0;
  arrayPole[11] = new Pole(shaderIF, xStart, 0.3, zStart, 0.1, 0.7, 0.1, ks); //bar between weights
	arrayPole[12] = new Pole(shaderIF, xStart+1.6, 0.3, zStart, 0.1, 0.7, 0.1, ks); //bar between weights
	arrayPole[13] = new Pole(shaderIF, xStart, 0.9, zStart, 1.7, 0.1, 0.1, ks); //bar between weights

  arrayCylinder[4] = new Cylinder(shaderIF, xStart + 0.85, 0.91, zStart+0.1, zStart+0.31, 0.6, kg, 50, grW, 1); //Green Weight
	arrayDisk[8] = new Disk(shaderIF, xStart + 0.85, 0.91, zStart+0.1, 0.6, kg, 50, grW, 1);
	arrayDisk[9] = new Disk(shaderIF, xStart + 0.85, 0.91, zStart+0.31, 0.6, kg, 50, grW, 1);
  zStart+=1.0;
  arrayPole[14] = new Pole(shaderIF, xStart, 0.3, zStart, 0.1, 0.7, 0.1, ks); //bar between weights
	arrayPole[15] = new Pole(shaderIF, xStart+1.6, 0.3, zStart, 0.1, 0.7, 0.1, ks); //bar between weights
	arrayPole[16] = new Pole(shaderIF, xStart, 0.9, zStart, 1.7, 0.1, 0.1, ks); //bar between weights
}

void WeightHolder::render()
{
	for (int i = 0; i < 17; i++)
  {
    arrayPole[i] -> render();
  }
  for (int i = 0; i < 5; i++)
  {
    arrayCylinder[i] -> render();
  }
  for (int i = 0; i < 10; i++)
  {
    arrayDisk[i] -> render();
  }
}
