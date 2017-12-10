// Cylinder.h

#ifndef CYLINDER_H
#define CYLINDER_H

#include <GL/gl.h>

#include "SceneElement.h"

typedef float vec2[2];

class Cylinder : public SceneElement
{
public:
	Cylinder(ShaderIF* sIF, double x1, double height, double zStart, double zEnd, double radius, double k[3], float s, const char* texImageSource, float divide);
	virtual ~Cylinder();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimits) const;
	void render();
protected:
	GLenum wrapS, wrapT;
  float d;
	
private:
	GLuint vao[1];
	GLuint vbo[3]; // 0: coordinates; 1: normal vectors
	float kd[3];
  double x, y, z1, z2, r;

	void defineCylinder();
};

#endif
