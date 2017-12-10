#include <iostream>
#include <math.h>

#include "Cylinder.h"

Cylinder::Cylinder(ShaderIF* sIF, double x1, double height, double zStart, double zEnd, double radius, double k[3], float s, const char* texImageSource, float divide) : SceneElement(sIF, *(new PhongMaterial(k[0], k[1], k[2], 0.2, 0.2, 0.8, s, 1.0))),
                                                                                                                                        wrapS(GL_CLAMP_TO_BORDER), wrapT(GL_CLAMP_TO_BORDER)
{
  x = x1; y = height; z1 = zStart; z2 = zEnd; r = radius;

  for (int i = 0; i < 3; i++)
  {
    kd[i] = k[i];
  }

	defineCylinder();
  texID = defineTexture(texImageSource);
}

Cylinder::~Cylinder()
{
	glDeleteBuffers(3, vbo);
	glDeleteVertexArrays(1, vao);
}

const int N_POINTS_AROUND_SLICE = 18; // number points around a cross-section

void Cylinder::defineCylinder()
{
	typedef float vec3[3];
	int nPoints = 2 * (N_POINTS_AROUND_SLICE + 1);
	vec3* coords = new vec3[nPoints];
	vec3* normals = new vec3[nPoints];
  vec2* texCoords = new vec2[nPoints];
	double theta = 0.0;
	double dTheta = 2.0*M_PI/N_POINTS_AROUND_SLICE;

  //Fill the array with the points
	for (int i=0 ; i<=N_POINTS_AROUND_SLICE ; i++)
	{
		int j = 2 * i;
		double dx = cos(theta);
		double dy = sin(theta);

    float tc = (i/(float)(2*M_PI));
    texCoords[i][0] = tc; texCoords[i][1] = z1;
    texCoords[i+1][0] = tc; texCoords[i+1][1] = z2;

		normals[j][0] = dx; normals[j][1] = dy; normals[j][2] = 0.0;
		coords[j][0] = x + r*dx; coords[j][1] = y + r*dy; coords[j][2] = z1;
		normals[j+1][0] = dx ; normals[j+1][1] = dy; normals[j+1][2] = 0.0;
		coords[j+1][0] = x + r*dx; coords[j+1][1] = y + r*dy; coords[j+1][2] = z2;


		theta += dTheta;
	}

	glGenVertexArrays(1, vao);
	glGenBuffers(3, vbo);
	glBindVertexArray(vao[0]);

	int numBytes = nPoints * sizeof(vec3);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, numBytes, coords, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, numBytes, normals, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

  glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, nPoints*2*sizeof(float), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("texCoords"), 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("texCoords"));

	delete [] coords;
	delete [] normals;
  delete [] texCoords;
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Cylinder::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = x - r;
	xyzLimits[1] = x + r;
	xyzLimits[2] = y - r;
	xyzLimits[3] = y + r;
	xyzLimits[4] = z1;
	xyzLimits[5] = z2;
}

void Cylinder::render()
{
	typedef float vec3[3];
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderIF->getShaderPgmID());

  establishLightingEnvironment();
  establishMaterial();
  establishTexture();
  establishView();

	glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 2*(N_POINTS_AROUND_SLICE+1));

  glUniform1i(shaderIF->ppuLoc("texUse"), 0);

	glUseProgram(pgm);
}
