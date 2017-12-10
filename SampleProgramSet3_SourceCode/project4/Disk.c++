#include <iostream>
#include "Disk.h"

Disk::Disk(ShaderIF* sIF, double x, double y, double z, double r, double k[3], float s, const char* texImageSource, float divide) : SceneElement(sIF, *(new PhongMaterial(k[0], k[1], k[2], 0.2, 0.2, 0.8, s, 1))),
                                                                                                                                  wrapS(GL_CLAMP_TO_BORDER), wrapT(GL_CLAMP_TO_BORDER)
{
  xyz[0] = x - r; xyz[1] = x + r; //Xmin and Xmax
  xyz[2] = y-r; xyz[3] = y + r; //Ymin and Ymax
  xyz[4] = xyz[5] = z; //Zmin and Zmax

  x1 = x; y1 = y; z1 = z; r1 = r;

  for (int i = 0; i < 3; i++)
  {
    kd[i] = k[i];
  }

  defineInitialGeometry();
  texID = defineTexture(texImageSource);
}

Disk::~Disk()
{
  glDeleteBuffers(2, vbo);
  glDeleteVertexArrays(1, vao);
}

const int N_POINTS_AROUND_SLICE = 18;

void Disk::defineInitialGeometry()
{
  typedef float vec3[3];
	vec3* coords = new vec3[N_POINTS_AROUND_SLICE+1];
  vec2* texCoords = new vec2[N_POINTS_AROUND_SLICE+1];
	double theta = 0.0;
	double dTheta = 2.0*M_PI/N_POINTS_AROUND_SLICE;

  //Fill the array with points
	for (int i=0 ; i<=N_POINTS_AROUND_SLICE ; i++)
	{
		float dx = cos(theta);
		float dy = sin(theta);
		coords[i][0] = x1 + r1*dx;
    coords[i][1] = y1 + r1*dy;
    coords[i][2] = z1;

    float tx = dx*0.5 + 0.5;
    float ty = dy*0.5 + 0.5;
    texCoords[i][0] = tx; texCoords[i][1] = ty;

		theta += dTheta;
	}

  //Create the VAO and VBO names
  glGenVertexArrays(1, vao);
  glGenBuffers(2, vbo);

  //Initialize the VAO and VBO
  glBindVertexArray(vao[0]);
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

  //Allocate space for and send data to the GPU
  int numBytes = sizeof(vec3) * (N_POINTS_AROUND_SLICE+1);
  glBufferData(GL_ARRAY_BUFFER, numBytes, coords, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

  glDisableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, (N_POINTS_AROUND_SLICE+1)*2*sizeof(float), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("texCoords"), 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("texCoords"));

  delete [] coords;
  delete [] texCoords;
}

void Disk::getMCBoundingBox(double* xyzLimits) const
{
  for (int i = 0; i < 6; i++)
  {
    xyzLimits[i] = xyz[i];
  }
}

void Disk::render()
{
  //Save the current GLSL program in use
  GLint pgm;
  glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
  glUseProgram(shaderIF->getShaderPgmID());

  establishLightingEnvironment();
  establishMaterial();
  establishTexture();
  establishView();

  glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);

  glDisableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));
  glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, 0.0, 1.0);

  glBindVertexArray(vao[0]);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 20);

  glUniform1i(shaderIF->ppuLoc("texUse"), 0);

  glUseProgram(pgm);
}
