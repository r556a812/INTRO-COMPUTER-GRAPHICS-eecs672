// Cylinder.h

#ifndef CYLINDER_H
#define CYLINDER_H

#include <GL/gl.h>

#include "ModelView.h"
#include "ShaderIF.h"

class Cylinder : public ModelView
{
public:
	Cylinder(ShaderIF* sIF, double x1, double height, double zStart, double zEnd, double radius, double k[3]);
	virtual ~Cylinder();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimits) const;
	void render();
private:
	ShaderIF* shaderIF;
	GLuint vao[1];
	GLuint vbo[2]; // 0: coordinates; 1: normal vectors
	float kd[3];
  double x, y, z1, z2, r;

	void defineCylinder();
};

#endif
