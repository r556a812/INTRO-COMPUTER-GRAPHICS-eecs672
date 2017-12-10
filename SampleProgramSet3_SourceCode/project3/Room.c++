// Room.c++

#include "Room.h"

Room::Room(ShaderIF* sIF) : SceneElement(sIF, *(new PhongMaterial(0.556863, 0.137255, 0.137255)))
{
  xmin = 0.0; xmax = 50.0;
  ymin = 0.0; ymax = 20.0;
  zmin = 0.0; zmax = 40.0;

  defineInitialGeometry();
}

Room::~Room()
{
  for(int i = 0; i < 9; i++)
  {
    delete arrayFloor[i];
  }
  for (int i = 0; i < 7; i++)
  {
    delete arrayWall[i];
  }
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Room::getMCBoundingBox(double* xyzLimits) const
{
  xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void Room::defineInitialGeometry()
{
  double kf[3];
  double kb[3];
  double k[3];

  //Create the floor
	kf[0] = 0.556863; kf[1] = 0.137255; kf[2] = 0.137255; //Red
	arrayFloor[0] = new Floor(shaderIF, 0.0, 0.0, 0.0, 50.0, 0.0, 40.0, kf);

  //Create the gray strips on the floor ends
	kb[0] = 0.9; kb[1] = 0.9; kb[2] = 0.9; //Gray
	arrayFloor[1] = new Floor(shaderIF, 1.0, 0.01, 0.0, 6.0, 0.0, 40.0, kb);
  arrayFloor[2] = new Floor(shaderIF, 43.0, 0.01, 0.0, 6.0, 0.0, 40.0, kb);

  //Create the weight lifting squares on the floor
  k[0] = 0.858824; k[1] = 0.858824; k[2] = 0.439216; //Brown
  //Left side
	arrayFloor[3] = new Floor(shaderIF, 8.5, 0.01, 6.3, 10.0, 0.0, 3.2, k);
	arrayFloor[4] = new Floor(shaderIF, 8.5, 0.01, 18.3, 10.0, 0.0, 3.2, k);
	arrayFloor[5] = new Floor(shaderIF, 8.5, 0.01, 30.3, 10.0, 0.0, 3.2, k);
  //Right side
  arrayFloor[6] = new Floor(shaderIF, 31.5, 0.01, 6.3, 10.0, 0.0, 3.2, k);
	arrayFloor[7] = new Floor(shaderIF, 31.5, 0.01, 18.3, 10.0, 0.0, 3.2, k);
	arrayFloor[8] = new Floor(shaderIF, 31.5, 0.01, 30.3, 10.0, 0.0, 3.2, k);

	k[0] = 0.752941; k[1] = 0.752941; k[2] = 0.752941; // Light blue
  //Create the Right Wall
	arrayWall[0] = new Rwall(shaderIF, 50, 0, 0, 0, 20, 40, k);
  //Create the Left Wall
	arrayWall[1] = new Rwall(shaderIF, 0, 0, 0, 0, 20, 40, k);

	k[0] = 0.184314; k[1] = 0.184314; k[2] = 0.309804; //Navy Blue
  //Create the Back Wall
	arrayWall[2] = new Rwall(shaderIF, 0.0, 0.0, 0.0, 50.0, 20.0, 0.0, k);
  //Create the Blue Stripes on the side walls. Uses same k as back wall
	arrayWall[3] = new Rwall(shaderIF, 49.99, 15, 0.0, 0, 3, 40, k);
	arrayWall[4] = new Rwall(shaderIF, 0.01, 15, 0.0, 0, 3, 40, k);

	k[0] = 0.556863; k[1] = 0.137255; k[2] = 0.137255; //Red
  //Create the red stripe on the side walls.
	arrayWall[5] = new Rwall(shaderIF, 49.98, 16, 0.0, 0, 1.0, 40, k);
	arrayWall[6] = new Rwall(shaderIF, 0.02, 16, 0.0, 0, 1.0, 40, k);
}

void Room::render()
{
	for (int i = 0; i < 9; i++)
  {
    arrayFloor[i] -> render();
  }
  for (int i = 0; i < 7; i++)
  {
    arrayWall[i] -> render();
  }
}
