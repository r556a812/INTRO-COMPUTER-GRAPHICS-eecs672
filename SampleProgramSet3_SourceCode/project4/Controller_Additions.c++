#include "Controller_Additions.h"

Controller_Additions::Controller_Additions(const std::string& windowTitle, int rcFlags): GLFWController(windowTitle, rcFlags), shaderIF(nullptr)
{
}

Controller_Additions::~Controller_Additions()
{
}

void Controller_Additions::handleDisplay()
{
  if (theWindow == nullptr)
		return;
	glfwMakeContextCurrent(theWindow);
	int width, height;
	glfwGetFramebufferSize(theWindow, &width, &height);
	glViewport(0, 0, width, height);

	// clear the frame buffer
	glClear(glClearFlags);

  glDepthMask(GL_TRUE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // glClear(glClearFlags);
  glUseProgram(shaderIF->getShaderPgmID());
  glUniform1i(shaderIF->ppuLoc("sceneHasTranslucentObjects"), 1);

  // draw opaque objects
  glDisable(GL_BLEND);
  glUniform1i(shaderIF->ppuLoc("drawingOpaqueObjects"), 1);
  drawObjects();

  // draw translucent objects
  glDepthMask(GL_FALSE);
  glEnable(GL_BLEND);
  glUniform1i(shaderIF->ppuLoc("drawingOpaqueObjects"), 0);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  drawObjects();

  glfwSwapBuffers(theWindow);
  
}

void Controller_Additions::setShader(ShaderIF* s)
{
  shaderIF = s;
}

void Controller_Additions::drawObjects()
{
  for (std::vector<ModelView*>::iterator it=models.begin() ; it<models.end() ; it++)
		(*it)->render();
}
