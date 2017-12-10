// Room.c++

#include "Room.h"

Room::Room(ShaderIF* sIF, const char* texImageSource_mat, const char* texImageSource_wood, const char* texImageSource_grass, const char* texImageSource_bmat, const char* texImageSource_wall) : SceneElement(sIF, *(new PhongMaterial(0.556863, 0.137255, 0.137255)))
{
  xmin = 0.0; xmax = 71.0;
  ymin = 0.0; ymax = 20.0;
  zmin = 0.0; zmax = 40.0;

  matTexture = texImageSource_mat;
  woodTexture = texImageSource_wood;
  grassTexture = texImageSource_grass;
  bmatTexture = texImageSource_bmat;
  wallTexture = texImageSource_wall;

  defineInitialGeometry();
}

Room::~Room()
{
  for(int i = 0; i < 10; i++)
  {
    delete arrayFloor[i];
  }
  for (int i = 0; i < 13; i++)
  {
    delete arrayWall[i];
  }
  for (int i = 0; i < 14; i++)
  {
    delete arrayPole[i];
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
  double kg[3];
  float s = 25.0;

  int d = 10;

  //Create the floor
	//kf[0] = 0.556863; kf[1] = 0.137255; kf[2] = 0.137255; //Red
  kf[0] = 1; kf[1] = 0; kf[2] = 0;
	arrayFloor[0] = new Floor(shaderIF, 0.0, 0.0, 0.0, 50.0, 0.0, 40.0, kf, s, bmatTexture, 10);

  //Create the gray strips on the floor ends
	kb[0] = 0.9; kb[1] = 0.9; kb[2] = 0.9; //Gray
	arrayFloor[1] = new Floor(shaderIF, 1.0, 0.01, 0.0, 6.0, 0.0, 40.0, kb, s, matTexture, 5);
  arrayFloor[2] = new Floor(shaderIF, 43.0, 0.01, 0.0, 6.0, 0.0, 40.0, kb, s, matTexture, 5);

  //Create the weight lifting squares on the floor
  k[0] = 0.858824; k[1] = 0.858824; k[2] = 0.439216; //Brown
  s = 100.0;
  //Left side
	arrayFloor[3] = new Floor(shaderIF, 8.5, 0.01, 6.3, 10.0, 0.0, 3.2, k, s, woodTexture, 1);
	arrayFloor[4] = new Floor(shaderIF, 8.5, 0.01, 18.3, 10.0, 0.0, 3.2, k, s, woodTexture, 1);
	arrayFloor[5] = new Floor(shaderIF, 8.5, 0.01, 30.3, 10.0, 0.0, 3.2, k, s, woodTexture, 1);
  //Right side
  arrayFloor[6] = new Floor(shaderIF, 31.5, 0.01, 6.3, 10.0, 0.0, 3.2, k, s, woodTexture, 1);
	arrayFloor[7] = new Floor(shaderIF, 31.5, 0.01, 18.3, 10.0, 0.0, 3.2, k, s, woodTexture, 1);
	arrayFloor[8] = new Floor(shaderIF, 31.5, 0.01, 30.3, 10.0, 0.0, 3.2, k, s, woodTexture, 1);

  //Grass outside right window
  k[0] = 0.486; k[1] = 0.988; k[2] = 0.0;
  arrayFloor[9] = new Floor(shaderIF, 50.01, 0.0, 0.0, 20.0, 0.0, 40.0, k, s, grassTexture, 10);

	k[0] = 0.752941; k[1] = 0.752941; k[2] = 0.752941; // Light blue
  s = 25.0;
  //Create the Right Wall
	arrayWall[0] = new Rwall(shaderIF, 50, 10, 0, 0, 10, 40, k, s, 1, wallTexture, d);
  arrayWall[1] = new Rwall(shaderIF, 50, 0, 0, 0, 10, 6, k, s, 1, wallTexture, d);
  arrayWall[2] = new Rwall(shaderIF, 50, 0, 34, 0, 10, 6, k, s, 1, wallTexture, d);

  //Create the Left Wall
	arrayWall[3] = new Rwall(shaderIF, 0, 10, 0, 0, 10, 40, k, s, 1, wallTexture, d);
  arrayWall[4] = new Rwall(shaderIF, 0, 0, 0, 0, 10, 6, k, s, 1, wallTexture, d);
  arrayWall[5] = new Rwall(shaderIF, 0, 0, 34, 0, 10, 6, k, s, 1, wallTexture, d);

	k[0] = 0.184314; k[1] = 0.184314; k[2] = 0.309804; //Navy Blue
  //Create the Back Wall
	arrayWall[6] = new Rwall(shaderIF, 0.0, 0.0, 0.0, 50.0, 20.0, 0.0, k, s, 1, wallTexture, 0.5);
  //Create the Blue Stripes on the side walls. Uses same k as back wall
	arrayWall[7] = new Rwall(shaderIF, 49.99, 15, 0.0, 0, 3, 40, k, s, 1, wallTexture, d);
	arrayWall[8] = new Rwall(shaderIF, 0.01, 15, 0.0, 0, 3, 40, k, s, 1, wallTexture, d);

	k[0] = 0.556863; k[1] = 0.137255; k[2] = 0.137255; //Red
  //Create the red stripe on the side walls.
	arrayWall[9] = new Rwall(shaderIF, 49.98, 16, 0.0, 0, 1.0, 40, k, s, 1, wallTexture, d);
	arrayWall[10] = new Rwall(shaderIF, 0.02, 16, 0.0, 0, 1.0, 40, k, s, 1, wallTexture, d);

  kb[0] = 0; kb[1] = 0; kb[2] = 0;
  kg[0] = 0.39; kg[1] = 0.78; kg[2] = 0.98;//red 0.74902 green 0.847059 blue 0.847059
  s = 95.0;
  //Window on right wall
  arrayWall[11] = new Rwall(shaderIF, 50, 0, 6, 0, 10, 28, kg, s, 0.65, wallTexture, d);
  //Border around the window
  arrayPole[0] = new Pole(shaderIF, 49.7, 0.0, 6, 0.3, 0.3, 28, kb);
  arrayPole[1] = new Pole(shaderIF, 49.7, 9.7, 6, 0.3, 0.3, 28, kb);
  arrayPole[2] = new Pole(shaderIF, 49.7, 0.3, 6, 0.3, 9.7, 0.3, kb);
  arrayPole[3] = new Pole(shaderIF, 49.7, 0.3, 33.7, 0.3, 9.7, 0.3, kb);
  //Lines in the middle of the window
  arrayPole[4] = new Pole(shaderIF, 49.7, 0.3, 12.7, 0.3, 9.7, 0.3, kb);
  arrayPole[5] = new Pole(shaderIF, 49.7, 0.3, 19.7, 0.3, 9.7, 0.3, kb);
  arrayPole[6] = new Pole(shaderIF, 49.7, 0.3, 26.7, 0.3, 9.7, 0.3, kb);

  //window on left wall
  arrayWall[12] = new Rwall(shaderIF, 0, 0, 6, 0, 10, 28, kg, s, 0.65, wallTexture, d);
  //Border around the window
  arrayPole[7] = new Pole(shaderIF, 0, 0.0, 6, 0.3, 0.3, 28, kb);
  arrayPole[8] = new Pole(shaderIF, 0, 9.7, 6, 0.3, 0.3, 28, kb);
  arrayPole[9] = new Pole(shaderIF, 0, 0.3, 6, 0.3, 9.7, 0.3, kb);
  arrayPole[10] = new Pole(shaderIF, 0, 0.3, 33.7, 0.3, 9.7, 0.3, kb);
  //Lines in the middle of the window
  arrayPole[11] = new Pole(shaderIF, 0, 0.3, 12.7, 0.3, 9.7, 0.3, kb);
  arrayPole[12] = new Pole(shaderIF, 0, 0.3, 19.7, 0.3, 9.7, 0.3, kb);
  arrayPole[13] = new Pole(shaderIF, 0, 0.3, 26.7, 0.3, 9.7, 0.3, kb);
}

void Room::render()
{
	for (int i = 0; i < 10; i++)
  {
    arrayFloor[i] -> render();
  }
  for (int i = 0; i < 13; i++)
  {
    arrayWall[i] -> render();
  }
  for (int i = 0; i < 14; i++)
  {
    arrayPole[i] -> render();
  }
}
