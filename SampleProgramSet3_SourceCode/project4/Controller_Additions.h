// GLFWController.h - A concrete Controller subclass using the GLFW window interface

#ifndef CONTROLLER_ADDITIONS_H
#define CONTROLLER_ADDITIONS_H

#include "GLFW/glfw3.h"

#include "GLFWController.h"
#include "SceneElement.h"

class Controller_Additions : public GLFWController
{
public:
	Controller_Additions(const std::string& windowTitle, int rcFlags = 0);
	virtual ~Controller_Additions();
  void setShader(ShaderIF* s);

protected:
	void handleDisplay();
  void drawObjects();


  ShaderIF* shaderIF;
};

#endif
