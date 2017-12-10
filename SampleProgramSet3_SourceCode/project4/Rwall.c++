#include <iostream>
#include "Rwall.h"

Rwall::Rwall(ShaderIF* sIF, float cx, float cy, float cz, float lx, float ly, float lz, double k[3], float s, float a, const char* texImageSource, int divide) : SceneElement(sIF, *(new PhongMaterial(k[0], k[1], k[2], 0.2, 0.2, 0.8, s, a))),
                                                                                                                                        wrapS(GL_CLAMP_TO_BORDER), wrapT(GL_CLAMP_TO_BORDER)
{
  xyz[0] = cx; xyz[1] = lx + cx; //Xmin and Xmax
  xyz[2] = cy; xyz[3] = ly + cy; //Ymin and Ymax
  xyz[4] = cz; xyz[5] = lz + cz; //Zmin and Zmax

  for (int i = 0; i < 3; i++)
  {
    kd[i] = k[i];
  }

  d = divide;

  defineInitialGeometry();
  texID = defineTexture(texImageSource);
}

Rwall::~Rwall()
{
  glDeleteBuffers(2, vbo);
  glDeleteVertexArrays(1, vao);
}

void Rwall::defineInitialGeometry()
{
  //Coords for the Floor all in feet
  vec3 vertices[4] =
  {
    {static_cast<float>(xyz[0]), static_cast<float>(xyz[2]), static_cast<float>(xyz[4])},
    {static_cast<float>(xyz[0]), static_cast<float>(xyz[3]), static_cast<float>(xyz[4])},
    {static_cast<float>(xyz[1]), static_cast<float>(xyz[3]), static_cast<float>(xyz[5])},
    {static_cast<float>(xyz[1]), static_cast<float>(xyz[2]), static_cast<float>(xyz[5])}
  };

  vec2 texCoords[4] = { {0,0}, {1,0}, {1,1}, {0,1} };

  //Create the VAO and VBO names
  glGenVertexArrays(1, vao);
  glGenBuffers(2, vbo);

  //Initialize the VAO and VBO
  glBindVertexArray(vao[0]);
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

  //Allocate space for and send data to the GPU
  int numBytes = sizeof(vec3) * 4;
  glBufferData(GL_ARRAY_BUFFER, numBytes, vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

  glDisableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 4*2*sizeof(float), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("texCoords"), 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("texCoords"));
}

void Rwall::getMCBoundingBox(double* xyzLimits) const
{
  for (int i = 0; i < 6; i++)
  {
    xyzLimits[i] = xyz[i];
  }
}

void Rwall::render()
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
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  glUniform1i(shaderIF->ppuLoc("texUse"), 0);

  glUseProgram(pgm);
}
