// MonkeyBars.c++

#include "MonkeyBars.h"

MonkeyBars::MonkeyBars(ShaderIF* sIF, double xStart, double xEnd, double zStart, double zEnd, double height, double k[3]) : shaderIF(sIF)
{
  xmin = xStart; xmax = xEnd; ymin = 0.0; ymax = height; zmin = zStart; zmax = zEnd;

  for (int i = 0; i < 3; i++)
  {
    kd[i] = k[i];
  }

  defineInitialGeometry();
}

MonkeyBars::~MonkeyBars()
{
  for(int i = 0; i < 24; i++)
  {
    arrayPole[i] -> ~Pole();
  }
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void MonkeyBars::getMCBoundingBox(double* xyzLimits) const
{
  if (xmin < xmax)
  {
    xyzLimits[0] = xmin;
  	xyzLimits[1] = xmax;
  }
  else
  {
    xyzLimits[0] = xmax;
  	xyzLimits[1] = xmin;
  }

	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void MonkeyBars::defineInitialGeometry()
{
  double length = (zmax - zmin)/7;
  double width = length/(4*length);

  //Create the big Poles from ground up
	arrayPole[0] = new Pole(shaderIF, xmax, ymin, zmin, width, ymax, width, kd);
	arrayPole[1] = new Pole(shaderIF, xmax, ymin, zmin+length-width, width, ymax, width, kd);
	arrayPole[2] = new Pole(shaderIF, xmax, ymin, zmin+(3*length)-width, width, ymax, width, kd);
	arrayPole[3] = new Pole(shaderIF, xmax, ymin, zmin+(4*length)-width, width, ymax, width, kd);
	arrayPole[4] = new Pole(shaderIF, xmax, ymin, zmin+(6*length)-width, width, ymax, width, kd);
	arrayPole[5] = new Pole(shaderIF, xmax, ymin, zmin+(7*length)-width, width, ymax, width, kd);

  //If statement to count for the change in the width of the bar in the calculations.
  //Since start at top left corner, math is different on one side of room than the other side
  //Left side adds the width of bar, right side subtracts width
  if (xmin == 0)
  {
    //Creates the connecting poles at the top
    arrayPole[6] = new Pole(shaderIF, xmax+width, ymax-(.1*ymax), zmin, width/2, width/2, zmax-zmin, kd);
  	arrayPole[7] = new Pole(shaderIF, xmax+width, ymax-(.01*ymax), zmin, width/2, width/2, zmax-zmin, kd);

    //Creates the connecting poles from wall to big Poles
  	arrayPole[8] = new Pole(shaderIF, xmin, ymax-(.1*ymax), zmin, xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[9] = new Pole(shaderIF, xmin, ymax-(.01*ymax), zmin, xmax-xmin+width, width/2, width/2, kd);

  	arrayPole[10] = new Pole(shaderIF, xmin, ymax-(.1*ymax), zmin+length, xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[11] = new Pole(shaderIF, xmin, ymax-(.01*ymax), zmin+length, xmax-xmin+width, width/2, width/2, kd);

  	arrayPole[12] = new Pole(shaderIF, xmin, ymax-(.1*ymax), zmin+(2*length), xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[13] = new Pole(shaderIF, xmin, ymax-(.01*ymax), zmin+(2*length), xmax-xmin+width, width/2, width/2, kd);

  	arrayPole[14] = new Pole(shaderIF, xmin, ymax-(.1*ymax), zmin+(3*length), xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[15] = new Pole(shaderIF, xmin, ymax-(.01*ymax), zmin+(3*length), xmax-xmin+width, width/2, width/2, kd);

  	arrayPole[16] = new Pole(shaderIF, xmin, ymax-(.1*ymax), zmin+(4*length), xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[17] = new Pole(shaderIF, xmin, ymax-(.01*ymax), zmin+(4*length), xmax-xmin+width, width/2, width/2, kd);

  	arrayPole[18] = new Pole(shaderIF, xmin, ymax-(.1*ymax), zmin+(5*length), xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[19] = new Pole(shaderIF, xmin, ymax-(.01*ymax), zmin+(5*length), xmax-xmin+width, width/2, width/2, kd);

  	arrayPole[20] = new Pole(shaderIF, xmin, ymax-(.1*ymax), zmin+(6*length), xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[21] = new Pole(shaderIF, xmin, ymax-(.01*ymax), zmin+(6*length), xmax-xmin+width, width/2, width/2, kd);

  	arrayPole[22] = new Pole(shaderIF, xmin, ymax-(.1*ymax), zmin+(7*length), xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[23] = new Pole(shaderIF, xmin, ymax-(.01*ymax), zmin+(7*length), xmax-xmin+width, width/2, width/2, kd);
  }
  else
  {
    //Creates the connecting poles at the top
    arrayPole[6] = new Pole(shaderIF, xmax-(width/2), ymax-(.1*ymax), zmin, width/2, width/2, zmax-zmin, kd);
  	arrayPole[7] = new Pole(shaderIF, xmax-(width/2), ymax-(.01*ymax), zmin, width/2, width/2, zmax-zmin, kd);

    //Creates the connecting poles from wall to big Poles
  	arrayPole[8] = new Pole(shaderIF, xmin-width, ymax-(.1*ymax), zmin, xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[9] = new Pole(shaderIF, xmin-width, ymax-(.01*ymax), zmin, xmax-xmin+width, width/2, width/2, kd);

  	arrayPole[10] = new Pole(shaderIF, xmin-width, ymax-(.1*ymax), zmin+length, xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[11] = new Pole(shaderIF, xmin-width, ymax-(.01*ymax), zmin+length, xmax-xmin+width, width/2, width/2, kd);

  	arrayPole[12] = new Pole(shaderIF, xmin-width, ymax-(.1*ymax), zmin+(2*length), xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[13] = new Pole(shaderIF, xmin-width, ymax-(.01*ymax), zmin+(2*length), xmax-xmin+width, width/2, width/2, kd);

  	arrayPole[14] = new Pole(shaderIF, xmin-width, ymax-(.1*ymax), zmin+(3*length), xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[15] = new Pole(shaderIF, xmin-width, ymax-(.01*ymax), zmin+(3*length), xmax-xmin+width, width/2, width/2, kd);

  	arrayPole[16] = new Pole(shaderIF, xmin-width, ymax-(.1*ymax), zmin+(4*length), xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[17] = new Pole(shaderIF, xmin-width, ymax-(.01*ymax), zmin+(4*length), xmax-xmin+width, width/2, width/2, kd);

  	arrayPole[18] = new Pole(shaderIF, xmin-width, ymax-(.1*ymax), zmin+(5*length), xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[19] = new Pole(shaderIF, xmin-width, ymax-(.01*ymax), zmin+(5*length), xmax-xmin+width, width/2, width/2, kd);

  	arrayPole[20] = new Pole(shaderIF, xmin-width, ymax-(.1*ymax), zmin+(6*length), xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[21] = new Pole(shaderIF, xmin-width, ymax-(.01*ymax), zmin+(6*length), xmax-xmin+width, width/2, width/2, kd);

  	arrayPole[22] = new Pole(shaderIF, xmin-width, ymax-(.1*ymax), zmin+(7*length), xmax-xmin+width, width/2, width/2, kd);
  	arrayPole[23] = new Pole(shaderIF, xmin-width, ymax-(.01*ymax), zmin+(7*length), xmax-xmin+width, width/2, width/2, kd);
  }


}

void MonkeyBars::render()
{
	for (int i = 0; i < 24; i++)
  {
    arrayPole[i] -> render();
  }
}
